/// @date 2024-07-30
/// @file test.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief
///
///
#include <iostream>
#include <Apple/lib.h>
#include <Adder.h>
#include "test.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("create zip", "[create_zip]")
{
    Adder adder;
    adder.print_value(std::cout);
    adder.add(5);
    adder.print_value(std::cout);
    adder.add(5);
    adder.print_value(std::cout);
    adder.clear();
    REQUIRE(a(0, 1) == 1);
}

TEST_CASE("cuda minial function", "[cuda_common_1]")
{
    main_cuda();
}


// 测试模板数组
// using namespace mn;
// int main() {
//     ZIRAN::DataDir output_dir{};
//     std::string obj_filename = output_dir.absolutePath(ZIRAN::outputFileName("logs/basic-log", ".txt"));

//     auto logger = spdlog::basic_logger_mt("basic_logger", obj_filename);

//     CompactDomain<uint32_t, 3, 4, 5, 6> cd;
//     CompactDomain<uint32_t, 3, 4, 5, 6>::index cd_vec;
//     using extends = CompactDomain<uint32_t, 3, 4, 5, 6>::base_t::extends;
//     using extends_1 = CompactDomain<uint32_t, 3, 4, 5, 7, 8, 9>::base_t::extends;

//     vec_impl<double, std::integer_sequence<uint32_t, 3, 4, 5, 6>> v1;
//     vec_impl<double, extends> v2;
//     vec_impl<double, extends_1> v3;

//     spdlog::info("Extent of v3  : {}", v3.extent);

//     spdlog::info("CompactDomain dim : {}", cd.dim);
//     spdlog::info("CompactDomain extent : {}", cd.extent);

//     spdlog::info("CompactDomain range : {}", cd.range(placeholder::_1));
//     spdlog::info("CompactDomain range : {}", cd.range(placeholder::_0));

//     spdlog::info("CompactDomain offset : {}", cd.offset(1));
//     spdlog::info("CompactDomain offset : {}", cd.offset(1, 0, 0, 0));
//     spdlog::info("CompactDomain offset : {}", cd.offset(1, 2));
//     spdlog::info("CompactDomain offset : {}", cd.offset(0, 0, 0, 0));
//     spdlog::info("CompactDomain offset : {}", cd.offset(0, 0, 0, 1));
//     spdlog::info("CompactDomain offset : {}", cd.offset(0, 0, 1, 1));
//     spdlog::info("CompactDomain offset : {}", cd.offset(0, 1, 1, 1));
//     spdlog::info("CompactDomain offset : {}", cd.offset(1, 1, 1, 1));

//     return 0;
// }


// Author: Wes Kendall
// Copyright 2011 www.mpitutorial.com
// This code is provided freely with the tutorials on mpitutorial.com. Feel
// free to modify it for your own use. Any distribution of the code must
// either provide a link to www.mpitutorial.com or keep this header intact.
//
// Example using MPI_Send and MPI_Recv to pass a message around in a ring.
//
// #include <mpi.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <spdlog/spdlog.h>

// int main(int argc, char** argv) {
//     // Initialize the MPI environment
//     MPI_Init(NULL, NULL);
//     // Find out rank, size
//     int world_rank;
//     MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
//     int world_size;
//     MPI_Comm_size(MPI_COMM_WORLD, &world_size);

//     int token;
//     // Receive from the lower process and send to the higher process. Take care
//     // of the special case when you are the first process to prevent deadlock.
//     if (world_rank != 0) {
//         MPI_Recv(&token, 1, MPI_INT, world_rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//         spdlog::info("Process {0} received token {1} from process {2}", world_rank, token, world_rank - 1);
//     } else {
//         // Set the token's value if you are process 0
//         token = -1;
//     }
//     token++;

//     MPI_Send(&token, 1, MPI_INT, (world_rank + 1) % world_size, 0, MPI_COMM_WORLD);
//     // Now process 0 can receive from the last process. This makes sure that at
//     // least one MPI_Send is initialized before all MPI_Recvs (again, to prevent
//     // deadlock)
//     if (world_rank == 0) {
//         MPI_Recv(&token, 1, MPI_INT, world_size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
//         spdlog::info("Process {0} received token {1} from process {2}", world_rank, token, world_size - 1);
//     }
//     MPI_Finalize();
// }




// #include <spdlog/spdlog.h>
// #include <spdlog/sinks/basic_file_sink.h> // 或者 rotating_file_sink.h

// int main() {
//     // 创建一个输出到文件的sink
//     auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/my_log.txt", true);
//     // 如果需要滚动日志，可以使用 rotating_file_sink
//     // auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/my_log.txt", 1048576 * 5, 3);

//     // 将默认日志记录器设置为输出到文件
//     // spdlog::default_logger()->sinks().clear(); // 清除默认的控制台输出sink
//     spdlog::default_logger()->sinks().push_back(file_sink);

//     // 设置日志格式和级别（可选）
//     // spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%L%$] %v");
//     spdlog::set_level(spdlog::level::info);

//     // 使用 spdlog 直接输出日志
//     spdlog::info("This is an info message");
//     spdlog::warn("This is a warning message");
//     spdlog::error("This is an error message");

//     // 刷新并关闭spdlog
//     spdlog::shutdown();
//     return 0;
// }
