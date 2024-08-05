/// @date 2024-08-02
/// @file main.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief main runner
///
///
#include <common/Parameters.h>
#include <MPM/TmpSimulation.h>


// 一个类，包含
//             cxxopts::Options options
//             nlohmann::json json

int main(int argc, char* argv[]) {
    ParameterRoot::startup();

    init_logging(argc, argv);

    LOG_INFO("1");
    LOG_WARN("2");
    // LOG_ERROR("2");
    parse_arguments(argc, argv);
    auto param = ParameterRoot::get_instance();

    // TODO: 简便读取
    // auto fov = param["from_file"]["camera"]["fov"];
    auto from_file = std::get<std::shared_ptr<Parameter>>(param->value("from_file"));
    auto camera    = std::get<std::shared_ptr<Parameter>>(from_file->value("camera"));
    auto fov = std::get<double>(camera->value("fov"));  
    
    spdlog::info("fov: {}", fov);

    
    TmpSimulation<double, 3> sim;

    sim.simulate();

    return 0;
}

