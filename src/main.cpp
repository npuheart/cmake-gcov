/// @date 2024-08-02
/// @file main.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief main runner
///
///
#include<VtuIO.h>
int main(int argc, char* argv[]) {

    std::vector<double>      v1{1, 2, 1};
    std::vector<double>      v2{1, 2, 2};
    std::vector<double>      v3{1, 2, 3};
    std::vector<std::string> tags{"v1", "v2", "v3"};
    writevtu(tags,v1,v2,v3);
    return 0;
}
