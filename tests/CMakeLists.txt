# test/CMakeLists.txt
include(FetchContent)  
FetchContent_Declare(  
        Catch2  
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git  
        GIT_TAG        v3.6.0  
)  
FetchContent_MakeAvailable(Catch2)  

add_executable(${PROJECT_NAME}_tests test.cpp test.cu)

target_link_libraries(${PROJECT_NAME}_tests PUBLIC ${PROJECT_NAME}_dev Catch2::Catch2WithMain)


add_test(NAME AllTests  
        COMMAND ${PROJECT_NAME}_tests --success  
)  