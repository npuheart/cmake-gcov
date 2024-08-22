//// @date 2024-07-22
/// @file main.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief
///
///
#include <common/log/timer.h>
#include <thread>
int main_poisson(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    {
        main_poisson(argc, argv);
        Timer timer("main_poisson");
    }

    {
        Timer timer("aaa");
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
    {
        Timer timer(__PRETTY_FUNCTION__);
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }

    {
        FUNCTION_TIMER;
        Timer timer_1("bbb");
        std::this_thread::sleep_for(std::chrono::microseconds(200));
    }

    TimeLogger::instance().print_timing();
    TimeLogger::instance().print_statistics();
    return 0;
}