/// @date 2024-08-02
/// @file main.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief main runner
///
///
#include <MPM/TmpSimulation.h>
#include <common/Parameters.h>
#include <MPM/MpmGrid.h>

// 一个类，包含
//             cxxopts::Options options
//             nlohmann::json json

template <typename T, int dim>
struct tmp {
    using padding_size = std::conditional<dim == 3, std::integral_constant<int, 6>, std::integral_constant<int, 8>>;
    using idx_type     = std::conditional<std::is_same<T, float>::value, int32_t, int64_t>::type;

    ZIRAN::Vector<T, dim> a;
    T                  m;
    ZIRAN::Vector<T, dim> new_v;
    idx_type           idx;

    ZIRAN::Vector<T, padding_size::type::value> padding;

    T phase_field;
    T phase_field_multiplier;

    void reset()
    {

    }
};

namespace ZIRAN {
// static_assert(is_power_of_two(sizeof(tmp<float, 2>)), "GridState<float, 2> size must be POT");
static_assert(is_power_of_two(sizeof(tmp<float, 3>)), "GridState<float, 3> size must be POT");
// static_assert(is_power_of_two(sizeof(tmp<double, 2>)), "GridState<double, 2> size must be POT");
static_assert(is_power_of_two(sizeof(tmp<double, 3>)), "GridState<double, 3> size must be POT");

template <class T, int dim>
class MPMGrid {
  public:
    static constexpr int log2_page        = 12;   // 每页内存为 4KB 2^12 = 4096
    static constexpr int spgrid_size      = 2048; // 2048 * 2048 * 2048 * 4KB = 16GB
    static constexpr int half_spgrid_size = spgrid_size / 2;
    using SparseGrid                      = SPGrid_Allocator<tmp<T, dim>, dim, log2_page>;
    using SparseMask                      = typename SparseGrid::template Array_type<>::MASK;
    using PageMap                         = SPGrid_Page_Map<log2_page>;
    // Linear_Offset() is not a constexpr function to initialize this
    const uint64_t origin_offset;

    std::unique_ptr<SparseGrid> grid;
    std::unique_ptr<PageMap>    page_map;
    std::unique_ptr<PageMap>    fat_page_map;
    int                         num_nodes = 0;

    std::vector<int>      particle_fence;
    std::vector<uint64_t> particle_sorter;

  public:
    MPMGrid()
        : origin_offset(SparseMask::Linear_Offset(half_spgrid_size, half_spgrid_size, half_spgrid_size)) {
        if constexpr (dim == 2) {
            grid = std::make_unique<SparseGrid>(spgrid_size, spgrid_size);
        } else {
            grid = std::make_unique<SparseGrid>(spgrid_size, spgrid_size, spgrid_size);
        }
        page_map     = std::make_unique<PageMap>(*grid);
        fat_page_map = std::make_unique<PageMap>(*grid);
    }

