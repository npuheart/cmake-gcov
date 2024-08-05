/// @date 2024-08-05
/// @file TmpSimulation.h
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
/// 
/// @brief 
/// 
///



#pragma once

#include <MPM/SimulationBase.h>


template <class T, int _dim>
class TmpSimulation: public ZIRAN::SimulationBase
{
public:
    static const int dim = _dim;

    bool useDouble() override { return std::is_same<T, double>::value; }
    int dimension() override { return dim; }
    const char* name() override { return "tmp_base"; }

    void advanceOneTimeStep(double dt) override {}
    void writeState(std::ostream&) override {}
    void readState(std::istream&) override {}
};


