
# 添加子项目
add_subdirectory(Apple)
add_subdirectory(Depends)
add_subdirectory(Mn)
add_subdirectory(SPGrid)
add_subdirectory(libkokkos)

# Create the library (创建库)
add_library(${PROJECT_NAME}_dev OBJECT Adder.cpp)
target_include_directories(${PROJECT_NAME}_dev PUBLIC ".")

# 链接子项目
target_link_libraries(${PROJECT_NAME}_dev PUBLIC Apple mncuda spgrid)
target_link_libraries(${PROJECT_NAME}_dev PUBLIC tbb partio pugixml Tick)

find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME}_dev PUBLIC spdlog::spdlog)

find_package(Eigen3 REQUIRED)
add_library(eigen INTERFACE IMPORTED)
target_include_directories(${PROJECT_NAME}_dev SYSTEM PUBLIC ${EIGEN3_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}_dev PUBLIC eigen)

find_package(MPI REQUIRED)
target_include_directories(${PROJECT_NAME}_dev PUBLIC ${MPI_INCLUDE_PATH})
target_link_libraries(${PROJECT_NAME}_dev PUBLIC ${MPI_CXX_LIBRARIES})

find_package(nlohmann_json REQUIRED)
target_link_libraries(${PROJECT_NAME}_dev PUBLIC  nlohmann_json::nlohmann_json)

# NOTE: 含有kokkos的代码需要独立编译，然后最为库导入
set(KOKKOS_LIB_NAME kokkos_lib)
set(KOKKOS_LIB_PATH "${CMAKE_SOURCE_DIR}/src/libkokkos")
if(BUILD_KOKKOS_LIB)
   # 定义自定义命令以生成共享库
    add_custom_command(
        OUTPUT "${KOKKOS_LIB_NAME}_lib"
        COMMAND cmake -B "${CMAKE_BINARY_DIR}/${KOKKOS_LIB_NAME}" -S . -DKOKKOS_LIB_NAME="${KOKKOS_LIB_NAME}" 
        COMMAND cmake --build "${CMAKE_BINARY_DIR}/${KOKKOS_LIB_NAME}"
        WORKING_DIRECTORY "${KOKKOS_LIB_PATH}"
        COMMENT "Generating shared library ${KOKKOS_LIB_NAME}"
    )
    # 添加依赖关系：确保自定义命令在创建目标之前执行
    add_custom_target(${KOKKOS_LIB_NAME}_build ALL
        DEPENDS "${KOKKOS_LIB_NAME}_lib"
    )
endif()

add_library(${KOKKOS_LIB_NAME} SHARED IMPORTED GLOBAL)
set_target_properties(${KOKKOS_LIB_NAME} PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${KOKKOS_LIB_PATH}/include"
  IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/${KOKKOS_LIB_NAME}/lib/lib${KOKKOS_LIB_NAME}.so"
)

add_dependencies(${KOKKOS_LIB_NAME} ${KOKKOS_LIB_NAME}_build)
target_link_libraries(${PROJECT_NAME}_dev PUBLIC ${KOKKOS_LIB_NAME})

# 生成配置文件
set(${PROJECT_NAME}_DATA_DIR ${CMAKE_SOURCE_DIR}/data)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/common/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/common/config.h)

message(STATUS "${COLOR_BLUE}${KOKKOS_LIB_NAME}_include: ${KOKKOS_LIB_PATH}/include${COLOR_RESET}")
message(STATUS "${COLOR_BLUE}${KOKKOS_LIB_NAME}_lib:     ${CMAKE_BINARY_DIR}/${KOKKOS_LIB_NAME}/lib/lib${KOKKOS_LIB_NAME}.so${COLOR_RESET}")
message(STATUS "${COLOR_BLUE}${PROJECT_NAME}_DATA_DIR:  ${${PROJECT_NAME}_DATA_DIR}${COLOR_RESET}")


# 添加编译参数
target_compile_definitions(${PROJECT_NAME}_dev PUBLIC USE_CUDA_COMPILER)
target_compile_options(${PROJECT_NAME}_dev PRIVATE -Wall -Wextra -Werror=return-type)
