/// @date 2024-08-02
/// @file main.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief main runner
///
///
#include <common/io/ObjIO.h>
#include <common/io/VtuIO.h>
#include <common/DataDir.h>

int main(int argc, char* argv[]) {
    init_logging(argc, argv);
    ZIRAN::DataDir output_dir{};
    std::string obj_filename = output_dir.absolutePath("candy.obj");
    spdlog::info("Reading obj file: {}", obj_filename);
    auto points = IO::read_obj_vertices(obj_filename);
    std::vector<double>      v3;
    for (const auto& p : points) { v3.push_back(p[0]); }
    std::vector<std::string> tags{"v3"};
    IO::write_particles_to_vtu("aaa.vtu", points, tags, v3);
    return 0;
}
