/// @date 2024-08-02
/// @file main.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief main runner
///
///
#include <common/Parameters.h>
#include <MPM/TmpSimulation.h>
#include <MPM/MpmGrid.h>


// 一个类，包含
//             cxxopts::Options options
//             nlohmann::json json

template <typename T, int dim>
struct tmp
{
    std::array<T, dim> a;
    T m;
    std::array<T, dim> new_v;
    using idx_type = std::conditional<std::is_same<T, float>::value, int32_t, int64_t>::type;
    idx_type idx;
    
    using padding_size = std::conditional<dim == 3, std::integral_constant<int, 6>, std::integral_constant<int, 8>>;
    std::array<T, padding_size::type::value> padding;
    
    T phase_field;
    T phase_field_multiplier;
};

int main(int argc, char* argv[]) {

    ParameterRoot::startup();
    init_logging(argc, argv);
    parse_arguments(argc, argv);
    ZIRAN::MpmGrid<double, 3> grid;
    TmpSimulation<double, 3> sim;

    spdlog::info("Size of MpmGrid<double, 3> : {}", sizeof(ZIRAN::MpmGrid<double, 3>));
    spdlog::info("Size of MpmGrid<double, 2> : {}", sizeof(ZIRAN::MpmGrid<double, 2>));
    spdlog::info("Size of MpmGrid<float, 2> : {}", sizeof(ZIRAN::MpmGrid<float, 2>));
    spdlog::info("Size of MpmGrid<float, 3> : {}", sizeof(ZIRAN::MpmGrid<float, 3>));

    spdlog::info("Size of GridState<double, 2> : {}", sizeof(ZIRAN::GridState<double, 2>));
    spdlog::info("Size of GridState<double, 3> : {}", sizeof(ZIRAN::GridState<double, 3>));
    spdlog::info("Size of GridState<float, 2> : {}", sizeof(ZIRAN::GridState<float, 2>));
    spdlog::info("Size of GridState<float, 3> : {}", sizeof(ZIRAN::GridState<float, 3>));
      
    spdlog::info("Size of tmp<double, 3> : {}", sizeof(tmp<double, 3>));
    spdlog::info("Size of tmp<double, 2> : {}", sizeof(tmp<double, 2>));  
    spdlog::info("Size of tmp<float, 3> : {}", sizeof(tmp<float, 3>));
    spdlog::info("Size of tmp<float, 2> : {}", sizeof(tmp<float, 2>));
    

    // spdlog::info("Size of TmpSimulation<double, 3> : {}", sizeof(TmpSimulation<double, 3>));
    
    // sim.end_frame = 100;
    // sim.simulate();
    return 0;
}