    void sortParticles(const Field<Vector<T, dim>>& positions, T dx) {
        // BOW_TIMER_FLAG("sort particles");
        constexpr int index_bits = (32 - SparseMask::block_bits);
        particle_sorter.resize(positions.size());
        auto grid_array = grid->Get_Array();
        {
            // BOW_TIMER_FLAG("prepare array to sort");
            // BOW_ASSERT(positions.size() <= (1u << index_bits));
            tbb::parallel_for(0, (int)positions.size(), [&](int i) {
                BSplineWeights<T, dim> spline(positions[i], dx);
                auto what = spline.base_node.data();
                spdlog::info("spline.base_node.data() : {}, {}, {}", what[0], what[1], what[2]);
                uint64_t biased_offset = SparseMask::Linear_Offset(1000,0,0);
                spdlog::info("biased_offset : {}", biased_offset);
                spdlog::info("origin_offset : {}", origin_offset);
                uint64_t offset        = SparseMask::Packed_Add(biased_offset, origin_offset);
                particle_sorter[i]     = ((offset >> SparseMask::data_bits) << index_bits) + i;
            });
        }
        {
            // BOW_TIMER_FLAG("tbb parallel sort");
            tbb::parallel_sort(particle_sorter.begin(), particle_sorter.begin() + particle_sorter.size());
        }
        {
            // BOW_TIMER_FLAG("reset page map");
            page_map->Clear();
            for (int i = 0; i < (int)particle_sorter.size(); i++) {
                uint64_t offset = (particle_sorter[i] >> index_bits) << SparseMask::data_bits;
                page_map->Set_Page(offset);
            }
            page_map->Update_Block_Offsets();
        }
        // Update particle offset
        auto blocks = page_map->Get_Blocks();
        {
            // BOW_TIMER_FLAG("fat page map");
            // Reset fat_page_map
            // 记录相邻单元格
            fat_page_map->Clear();
            for (int b = 0; b < (int)blocks.second; b++) {
                spdlog::info("blocks.first[b] : {}", blocks.first[b]);
                spdlog::info("blocks.second   : {}", blocks.second);
                auto base_offset = blocks.first[b];
                if constexpr (dim == 2) {
                    auto x = 1 << SparseMask::block_xbits;
                    auto y = 1 << SparseMask::block_ybits;
                    auto c = SparseMask::LinearToCoord(base_offset);
                    for (int i = -1 + (c[0] == 0); i < 2; i++) {
                        for (int j = -1 + (c[1] == 0); j < 2; j++) {
                            fat_page_map->Set_Page(
                                SparseMask::Packed_Add(base_offset, SparseMask::Linear_Offset(x * i, y * j)));
                        }
                    }
                } else {
                    auto x = 1 << SparseMask::block_xbits;
                    auto y = 1 << SparseMask::block_ybits;
                    auto z = 1 << SparseMask::block_zbits;
                    auto c = SparseMask::LinearToCoord(base_offset);
                    for (int i = -1 + (c[0] == 0); i < 2; i++) {
                        for (int j = -1 + (c[1] == 0); j < 2; j++) {
                            for (int k = -1 + (c[2] == 0); k < 2; k++) {
                                fat_page_map->Set_Page(SparseMask::Packed_Add(
                                    base_offset, SparseMask::Linear_Offset(x * i, y * j, z * k)));
                            }
                        }
                    }
                }
            }
            fat_page_map->Update_Block_Offsets();
        }
        auto fat_blocks = fat_page_map->Get_Blocks();
        {
            // BOW_TIMER_FLAG("reset grid");
            // 将所有数据归零？
            for (int i = 0; i < (int)fat_blocks.second; ++i) {
                auto offset = fat_blocks.first[i];
                std::memset((T*)&grid_array(offset), 0, 1 << log2_page);
                auto* g = reinterpret_cast<tmp<T, dim>*>(&grid_array(offset));
                for (int k = 0; k < (int)SparseMask::elements_per_block; ++k)
                    g[k].reset();
            }
        }
        {
            // BOW_TIMER_FLAG("block particle offset");
            // 记录每个单元格中排在第一个的粒子的索引
            particle_fence.clear();
            uint64_t last_offset = -1;
            for (uint32_t i = 0; i < particle_sorter.size(); i++) {
                if (last_offset != (particle_sorter[i] >> 32)) particle_fence.push_back(i);
                last_offset = particle_sorter[i] >> 32;
                particle_sorter[i] &= ((1ll << index_bits) - 1);
            }
            particle_fence.push_back((uint32_t)particle_sorter.size());
        }
        num_nodes = 0;
    }
};
} // namespace ZIRAN

// page_map 是 bitmap, 用于记录哪些页被使用. 重置, 只记录那些被使用的内存页的offset.
// 1. 清理被记录的块
// 2. 将空间索引翻译成线性位移(linear offset)，偏位移(biased offset), 偏尾移相对于空间原点。
// 3. SparseMask::Packed_Add 获得真实的位移 offset to the channel base, 空间原点移动到整个区域的中心。
// 4. Set_Page(offset)
// 5. Update_block_offset()

int main(int argc, char* argv[]) {

    ParameterRoot::startup();
    init_logging(argc, argv);
    parse_arguments(argc, argv);
    ZIRAN::MPMGrid<double, 3>       grid;
    ZIRAN::Field<ZIRAN::Vector<double, 3>> positions;
    positions.push_back(ZIRAN::Vector<double, 3>(1, 2, 3));
    // void sortParticles(const Field<Vector<T, dim>>& positions, T dx)
    grid.sortParticles(positions, 0.1);

    // TmpSimulation<double, 3> sim;

    // spdlog::info("Size of MpmGrid<double, 3> : {}", sizeof(ZIRAN::MpmGrid<double, 3>));
    // spdlog::info("Size of MpmGrid<double, 2> : {}", sizeof(ZIRAN::MpmGrid<double, 2>));
    // spdlog::info("Size of MpmGrid<float, 2> : {}", sizeof(ZIRAN::MpmGrid<float, 2>));
    // spdlog::info("Size of MpmGrid<float, 3> : {}", sizeof(ZIRAN::MpmGrid<float, 3>));

    // spdlog::info("Size of GridState<double, 2> : {}", sizeof(ZIRAN::GridState<double, 2>));
    // spdlog::info("Size of GridState<double, 3> : {}", sizeof(ZIRAN::GridState<double, 3>));
    // spdlog::info("Size of GridState<float, 2> : {}", sizeof(ZIRAN::GridState<float, 2>));
    // spdlog::info("Size of GridState<float, 3> : {}", sizeof(ZIRAN::GridState<float, 3>));

    // spdlog::info("Size of tmp<double, 3> : {}", sizeof(tmp<double, 3>));
    // spdlog::info("Size of tmp<double, 2> : {}", sizeof(tmp<double, 2>));
    // spdlog::info("Size of tmp<float, 3> : {}", sizeof(tmp<float, 3>));
    // spdlog::info("Size of tmp<float, 2> : {}", sizeof(tmp<float, 2>));

    // spdlog::info("Size of TmpSimulation<double, 3> : {}", sizeof(TmpSimulation<double, 3>));

    // sim.end_frame = 100;
    // sim.simulate();
    return 0;
}
