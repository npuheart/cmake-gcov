#include <common/DataDir.h>
#include <common/io/ObjIO.h>
#include <common/io/PvdWriter.h>
#include <common/io/VtkIO.h>
#include <common/io/VtuIO.h>

#include <common/log/timer.h>

int main_vtk() {
    FUNCTION_TIMER;
    ZIRAN::DataDir output_dir{};
    std::string    obj_filename = output_dir.absolutePath(ZIRAN::outputFileName("partio", ".vtk"));

    // 示例数据：一个包含几个三维点的 std::vector
    std::vector<std::array<double, 3>> points = {{0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {0.0, 1.2, 0.0},
                                                 {0.0, 1.3, 0.0}, {0.0, 1.4, 0.0}, {0.0, 1.5, 0.0}, {0.5, 0.5, 1.0}};
    IO::writePositionVectorToVtk(obj_filename, points);
    return 0;
}

int main_vtu() {
    FUNCTION_TIMER;
    std::vector<std::array<double, 3>> points = {{1, 2, 1}, {1, 2, 2}, {1, 2, 3}};
    std::vector<std::array<double, 3>> v1_3D  = {{1, 2, 1}, {1, 2, 2}, {1, 2, 3}};
    std::vector<std::array<double, 3>> v2_3D  = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<double>                v3     = {1, 2, 3};
    std::vector<std::string>           tags{"v1", "v2", "v3"};
    IO::write_particles_to_vtu("aaa.vtu", points, tags, v1_3D, v2_3D, v3);
    return 0;
}

int main_vtu_2() {
    FUNCTION_TIMER;
    ZIRAN::DataDir output_dir{};
    std::string    obj_filename = output_dir.absolutePath("candy.obj");
    std::string    vtu_filename = output_dir.absolutePath("candy.vtu");
    auto           points       = IO::read_obj_vertices(obj_filename);
    spdlog::info("Reading obj file: {}", obj_filename);

    std::vector<double> v3;
    for (const auto& p : points) {
        v3.push_back(p[0]);
    }
    std::vector<std::string> tags{"v3"};
    IO::write_particles_to_vtu(vtu_filename, points, tags, v3);
    spdlog::info("Writing vtu file: {}", vtu_filename);
    return 0;
}

int main_pvd() {
    FUNCTION_TIMER;
    ZIRAN::DataDir output_dir{};
    std::string    obj_filename = output_dir.absolutePath("candy.obj");
    spdlog::info("Reading obj file: {}", obj_filename);
    IO::PvdWriter<IO::FileType::VTU> writer("aaa");
    
    for (size_t i = 0; i < 100; i++) {
        writer.write(0.1 * i, i);
    }

    return 0;
}
