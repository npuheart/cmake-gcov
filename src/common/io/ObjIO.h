

#pragma once




#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <common/log.h>
namespace IO {
std::vector<std::array<double,3>> read_obj_vertices(const std::string& filename) {

    std::ifstream objFile(filename.c_str()); 
    if (!objFile.is_open()) {
        LOG_ERROR("Could not open the .obj file : {}", filename.c_str());
    }

    std::vector<std::array<double,3>> vertices;
    std::string line;

    while (std::getline(objFile, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {  // Only process lines starting with 'v'
            std::array<double,3> vertex;
            iss >> vertex[0] >> vertex[1] >> vertex[2];
            vertices.push_back(vertex);
        }
    }

    objFile.close();

    // Output parsed vertex data
    // std::cout << "Vertices:\n";
    // for (const auto& v : vertices) {
    //     std::cout << "v " << v[0] << " " << v[1] << " " << v[2] << std::endl;
    // }

    return vertices;
}
} // namespace IO

// #include <ObjIO.h>
// #include <VtuIO.h>
// #include <common/DataDir.h>
// int main(int argc, char* argv[]) {
//     init_logging(argc, argv);
//     ZIRAN::DataDir output_dir{};
//     std::string obj_filename = output_dir.absolutePath("candy.obj");
//     spdlog::info("Reading obj file: {}", obj_filename);
//     auto points = read_obj_vertices(obj_filename);
//     std::vector<double>      v3;
//     for (const auto& p : points) { v3.push_back(p[0]); }
//     std::vector<std::string> tags{"v3"};
//     write_particles_to_vtu("aaa.vtu", points, tags, v3);
//     return 0;
// }
