/// @date 2024-08-02
/// @file main.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
/// 
/// @brief main runner
/// 
///


#include <VtkIO.h>
#include <CS/Util/DataDir.h>

int main() {
    ZIRAN::DataDir output_dir{};
    std::string obj_filename = output_dir.absolutePath(ZIRAN::outputFileName("partio", ".vtk"));

    // 示例数据：一个包含几个三维点的 std::vector
    std::vector<std::array<double, 3>> points = {
        {0.0, 0.0, 0.0},
        {1.0, 0.0, 0.0},
        {1.0, 1.0, 0.0},
        {0.0, 1.2, 0.0},
        {0.0, 1.3, 0.0},
        {0.0, 1.4, 0.0},
        {0.0, 1.5, 0.0},
        {0.5, 0.5, 1.0}
    };
    writePositionVectorToVtk(obj_filename,points);
    return 0;
}





// int main() {
//     Adder adder;
//     adder.print_value(std::cout);
//     adder.add(5);
//     adder.print_value(std::cout);
//     adder.add(5);
//     adder.print_value(std::cout);
//     adder.clear();

//     // StdVector<Eigen::EigenTV> samples;
//     // std::string filename = "test.bgeo";
//     // writePositionVectorToPartio(filename, samples);
//     pugi::xml_document doc;
//     pugi::xml_parse_result result = doc.load_file("xgconsole.xml");
//     if (!result)
//         return -1;
        
//     for (pugi::xml_node tool: doc.child("Profile").child("Tools").children("Tool"))
//     {
//         int timeout = tool.attribute("Timeout").as_int();
        
//         if (timeout > 0)
//             std::cout << "Tool " << tool.attribute("Filename").value() << " has timeout " << timeout << "\n";
//     }
//     return 0;
// }
