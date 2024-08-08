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

void fun(
    const std::string &filename,
    const std::vector<std::string> &tags, 
    const std::vector<std::string> &contens, 
    const std::vector<int> &value_sizes, 
    const std::vector<std::string> &points)
{

}

template <typename... Args>
void writevtu(std::vector<std::string> tags, Args... rest) {
    ASSERT_INFO(sizeof...(Args) == tags.size(), "{} == {}", sizeof...(Args), tags.size());

    const int          num  = sizeof...(Args);
    auto               temp = convert(rest...);
    pugi::xml_document xml_node;
    auto               vtkfile_node          = xml_node.append_child("VTKFile");
    vtkfile_node.append_attribute("type")    = "UnstructuredGrid";
    vtkfile_node.append_attribute("version") = "0.1";
    {

        auto u_node = vtkfile_node.append_child("UnstructuredGrid");
        {
            auto piece = u_node.append_child("Piece");

            piece.append_attribute("NumberOfPoints") = "32"; // 节点数量
            piece.append_attribute("NumberOfCells")  = "0";
            {
                auto node_1     = piece.append_child("Points");
                auto data_array = node_1.append_child("DataArray");

                data_array.append_attribute("type")               = "Float64";
                data_array.append_attribute("NumberOfComponents") = "3";
                data_array.append_attribute("format")             = "ascii";
                data_array.append_child(pugi::node_pcdata).set_value(""); // TODO: 坐标
            }
            {
                auto cells_node                        = piece.append_child("Cells");
                auto dataarray_1                       = cells_node.append_child("DataArray");
                dataarray_1.append_attribute("type")   = "UInt32";
                dataarray_1.append_attribute("Name")   = "connectivity";
                dataarray_1.append_attribute("format") = "ascii";
                dataarray_1.append_child(pugi::node_pcdata).set_value("");
                auto dataarray_2                       = cells_node.append_child("DataArray");
                dataarray_2.append_attribute("type")   = "UInt32";
                dataarray_2.append_attribute("Name")   = "offsets";
                dataarray_2.append_attribute("format") = "ascii";
                dataarray_2.append_child(pugi::node_pcdata).set_value("");
                auto dataarray_3                       = cells_node.append_child("DataArray");
                dataarray_3.append_attribute("type")   = "UInt8";
                dataarray_3.append_attribute("Name")   = "types";
                dataarray_3.append_attribute("format") = "ascii";
                dataarray_3.append_child(pugi::node_pcdata).set_value("");
            }

            auto point_data                        = piece.append_child("PointData");
            point_data.append_attribute("Vectors") = tags[0].c_str();
            for (size_t i = 0; i < num; i++) {
                spdlog::info(" {}: {}", tags[i], temp[i]);
                auto data_array = point_data.append_child("DataArray");

                data_array.append_attribute("type")               = "Float64";
                data_array.append_attribute("Name")               = "displacement";
                data_array.append_attribute("NumberOfComponents") = "3";
                data_array.append_attribute("format")             = "ascii";
                data_array.append_child(pugi::node_pcdata).set_value(temp[i].c_str());
            }
        }
    }
    xml_node.save_file("a.vtu");
}
