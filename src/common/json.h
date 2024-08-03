/// @date 2024-08-03
/// @file json.h
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief
///
///

#include "log.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

class JsonFile {
public:
  JsonFile(const std::string &filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
      try {
        file >> jsonData;
      } catch (const std::exception &e) {
        spdlog::error("Error parsing JSON: {}", e.what());
      }
      file.close();
    } else {
      spdlog::error("Error opening file: {}", filename);
    }
  }

  void printData() { spdlog::info("JSON Data: {}", jsonData.dump(4)); }

  template <typename T> T get_value(const std::string &key) {
    if (jsonData.find(key) != jsonData.end()) {
      if constexpr (std::is_same_v<T, double>) {
        if (jsonData[key].is_number()) {
          return jsonData[key].get<double>();
        } else {
          LOG_ERROR("键：{} 存在, 但值不是数字", key.c_str());
        }
      }
      if constexpr (std::is_same_v<T, std::string>) {
        if (jsonData[key].is_string()) {
          return jsonData[key].get<std::string>();
        } else { 
          LOG_ERROR("键：{} 存在, 但值不是字符串", key.c_str());
        }
      }
      LOG_ERROR("仅支持 double 和 std::string 类型");
    }
    {
      LOG_ERROR("键不存在：{}", key.c_str());
    }
    return T{}; // 函数不会运行到这里，以下语句只为注明返回类型。
  }

private:
  nlohmann::json jsonData;
};
