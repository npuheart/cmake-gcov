find_package(DOLFINX REQUIRED)
include(CheckSymbolExists)
set(CMAKE_REQUIRED_INCLUDES ${PETSC_INCLUDE_DIRS})
check_symbol_exists(PETSC_USE_COMPLEX petscsystypes.h PETSC_SCALAR_COMPLEX)
check_symbol_exists(PETSC_USE_REAL_DOUBLE petscsystypes.h PETSC_REAL_DOUBLE)

# Add target to compile UFL files
if(PETSC_SCALAR_COMPLEX EQUAL 1)
  if(PETSC_REAL_DOUBLE EQUAL 1)
    set(SCALAR_TYPE "--scalar_type=complex128")
  else()
    set(SCALAR_TYPE "--scalar_type=complex64")
  endif()
else()
  if(PETSC_REAL_DOUBLE EQUAL 1)
    set(SCALAR_TYPE "--scalar_type=float64")
  else()
    set(SCALAR_TYPE "--scalar_type=float32")
  endif()
endif()
add_custom_command(
  OUTPUT poisson.c
  COMMAND ffcx ${CMAKE_CURRENT_SOURCE_DIR}/poisson.py ${SCALAR_TYPE}
  VERBATIM
  DEPENDS poisson.py
  COMMENT "Compile poisson.py using FFCx"
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_library(demo_poisson main.cpp ${CMAKE_CURRENT_BINARY_DIR}/poisson.c)
target_link_libraries(demo_poisson PUBLIC dolfinx)

# Do not throw error for 'multi-line comments' (these are typical in rst which
# includes LaTeX)
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-Wno-comment" HAVE_NO_MULTLINE)
set_source_files_properties(
  main.cpp
  PROPERTIES
    COMPILE_FLAGS
    "$<$<BOOL:${HAVE_NO_MULTLINE}>:-Wno-comment -Wall -Wextra -pedantic -Werror>"
)
