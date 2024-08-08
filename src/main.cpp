/// @date 2024-08-02
/// @file main.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief main runner
///
///
#include <common/log.h>
#include <pugixml.hpp>

template <typename T>
std::string sum(T value) {
    std::stringstream  sstream;
    sstream << value;
    return sstream.str();
}

template <typename T, typename... Args>
std::string sum(T first, Args... rest) {
    std::stringstream  sstream;
    sstream << first << " " << sum(rest...) ;
    return sstream.str();
}

//     // sstream << 0 << " " << dim.x - 1 << " " << 0 << " " << dim.y - 1 << " " << 0 << " " << dim.z - 1;
//     std::string _1 = sstream.str();
//     return (args + ...);

int main(int argc, char* argv[]) {
    spdlog::info("sum: {}", sum(1, 2, 3, 4, 5));
    pugi::xml_document xml_node;
    pugi::xml_node     vtkfile_node = xml_node.append_child("VTKFile");
    vtkfile_node.append_attribute("type") = "aa";
    vtkfile_node.append_child(pugi::node_pcdata).set_value(sum(1, 2, 3, 4, 5).c_str());
    xml_node.save_file("a.vtu");

    return 0;
}
