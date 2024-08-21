// TODO: duplicated, remove me
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
