/// @date 2024-08-03
/// @file log.h
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief
///
///

#pragma once
#include "config.h"
#include <spdlog/cfg/argv.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#define LOG_ERROR(fmt, ...)                                                    \
  spdlog::error(" {:20}:{:4} | " fmt, __FILE__, __LINE__, ##__VA_ARGS__);      \
  spdlog::shutdown();                                                          \
  throw std::runtime_error("Error of npuheart.");

#define LOG_WARN(fmt, ...)                                                     \
  spdlog::warn(" {:20}:{:4} | " fmt, __FILE__, __LINE__, ##__VA_ARGS__);

#define LOG_INFO(fmt, ...)                                                     \
  spdlog::info(" {:20}:{:4} | " fmt, __FILE__, __LINE__, ##__VA_ARGS__);

void init_logging(int argc, char *argv[]) {

  spdlog::set_level(spdlog::level::info);
  spdlog::cfg::load_argv_levels(argc, argv);

  auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
      CMAKE_LOG_DIR, true);

  if (!CONSOLE_LOG) {
    spdlog::default_logger()->sinks().clear(); // 清除默认的控制台输出sink
  }

  spdlog::default_logger()->sinks().push_back(file_sink);

  // spdlog::set_pattern("%^[%H:%M:%S %H:%M:%S.%e] [%8l]%$ %v");
  // spdlog::info("配置文件为：{}", "config_file");
  // spdlog::warn("配置文件为：{}", "XXXXXXXXX");
  // spdlog::error("Support for floats {:03.2f}", 1.23456);
  // spdlog::critical(
  //     "Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
}