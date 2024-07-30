cmake_minimum_required(VERSION 3.18)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set the cmake options
option(ENABLE_TESTS "Build the test" ON)
option(ENABLE_COVERAGE "Generate coverage report" ON)

# Set the compiler options
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
# set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake;${CMAKE_MODULE_PATH}")
if (ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "-fprofile-arcs -ftest-coverage") # 
endif ()

# print messages
message(STATUS ENABLE_COVERAGE=${ENABLE_COVERAGE})
message(STATUS ENABLE_TESTS=${ENABLE_TESTS})






project(CMake_GCov CXX)

add_subdirectory(src)  



# Create the executable (唯一的主程序)
add_executable(main src/main.cpp)
target_link_libraries(main ${PROJECT_NAME}_dev)







# Enable testing
if (ENABLE_TESTS)
	# 启用测试
    enable_testing()  
    add_subdirectory(tests)  
endif ()
