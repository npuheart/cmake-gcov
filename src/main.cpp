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
}

