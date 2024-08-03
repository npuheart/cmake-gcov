/// @date 2024-08-03
/// @file main.cu
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
/// 
/// @brief 
/// 
///

#include <cstdio>
#include <cuda_runtime.h>
#include <MnSystem/Cuda/HostUtils.hpp>

using namespace mn;

__host__ __device__ void say_hello() {
    printf("Hello, world!\n");
}

__global__ void kernel() {
    say_hello();
}

int main_cuda() {
    kernel<<<2, 2>>>();
    cudaDeviceSynchronize();
    check_cuda_errors(cudaSetDevice(1));
    get_last_cuda_error("上一个错误");
    say_hello();
    return 0;
}