# # test/CMakeLists.txt
# include(FetchContent)  
# FetchContent_Declare(  
#         Catch2  
#         GIT_REPOSITORY https://github.com/catchorg/Catch2.git  
#         GIT_TAG        v3.6.0  
# )  
# FetchContent_MakeAvailable(Catch2)  
  
# add_executable(SimZipTest test.cpp)  
# target_link_libraries(SimZipTest PRIVATE SimZip Catch2::Catch2WithMain)  
  
# add_test(NAME SimZipTest  
#         COMMAND $<TARGET_FILE:SimZipTest> --success  
# )  

add_executable(${PROJECT_NAME}_tests test.cpp)

target_link_libraries(${PROJECT_NAME}_tests PUBLIC ${PROJECT_NAME}_dev)

add_test(output_test ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_tests)
set_tests_properties(output_test PROPERTIES PASS_REGULAR_EXPRESSION "Hello World\n")
