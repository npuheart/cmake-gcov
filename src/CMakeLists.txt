
# 添加子项目
add_subdirectory(Apple)
add_subdirectory(Depends)

# Create the library (创建库)
add_library(${PROJECT_NAME}_dev OBJECT Adder.cpp)
target_include_directories(${PROJECT_NAME}_dev PUBLIC ".")

# 链接子项目
target_link_libraries(${PROJECT_NAME}_dev PUBLIC Apple)
target_link_libraries(${PROJECT_NAME}_dev PUBLIC tbb partio pugixml)

find_package(spdlog REQUIRED)
target_link_libraries(${PROJECT_NAME}_dev PRIVATE spdlog::spdlog)

find_package(Eigen3 REQUIRED)
add_library(eigen INTERFACE IMPORTED)
target_include_directories(${PROJECT_NAME}_dev SYSTEM PUBLIC ${EIGEN3_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}_dev PUBLIC eigen)



set(ZIRAN_DATA_DIR ${ZIRAN_SOURCE_DIR}/data)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CS/Util/DataDir.h.in ${CMAKE_CURRENT_SOURCE_DIR}/CS/Util/DataDir.h @ONLY)

