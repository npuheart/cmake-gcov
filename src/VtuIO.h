/// @date 2024-08-08
/// @file VtuIO.h
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
/// 
/// @brief 
/// 
///
#include <common/log.h>
#include <pugixml.hpp>
#include <vector>

// 将一个vector转换成字符串
std::vector<std::string> convert(std::vector<double> first) {
    std::vector<std::string> result;
    std::stringstream        sstream;
    for (auto i : first)
        sstream << i << " ";
    result.push_back(sstream.str());
    return result;
}

template <typename T, typename... Args>
std::vector<std::string> convert(T first, Args... rest) {
    std::vector<std::string> temp1 = convert(first);
    std::vector<std::string> temp2 = convert(rest...);
    std::vector<std::string> temp;
    for (auto i : temp1)
        temp.push_back(i);
    for (auto i : temp2)
        temp.push_back(i);
    return temp;
}

template <typename... Args>
void writevtu(std::vector<std::string> tags, Args... rest){
    const int num = sizeof...(Args);
    auto temp = convert(rest...);
    pugi::xml_document xml_node;
    // sizeof...(Args) == tags.size();
    for (size_t i = 0; i < num; i++) {
        spdlog::info(" {}: {}", tags[i], temp[i]);
        pugi::xml_node vtkfile_node             = xml_node.append_child("VTKFile");
        vtkfile_node.append_attribute("number") = i;
        vtkfile_node.append_attribute("tag")    = tags[i].c_str();
        vtkfile_node.append_child(pugi::node_pcdata).set_value(temp[i].c_str());
    }
    xml_node.save_file("a.vtu");
}
