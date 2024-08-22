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

int main() {
    { Timer timer("aaa"); }
    { Timer timer(__PRETTY_FUNCTION__); }
    
    {FUNCTION_TIMER;}

    TimeLogger::instance().print_timing();
    return 0;
}