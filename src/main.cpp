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
#include <MPM/MpmGrid.h>


// 一个类，包含
//             cxxopts::Options options
//             nlohmann::json json

int main(int argc, char* argv[]) {

    ParameterRoot::startup();
    init_logging(argc, argv);
    parse_arguments(argc, argv);
    ZIRAN::MpmGrid<double, 3> grid;
    TmpSimulation<double, 3> sim;
    
    sim.end_frame = 100;
    sim.simulate();
    return 0;
}

