/// @date 2024-08-03
/// @file Configurations.h
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief 配置文件
///
///

// 使用方法
// auto param = ParameterRoot::get_instance();
// // TODO: 简便读取
// // auto fov = param["from_file"]["camera"]["fov"];
// auto from_file = std::get<std::shared_ptr<Parameter>>(param->value("from_file"));
// auto camera    = std::get<std::shared_ptr<Parameter>>(from_file->value("camera"));
// auto fov = std::get<double>(camera->value("fov"));  
// spdlog::info("fov: {}", fov);


#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <variant>
#include <vector>

#include <MnBase/Singleton.h>
#include <common/FileSystem.h>
#include <nlohmann/json.hpp>

#include <common/json.h>
#include <common/log.h>
#include <cxxopts.hpp>



class Parameter {
  public:
    using _valuetype = std::variant<bool, int, double, std::string, std::vector<double>, std::shared_ptr<Parameter>>;
    using _functype  = std::function<void(const std::string&, const _valuetype&, const std::string&)>;

  public:
    const _valuetype& value(const std::string& key) const { return _map.at(key); }

    template <typename T>
    auto set_value(const std::string& key, const T& value) {
        _map[key] = value;
        return _map[key];
    }

    void for_each(const _functype& func, const std::string& tag) const {
        for (const auto& [key, value] : _map) {
            if (auto p = std::get_if<std::shared_ptr<Parameter>>(&value)) {
                func(key, value, tag);
                (*p)->for_each(func, tag + "    ");
            } else {
                func(key, value, tag);
            }
        }
    }

    std::string                       _name;
    std::map<std::string, _valuetype> _map;
};

struct ParameterRoot : mn::ManagedSingleton<ParameterRoot>, Parameter {};

// NOTE: 目前只能读取 std::string 和 double 类型的数据( int 会被转换成 double )
void json_to_param(const nlohmann::json& jsonData, Parameter& param){
    for (auto& [key, value] : jsonData.items()) {
        if (jsonData.at(key).is_number()) {
            param.set_value(key, jsonData.at(key).get<double>());
        } else if (jsonData.at(key).is_string()) {
            param.set_value(key, jsonData.at(key).get<std::string>());
        } else if (jsonData.at(key).is_object()) { // 访问嵌套的对象
            auto subparam = std::make_shared<Parameter>();
            param.set_value(key, subparam);
            json_to_param(jsonData.at(key), *subparam);
        } else if (jsonData.at(key).is_array()) {
            // 遍历 JSON 数组，并将每个元素存储到 vector 中
            std::vector<double> values;
            auto jsonArray = jsonData.at(key);
            for (const auto& element : jsonArray) {
                if (element.is_number()){
                    values.push_back(element.get<double>());
                } else {
                    spdlog::warn("不支持数字以外类型的数组: {}", key);
                }
            }
            param.set_value(key, values);
        } 
        else {
            spdlog::warn("Skip item: {}", key);
        }
    }
}

void parse_json_file() {

    auto param_root = ParameterRoot::get_instance();
    auto filename   = std::get<std::string>(param_root->value("file"));

    std::ostringstream oss;
    ZIRAN::FILESYSTEM::readFile(oss, filename);
    std::string    fileContents = oss.str();
    nlohmann::json jsonData     = nlohmann::json::parse(fileContents);

    // jsonData, param_root
    auto param_from_file = std::make_shared<Parameter>();
    param_root->set_value("from_file", param_from_file);


    json_to_param(jsonData, *param_from_file);

    auto func = [](const std::string& key, const Parameter::_valuetype& value, const std::string& tag) {
        if (auto p = std::get_if<std::shared_ptr<Parameter>>(&value)) {
            spdlog::info("{}{} :", tag, key);
        } else if (auto p = std::get_if<bool>(&value)) {
            spdlog::info("{}{}: {}", tag, key, *p);
        } else if (auto p = std::get_if<int>(&value)) {
            spdlog::info("{}{}: {}", tag, key, *p);
        } else if (auto p = std::get_if<double>(&value)) {
            spdlog::info("{}{}: {}", tag, key, *p);
        } else if (auto p = std::get_if<std::string>(&value)) {
            spdlog::info("{}{}: {}", tag, key, *p);
        } else if (auto p = std::get_if<std::vector<double>>(&value)) {
            spdlog::info("{}{}:", tag, key);
            for (const auto& v : *p) {
                spdlog::info("{}    {}",tag, v);
            }
        } else {
            spdlog::error("Parameter type not supported");
        }
    };
    param_root->for_each(func, "");
}

auto parse_arguments(int argc, char* argv[]) {

    cxxopts::Options options("Scene_Loader", "Read simulation scene");
    options.add_options()("f,file", "Scene Configuration File",
                          cxxopts::value<std::string>()->default_value("../data/scene.json"));
    options.add_options()("g,gile", "Generate Something", cxxopts::value<int>()->default_value("0"));
    options.add_options()("h,help", "Show Help");

    // 打印帮助
    auto result = options.parse(argc, argv);
    if (result.count("help")) {
        spdlog::info("{}", options.help());
        exit(0);
    }

    // 将参数读入参数单例(ParameterRoot)
    auto param_root = ParameterRoot::get_instance();
    param_root->set_value("file", result["file"].as<std::string>());
    param_root->set_value("gile", result["gile"].as<int>());

    // 解析配置文件中的参数
    parse_json_file();
}



