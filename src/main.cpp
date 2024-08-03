/// @date 2024-08-02
/// @file main.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief main runner
///
///
#include <Configurations.h>
#include <common/json.h>
#include <common/log.h>

int main(int argc, char* argv[]) {

    init_logging(argc, argv);

    LOG_INFO("1");
    LOG_WARN("2");
    // LOG_ERROR("2");


    const std::string config_file = argv[1];

    auto json  = std::make_shared<JsonFile>(config_file);
    int  N_s   = json->get_value<double>("path_output");
    
    json->printData();
    LOG_WARN("v_mu: {}", CaseSettings::v_mu)
    spdlog::info("v_mu: {}", CaseSettings::v_mu);
    spdlog::info("N_s: {}", N_s);
}

