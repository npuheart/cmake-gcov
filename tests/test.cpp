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
#include <catch2/catch_test_macros.hpp> 
// int main(){
//     a();
//     printf("Hello World\n");
//     return 0;
// }

TEST_CASE("create zip", "[create_zip]")  
{  
    Adder adder;
    adder.print_value(std::cout);
    adder.add(5);
    adder.print_value(std::cout);
    adder.add(5);
    adder.print_value(std::cout);
    adder.clear();
    REQUIRE(a(0,1) == 1); 
}

TEST_CASE("create zip2", "[create_zip]")  
{  
    REQUIRE(a(1,0) == 1); 
}