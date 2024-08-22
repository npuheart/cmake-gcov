cmake_minimum_required(VERSION 3.27)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

string(ASCII 27 ESC)
set(COLOR_RESET "${ESC}[0m")
set(COLOR_BLUE "${ESC}[34m")
set(COLOR_RED "${ESC}[31m")
set(COLOR_GREEN "${ESC}[32m")
set(COLOR_YELLOW "${ESC}[33m")

# Set the cmake options
option(ENABLE_TESTS "Build the tests" OFF)
option(ENABLE_COVERAGE "Generate coverage reports" OFF)
option(BUILD_KOKKOS_LIB "Enable kokkos lib" ON)
option(ENABLE_SANITIZER "Enable sanitizer to detect illegal I/O on memory" ON)

# Set the compiler options
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake;${CMAKE_MODULE_PATH}")
set(CMAKE_CUDA_ARCHITECTURES 89)

if (ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage") # 
endif ()

if (ENABLE_SANITIZER)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
    # message(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif ()

# print messages of settings
message(STATUS "${COLOR_BLUE}ENABLE_COVERAGE=${ENABLE_COVERAGE}${COLOR_RESET}")
message(STATUS "${COLOR_BLUE}ENABLE_TESTS=${ENABLE_TESTS}${COLOR_RESET}")
message(STATUS "${COLOR_BLUE}BUILD_KOKKOS_LIB=${BUILD_KOKKOS_LIB}${COLOR_RESET}")
message(STATUS "${COLOR_BLUE}CMAKE_CUDA_ARCHITECTURES=${CMAKE_CUDA_ARCHITECTURES}${COLOR_RESET}")
#####################################################################
################# Set the project (项目开始) #########################
#####################################################################
project(npuheart C CXX CUDA)

# 主要源码
add_subdirectory(src)  

# Create the executable (唯一的主程序)
add_executable(${PROJECT_NAME}_main src/main.cu src/main.cpp)
target_link_libraries(${PROJECT_NAME}_main ${PROJECT_NAME}_dev)

# Enable testing
if (ENABLE_TESTS)
	# 启用测试
    enable_testing()  
    add_subdirectory(tests)  
endif ()
