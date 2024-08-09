/// @date 2024-08-02
/// @file VtkIO.h
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
/// 
/// @brief 
/// 
///

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <spdlog/spdlog.h>



template <template <typename> class Vector, class Array>
void writePositionVectorToVtk(const std::string& particleFile,
    const Vector<Array>& points){
    
    // 打开文件以进行写入
    std::ofstream vtkFile(particleFile);

    // 检查文件是否成功打开
    if (!vtkFile.is_open()) {
        // CHECK_FALSE
        spdlog::error("Unable to open {} for writing.", particleFile);
    }

    // 写入 VTK 文件头部
    vtkFile << "# vtk DataFile Version 3.0\n";
    vtkFile << "Example VTK file\n";
    vtkFile << "ASCII\n";
    vtkFile << "DATASET POLYDATA\n";

    // 写入点数和点数据
    vtkFile << "POINTS "<<points.size()<<" float\n";
    for (const auto& point : points) {
        vtkFile << point[0] << " " << point[1] << " " << point[2] << "\n";
    }

    // 关闭文件
    vtkFile.close();
    spdlog::info("VTK file {} created successfully.", particleFile);
}



// int main() {
//     ZIRAN::DataDir output_dir{};
//     std::string obj_filename = output_dir.absolutePath(outputFileName("partio", ".vtk"));

//     // 示例数据：一个包含几个三维点的 std::vector
//     std::vector<std::array<double, 3>> points = {
//         {0.0, 0.0, 0.0},
//         {1.0, 0.0, 0.0},
//         {1.0, 1.0, 0.0},
//         {0.0, 1.2, 0.0},
//         {0.0, 1.3, 0.0},
//         {0.0, 1.4, 0.0},
//         {0.0, 1.5, 0.0},
//         {0.5, 0.5, 1.0}
//     };
//     writePositionVectorToVtk(obj_filename,points);
//     return 0;
// }