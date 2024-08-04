/// @date 2024-08-03
/// @file Configurations.h
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief 配置文件
///
///

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
    using _valuetype = std::variant<bool, int, double, std::string, std::shared_ptr<Parameter>>;
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

    // spdlog::info("file: {}", file);

    // auto json = std::make_shared<JsonFile>(file);
    // // json->for_each();
    // int N_s = json->get_value<double>("path_output");
    // json->printData();

    // auto param_linear_solver = std::make_shared<Parameter>();
    // auto param_newton_solver = std::make_shared<Parameter>();
    // auto param_line_search   = std::make_shared<Parameter>();

    // param_linear_solver->set_value("tolerance", 0.001);
    // param_newton_solver->set_value("black", true);
    // param_newton_solver->set_value("black", 1);
    // param_newton_solver->set_value("line_search", param_line_search);
    // param_line_search->set_value("step", 0.3);

    // param_root->set_value("linear_solver", param_linear_solver);
    // param_root->set_value("newton_solver", param_newton_solver);
    // param_root->set_value("haha", 0.2);

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
        } else {
            spdlog::error("Parameter type not supported");
        }
    };
    param_root->for_each(func, "");
}

auto parse_arguments(int argc, char* argv[]) {

    cxxopts::Options options("Scene_Loader", "Read simulation scene");
    options.add_options()("f,file", "Scene Configuration File",
                          cxxopts::value<std::string>()->default_value("scenes/scene.json"));
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
