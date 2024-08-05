




add_library(spgrid STATIC
        Core/SPGrid_Geometry.cpp
        Core/SPGrid_Utilities.cpp)

target_compile_options(spgrid PUBLIC "-Wno-unused-local-typedefs")

target_include_directories(spgrid PRIVATE ..)


