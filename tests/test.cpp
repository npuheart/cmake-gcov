/// @date 2024-07-30
/// @file test.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief
///
///

#include "common/common.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("minial CUDA function", "[cuda_common_1]") { REQUIRE(main_cuda() == 0); }

TEST_CASE("minial MPI function", "[mpi_common_1]") { REQUIRE(mpi_main() == 0); }

// 测试模板数组
// using namespace mn;
// int main() {
//     ZIRAN::DataDir output_dir{};
//     std::string obj_filename =
//     output_dir.absolutePath(ZIRAN::outputFileName("logs/basic-log", ".txt"));

//     auto logger = spdlog::basic_logger_mt("basic_logger", obj_filename);

//     CompactDomain<uint32_t, 3, 4, 5, 6> cd;
//     CompactDomain<uint32_t, 3, 4, 5, 6>::index cd_vec;
//     using extends = CompactDomain<uint32_t, 3, 4, 5, 6>::base_t::extends;
//     using extends_1 = CompactDomain<uint32_t, 3, 4, 5, 7, 8,
//     9>::base_t::extends;

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

// #include <spdlog/spdlog.h>
// #include <spdlog/sinks/basic_file_sink.h> // 或者 rotating_file_sink.h

// int main() {
//     // 创建一个输出到文件的sink
//     auto file_sink =
//     std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/my_log.txt",
//     true);
//     // 如果需要滚动日志，可以使用 rotating_file_sink
//     // auto file_sink =
//     std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/my_log.txt",
//     1048576 * 5, 3);

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
