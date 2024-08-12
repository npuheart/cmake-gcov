/// @date 2024-08-12
/// @file VtpIO.h
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief
///
///

#pragma once
#include "VtiIO.h"
#include "VtuIO.h"
#include <common/DataDir.h>
#include <filesystem>
namespace IO {

enum class FileType { VTU, VTI };

template <FileType T>
class PvdWriter;

template <>
class PvdWriter<FileType::VTU> {
    std::string _suffix = ".vtu";
    std::string _filename;
    std::string _path     = "";
    std::string _path_pvd = "";

  public:
    PvdWriter(const std::string& filename) : _filename(filename) {
        if (_filename.empty()) { _filename = "data"; }
        ZIRAN::DataDir output_dir{};
        _path = output_dir.absolutePath("output/");
        std::filesystem::path p(_path.c_str());

        // 创建输出路径
        std::filesystem::create_directories(p.parent_path());

        // 构造 pvd 文件的路径
        _path_pvd = _path + filename_pvd();

        // 初始化 pvd 文件
        // 单独给一个函数，initial_pvd_file
        pugi::xml_document xml_doc;
        pugi::xml_node     vtk_node          = xml_doc.append_child("VTKFile");
        vtk_node.append_attribute("type")    = "Collection";
        vtk_node.append_attribute("version") = "0.1";
        vtk_node.append_child("Collection");
        xml_doc.save_file(_path_pvd.c_str(), "  ");
    }

    void write(const double& time, const int& step) {
        write_pvd_file(time, step);
        write_vtk_file(time, step);
    }

    std::string filename_pvd() { return _filename + ".pvd"; }

    std::string filename_vtk(const int counter) {
        std::ostringstream fileid;
        fileid.fill('0');
        fileid.width(6);
        fileid << counter;
        return _filename + fileid.str() + _suffix;
    }

    void write_pvd_file(double time, std::size_t step) {

        pugi::xml_document     xml_doc;
        pugi::xml_parse_result result = xml_doc.load_file(_path_pvd.c_str());
        ASSERT_INFO(result, "Error when reading {}", _path_pvd.c_str());

        // Get Collection node
        pugi::xml_node xml_collections = xml_doc.child("VTKFile").child("Collection");

        // Get filename
        // 获取路径
        std::filesystem::path p(_path + filename_vtk(step));
        spdlog::info("                              pvd path: {}", _path_pvd);
        spdlog::info("function: {}, time: {}, step: {}, path: {}", __func__, time, step, p.string());

        // Append data set
        pugi::xml_node dataset_node               = xml_collections.append_child("DataSet");
        dataset_node.append_attribute("timestep") = time;
        dataset_node.append_attribute("part")     = "0";
        dataset_node.append_attribute("file")     = p.filename().string().c_str();

        // Save file
        xml_doc.save_file(_path_pvd.c_str(), "  ");
    }

    // TODO: 修改成以函数作为参数的函数模板
    void write_vtk_file(double time, std::size_t step) {
        std::filesystem::path p(_path + filename_vtk(step));
        spdlog::info("function: {}, time: {}, step: {}, path: {}", __func__, time, step, p.string());
    }
};

} // namespace IO
