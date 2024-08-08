/// @date 2024-08-02
/// @file main.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief main runner
///
///
#include <VtuIO.h>

int main(int argc, char* argv[]) {
    init_logging(argc, argv);

    std::vector<std::array<double, 3>> points = {{1, 2, 1}, {1, 2, 2}, {1, 2, 3}};
    std::vector<std::array<double, 3>> v1_3D  = {{1, 2, 1}, {1, 2, 2}, {1, 2, 3}};
    std::vector<std::array<double, 3>> v2_3D  = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<double>                v3     = {1, 2, 3};
    std::vector<std::string>           tags{"v1", "v2", "v3"};
    write_particles_to_vtu("aaa.vtu", points, tags, v1_3D, v2_3D, v3);
    return 0;
}
