/// @date 2024-08-03
/// @file main.cu
/// @author Ma Pengfei (code@pengfeima.cn)
/// @version 0.1
/// @copyright Copyright (c) 2024 Ma Pengfei
///
/// @brief
///
///

#include <MnSystem/Cuda/HostUtils.hpp>
#include <cstdio>
#include <cuda_runtime.h>

using namespace mn;

__host__ __device__ void say_hello() { printf("Hello, world!\n"); }

__global__ void kernel() { say_hello(); }

void print_devices() {
    int         deviceCount = 0;
    cudaError_t status      = cudaGetDeviceCount(&deviceCount);

    if (status != cudaSuccess) {
        std::cerr << "Error: cudaGetDeviceCount failed with error code " << status << std::endl;
    }

    for (int device = 0; device < deviceCount; ++device) {
        cudaDeviceProp deviceProp;
        status = cudaGetDeviceProperties(&deviceProp, device);

        if (status != cudaSuccess) {
            std::cerr << "Error: cudaGetDeviceProperties failed for device " << device << " with error code " << status
                      << std::endl;
            continue;
        }

        std::cout << "Device " << device << ": " << deviceProp.name << std::endl;
        std::cout << "  Compute capability: " << deviceProp.major << "." << deviceProp.minor << std::endl;
        std::cout << "  Total global memory: " << deviceProp.totalGlobalMem / (1024 * 1024) << " MB" << std::endl;
        std::cout << "  Multiprocessors: " << deviceProp.multiProcessorCount << std::endl;
        std::cout << "  Max threads per block: " << deviceProp.maxThreadsPerBlock << std::endl;
        std::cout << "  Max threads per multiprocessor: " << deviceProp.maxThreadsPerMultiProcessor << std::endl;
        std::cout << "  Warp size: " << deviceProp.warpSize << std::endl;
        std::cout << "  Max grid size: [" << deviceProp.maxGridSize[0] << ", " << deviceProp.maxGridSize[1] << ", "
                  << deviceProp.maxGridSize[2] << "]" << std::endl;
        std::cout << "  Max block size: [" << deviceProp.maxThreadsDim[0] << ", " << deviceProp.maxThreadsDim[1] << ", "
                  << deviceProp.maxThreadsDim[2] << "]" << std::endl;
        std::cout << std::endl;
    }
}
int main_cuda() {
    // mn::Cuda::startup();
    kernel<<<2, 2>>>();
    cudaDeviceSynchronize();
    check_cuda_errors(cudaSetDevice(1));
    get_last_cuda_error("上一个错误");
    say_hello();
    print_devices();
    return 0;
}