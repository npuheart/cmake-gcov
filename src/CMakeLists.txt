
# 添加子项目
add_subdirectory(Apple)
add_subdirectory(Depends)

# Create the library (创建库)
add_library(${PROJECT_NAME}_dev OBJECT Adder.cpp)
target_include_directories(${PROJECT_NAME}_dev PUBLIC ".")

# 链接子项目
target_link_libraries(${PROJECT_NAME}_dev PUBLIC Apple)
target_link_libraries(${PROJECT_NAME}_dev PUBLIC tbb)

