/// @date 2024-08-14
/// @file Singleton.h
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief
///
///
#pragma once

/*
 *	@note	Singleton
 */
// T must be: no-throw default constructible and no-throw destructible
template <typename T>
struct Singleton
{
public:
    static T &instance()
    {
        static T instance{};
        return instance;
    }
};
