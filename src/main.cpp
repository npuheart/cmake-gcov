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
    mn::ParameterRoot::startup();

    init_logging(argc, argv);

    LOG_INFO("1");
    LOG_WARN("2");
    // LOG_ERROR("2");
    parse_arguments(argc, argv);

    
    // template <typename T> auto 
    //      set_value(const string &key, const T &value) {

    // param::json  = std::make_shared<JsonFile>(config_file);

    // int    N_s   = param::json->get_value<double>("Ns");
    // int    N_bg  = param::json->get_value<double>("Nb");
    // int    Nt    = param::json->get_value<double>("Nt");
    // double T     = param::json->get_value<double>("T");
    // double muf   = param::json->get_value<double>("muf");
    // param::kappa = param::json->get_value<double>("kappa");
    // param::beta  = param::json->get_value<double>("beta");

    // param::t_start_closing = param::json->get_value<double>("t_start_closing");
    // param::dilation_radius = param::json->get_value<double>("dilation_radius");

    // param::posterior_papillary_x = param::json->get_value<double>("posterior_papillary_x");
    // param::posterior_papillary_y = param::json->get_value<double>("posterior_papillary_y");
    // param::posterior_papillary_z = param::json->get_value<double>("posterior_papillary_z");

    // param::anterior_papillary_x = param::json->get_value<double>("anterior_papillary_x");
    // param::anterior_papillary_y = param::json->get_value<double>("anterior_papillary_y");
    // param::anterior_papillary_z = param::json->get_value<double>("anterior_papillary_z");


        // FLAGS::Register v_mu_flag("-v_mu", "v_mu", CaseSettings::v_mu);
        // FLAGS::Register output_folder_flag("-o", "output_folder overwrite", CaseSettings::output_folder);
        // FLAGS::Register dbg_flag("-dbg", "debug mode (0: close 1: open)", HOTSettings::debugMode);
        // FLAGS::Register cneps_flag("-cneps", "epsilon for characteristic norm", HOTSettings::cneps);
        // FLAGS::Register usel_baselinemg_flag("--baseline", "if use baseline multigrid", HOTSettings::useBaselineMultigrid);
        // FLAGS::Register usecn_flag("--usecn", "if use characteristic norm", HOTSettings::useCN);
        // FLAGS::Register use_adaptiveH_flag("--adaptiveH", "if use adaptive hessian", HOTSettings::useAdaptiveHessian);
        // FLAGS::Register matrix_flag("--matfree", "if matrix-free", HOTSettings::matrixFree);
        // FLAGS::Register proj_flag("--project", "if project matrix", HOTSettings::project);

    // const std::string config_file = argv[1];

    // auto json  = std::make_shared<JsonFile>(config_file);
    // int  N_s   = json->get_value<double>("path_output");
    
    // json->printData();
    // LOG_WARN("v_mu: {}", CaseSettings::v_mu)
    // spdlog::info("v_mu: {}", CaseSettings::v_mu);
    // spdlog::info("N_s: {}", N_s);
}



//     auto   arguments = parse_arguments(argc, argv);
//     int    N_s       = arguments["Ns"].as<int>();
//     int    N_bg      = arguments["Nb"].as<int>();
//     int    Nt        = arguments["Nt"].as<int>();
//     double T         = arguments["T"].as<double>();
//     double muf       = arguments["muf"].as<double>();
//     double kappa       = arguments["kappa"].as<double>();
//     double beta       = arguments["beta"].as<double>();


//     // 命令行参数解析
// auto parse_arguments(int argc, char* argv[]) {
//     cxxopts::Options options("fsi_disk_driven", "Command line options");
//     options.add_options()(
//         // 固体步数
//         "Ns", "Number of solid discretization.", cxxopts::value<int>()->default_value("40"))(
//         // 背景网格步数
//         "Nb", "Number of backgrand discretization.", cxxopts::value<int>()->default_value("64"))(
//         // 时间步数
//         "Nt", "Number of time step.", cxxopts::value<int>()->default_value("10000"))(
//         "muf", "流体粘性", cxxopts::value<double>()->default_value("0.04"))(
//         "mus", "固体弹性", cxxopts::value<double>()->default_value("0.1"))(
//         "kappa", "不可压约束", cxxopts::value<double>()->default_value("100000"))(
//         "beta", "固定", cxxopts::value<double>()->default_value("10000000"))(
//         // 最终时刻
//         "T", "Final time step.", cxxopts::value<double>()->default_value("40"))(

