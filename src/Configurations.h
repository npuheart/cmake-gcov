/// @date 2024-08-03
/// @file Configurations.h
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief 配置文件
///
///

#include <common/json.h>
#include <common/log.h>
#include <cxxopts.hpp>
#include <map>
#include <variant>
#include <vector>

#include <MnBase/Singleton.h>

class Parameter {
public:
  using _valuetype =
      std::variant<bool, int, double, std::string, std::shared_ptr<Parameter>>;

public:
  auto value(const std::string &key) { return _map[key]; }

  template <typename T> auto set_value(const std::string &key, const T &value) {
    _map[key] = value;
    return _map[key];
  }

  void print(const std::string ident = "    ") {
    for (const auto &[key, value] : _map) {
      if(auto p = std::get_if<std::shared_ptr<Parameter>>(&value)) {
        std::cout << ident << "Key: " << key << std::endl;
        (*p)->print(ident+"    ");
      }

      // if (std::holds_alternative<std::shared_ptr<Parameter>>(value)) {
      //   std::cout << ident << "Key: " << key << std::endl;
      //   auto tmp = std::get<std::shared_ptr<Parameter>>(value);
      //   tmp->print(ident+"    ");

      // } 
      else {

        std::visit(
            [&key, &ident](auto &&arg) {
              std::cout << ident << "Key: " << key << ", Value: " << arg << std::endl;
            },
            value);
      }
    }
  }

  std::string _key;
  std::map<std::string, _valuetype> _map;
};

namespace mn {
struct ParameterRoot : ManagedSingleton<ParameterRoot>, Parameter {};
} // namespace mn

auto parse_arguments(int argc, char *argv[]) {

  cxxopts::Options options("Scene_Loader", "Read simulation scene");
  options.add_options()(
      "f,file", "Scene Configuration File",
      cxxopts::value<std::string>()->default_value("scenes/scene.json"));
  options.add_options()("g,gile", "Generate Something",
                        cxxopts::value<int>()->default_value("0"));
  options.add_options()("h,help", "Show Help");

  auto result = options.parse(argc, argv);
  if (result.count("help")) {
    std::cout << options.help() << std::endl;
    exit(0);
  }
  auto fn = result["file"].as<std::string>();
  spdlog::info("loading scene [{}]\n", fn);
}

namespace CmdArgument {
/// cmd0 for the hard young's modulus, cmd1 for the soft young's modulus
inline static double cmd0 = 0, cmd1 = 0;
} // namespace CmdArgument

namespace CaseSettings {

inline static double v_mu = 0.001;
inline static std::string output_folder;
} // namespace CaseSettings
namespace HOTSettings {
inline static double cgratio = 0.5;
inline static double characterNorm;
inline static double cneps{1e-5};
inline static bool useAdaptiveHessian{false};
inline static bool useCN{false};
inline static bool matrixFree{false}; ///< 0: matrix free, 1: matrix
inline static bool project{false};    ///< project dPdF or not
inline static bool systemBCProject{
    false}; ///< BC project system (matrix & rhs) or not
inline static bool linesearch{false};
inline static int boundaryType{0}; ///< 0: all sticky 1: has slip
inline static int lsolver{
    0}; ///< 0: newton with multigrid solver 1: newton with minres 2: newton
        ///< with cg 3: LBFGS with multigrid 4: direct solver
inline static int Ainv{
    0}; ///< 0: entry 1: block 2: mass (only works with minres)
inline static int smoother{
    0}; ///< 0: (optimal) Jacobi, 1: Optimal Jacobi, 2: PCG, 3: LBFGS-OJ, 4:
        ///< Minres, 5: GS, 6: Chebyshev, 7: Incomplete Cholesky
inline static int coarseSolver{0}; ///< Options same with smoother
inline static int levelCnt{1}, times{1};
inline static int levelscale{0};
inline static int debugMode{0}; ///< open all
inline static double omega{1};
inline static double topomega{0.1};
inline static bool revealJacobi{false};
inline static bool revealVcycle{false};
inline static bool topDownMGS{false};
inline static bool useBaselineMultigrid{false};
} // namespace HOTSettings
