/// @date 2024-08-02
/// @file main.cpp
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief main runner
///
///


#include <cstdio>
#include <iostream>
#include <cuda_runtime.h>

__host__ __device__ void say_hello() {
    printf("Hello, world!\n");
}

__global__ void kernel() {
    say_hello();
}

int main() {
    kernel<<<2, 2>>>();
    cudaDeviceSynchronize();
    say_hello();

    // 检查 kernel 启动的错误
    cudaError_t err = cudaGetLastError();
    if (err != cudaSuccess) {
        std::cerr << "CUDA error: " << cudaGetErrorString(err) << std::endl;
        return -1;
    }

    // 检查 kernel 执行的错误
    err = cudaDeviceSynchronize();
    if (err != cudaSuccess) {
        std::cerr << "CUDA error during synchronization: " << cudaGetErrorString(err) << std::endl;
        return -1;
    }
    return 0;
}