//         "h,help", "Show help");

//     auto result = options.parse(argc, argv);
//     if (result.count("help")) {
//         std::cout << options.help() << std::endl;
//         exit(0);
//     }
//     return result;
// }




// #include <ios>
// #include <iostream>
// #include <string>
// #include <memory>
// #include <sstream>
// #include <json/json.h>
// #include "reflect.hpp"


// struct Student {
//     std::string name;
//     int age;
//     int sex;

//     void speak(std::string lang, bool newline) const {
//         if (lang == "cn") {
//             std::cout << "你好！我是" << name << "，今年" << age << "岁，是" << (sex == 1 ? "男": "女") << "生。";
//         } else {
//             std::cout << "Hello! I am " << name << ", " << age << " years old, a " << (sex == 1 ? "boy": "girl") << ".";
//         }
//         if (newline) {
//             std::cout << '\n';
//         }
//     }

//     REFLECT(name, age, sex, speak); // 就地定义
// };


// struct Student2 {
//     std::string name;
//     int age;
//     int sex;
// };
// REFLECT_TYPE(Student2, name, age, sex); // 如果不能修改类的定义


// template <class T, class N>
// struct Baby {
//     N name;
//     T hungry;
// };
// REFLECT_TYPE_TEMPLATED(((Baby<T, N>), class T, class N), name, hungry); // 如果不能修改类的定义，且类是模板

// template <class T>
// std::string jsonSerialize(T &object) {
//     Json::Value root;
//     reflect::foreach_member(object, [&](const char *key, auto &value) {
//         root[key] = value;
//     });
//     Json::StreamWriterBuilder builder;
//     builder["indentation"] = "";
//     std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
//     std::ostringstream os;
//     writer->write(root, &os);
//     return os.str();
// }

// template <class T>
// T jsonDeserialize(std::string const &json) {
//     Json::Value root;
//     Json::Reader reader;
//     reader.parse(json, root);
//     T object;
//     reflect::foreach_member(object, [&](const char *key, auto &value) {
//         value = root[key].as<std::decay_t<decltype(value)>>();
//     });
//     return object;
// }


// int main() {
//     Student stu = {
//         .name = "Peng",
//         .age = 23,
//         .sex = 1,
//     };
//     Student2 stu2 = {
//         .name = "Sir",
//         .age = 23,
//         .sex = 1,
//     };
//     Baby<int, std::string> baby = {
//         .name = "Tom",
//         .hungry = 1,
//     };
//     Baby<float, const char *> baby2 = {
//         .name = "Jerry",
//         .hungry = 2.0f,
//     };

//     std::string bin = jsonSerialize(stu);
//     std::cout << bin << '\n';
//     auto stuDes = jsonDeserialize<Student>(bin);
//     std::cout << stuDes.name << '\n';
//     std::cout << stuDes.age << '\n';
//     std::cout << stuDes.sex << '\n';

//     std::cout << std::boolalpha;
//     std::cout << reflect::get_member<std::string>(stu, "name") << '\n';
//     std::cout << reflect::get_member<int>(stu, "age") << '\n';
//     std::cout << reflect::get_member<int>(stu, "sex") << '\n';
//     std::cout << reflect::has_member<Student>("sex") << '\n';
//     std::cout << reflect::has_member<Student>("sey") << '\n';
//     std::cout << reflect::is_member_type<Student, int>("sex") << '\n';
//     std::cout << reflect::is_member_type<Student, std::string>("sex") << '\n';
//     std::cout << reflect::is_member_type<Student, const int>("sex") << '\n';
//     // reflect::get_function<void(std::string, bool)>(stu, "speak")("cn", true);

//     bin = jsonSerialize(stu);
//     std::cout << bin << '\n';
//     bin = jsonSerialize(baby);
//     std::cout << bin << '\n';
//     bin = jsonSerialize(baby2);
//     std::cout << bin << '\n';

//     return 0;
// }
