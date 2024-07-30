# test/CMakeLists.txt
include(FetchContent)  
FetchContent_Declare(  
        Catch2  
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git  
        GIT_TAG        v3.6.0  
)  
FetchContent_MakeAvailable(Catch2)  

# add_executable(SimZipTest test.cpp)  
# target_link_libraries(SimZipTest PRIVATE SimZip Catch2::Catch2WithMain)  
  
# add_test(NAME SimZipTest  
#         COMMAND $<TARGET_FILE:SimZipTest> --success  
# )  

add_executable(${PROJECT_NAME}_tests test.cpp)

target_link_libraries(${PROJECT_NAME}_tests PUBLIC ${PROJECT_NAME}_dev Catch2::Catch2WithMain)

# add_test(output_test ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_tests)
# set_tests_properties(output_test PROPERTIES PASS_REGULAR_EXPRESSION "Hello World\n")


# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
    COMMAND echo "=================== add_custom_target ===================="
    COMMAND mkdir -p coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} 
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
add_custom_command(TARGET gcov
    PRE_BUILD 
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov -b ${CMAKE_SOURCE_DIR}/*.cpp -o ${OBJECT_DIR}
        | grep -A 5 "Adder.cpp" > CoverageSummary.tmp
    COMMAND cat CoverageSummary.tmp
    COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage  # Need separate command for this line
    )

add_dependencies(gcov ${PROJECT_NAME}_tests)
# Make sure to clean up the coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

# Create the gcov-clean target. This cleans the build as well as generated 
# .gcda and .gcno files.
add_custom_target(scrub
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm -f ${OBJECT_DIR}/*.gcno
    COMMAND rm -f ${OBJECT_DIR}/*.gcda
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

add_test(NAME SimZipTest  
        COMMAND ${PROJECT_NAME}_tests --success  
)  