/// @date 2024-07-30
/// @file Adder.h
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief
///
///

#pragma once

#include <iostream>
#include <cstdint>
#include <Partio.h>

class Adder
{
private:
    uint32_t _value;

public:
    Adder();

    void add(uint32_t x);

    void clear();

    void print_value(std::ostream &out);
};
