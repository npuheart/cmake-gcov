/// @date 2024-07-30
/// @file Adder.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
/// 
/// @brief 
/// 
///

#include <iostream>
#include "Adder.h"

Adder::Adder() : _value(0) {};

void Adder::add(uint32_t x)
{
    _value += x;
}
void Adder::clear()
{
    _value = 0;
}

void Adder::print_value(std::ostream &out)
{
    using namespace std;
    out << "Current value: " << _value << endl;
}
