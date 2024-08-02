/// @date 2024-08-02
/// @file main.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief main runner
///
///

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <CS/Util/DataDir.h>
#include <MnBase/Math/Vec.h>
#include <MnBase/Object/StructuralAuxiliary.h>



using namespace mn;
int main() {
    ZIRAN::DataDir output_dir{};
    std::string obj_filename = output_dir.absolutePath(ZIRAN::outputFileName("logs/basic-log", ".txt"));

    auto logger = spdlog::basic_logger_mt("basic_logger", obj_filename);

    CompactDomain<uint32_t, 3, 4, 5, 6> cd;
    CompactDomain<uint32_t, 3, 4, 5, 6>::index cd_vec;
    using extends = CompactDomain<uint32_t, 3, 4, 5, 6>::base_t::extends;
    using extends_1 = CompactDomain<uint32_t, 3, 4, 5, 7, 8, 9>::base_t::extends;

    vec_impl<double, std::integer_sequence<uint32_t, 3, 4, 5, 6>> v1;
    vec_impl<double, extends> v2;
    vec_impl<double, extends_1> v3;

    spdlog::info("Extent of v3  : {}", v3.extent);

    spdlog::info("CompactDomain dim : {}", cd.dim);
    spdlog::info("CompactDomain extent : {}", cd.extent);

    spdlog::info("CompactDomain range : {}", cd.range(placeholder::_1));
    spdlog::info("CompactDomain range : {}", cd.range(placeholder::_0));

    spdlog::info("CompactDomain offset : {}", cd.offset(1));
    spdlog::info("CompactDomain offset : {}", cd.offset(1, 0, 0, 0));
    spdlog::info("CompactDomain offset : {}", cd.offset(1, 2));
    spdlog::info("CompactDomain offset : {}", cd.offset(0, 0, 0, 0));
    spdlog::info("CompactDomain offset : {}", cd.offset(0, 0, 0, 1));
    spdlog::info("CompactDomain offset : {}", cd.offset(0, 0, 1, 1));
    spdlog::info("CompactDomain offset : {}", cd.offset(0, 1, 1, 1));
    spdlog::info("CompactDomain offset : {}", cd.offset(1, 1, 1, 1));

    return 0;
}
