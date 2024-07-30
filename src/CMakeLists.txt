

add_subdirectory(Apple)

# Create the library (创建库)
add_library(${PROJECT_NAME}_dev OBJECT Adder.cpp)
target_include_directories(${PROJECT_NAME}_dev PUBLIC ".")
target_link_libraries(${PROJECT_NAME}_dev PUBLIC Apple)
