//// @date 2024-07-22
/// @file main.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief
///
///

#include<common/memory/MemoryAllocator.h>

struct MemResource
{
    union
    {
        void *ptr;
        uintptr_t ptrval;
        uint64_t offset; ///< only legal for 64-bit app
    };
};
// *reinterpret_cast<Type*>(handle.ptrval)
struct Data
{
    MemResource handle;
    size_t size = 16;
    // memory manage
    template <typename Allocator>
    void allocate_handle(Allocator allocator)
    {
        if (size != 0)
        {
            handle.ptr = allocator.allocate(size);
        }
        else
        {
            handle.ptr = nullptr;
        }
    }
};

int main()
{
    Data data;
    data.allocate_handle(HeapAllocator{});
    auto data_ptr = reinterpret_cast<int *>(data.handle.ptr);
    for (size_t i = 0; i < data.size/sizeof(int)+100; i++)
    {
        data_ptr[i] = i;
        printf("%d\n", data_ptr[i]);
    }
    
    printf("Hello, World!%d\n", data.size/sizeof(int));

    return 0;
}