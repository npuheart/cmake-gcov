# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/runner/work/cmake-gcov/cmake-gcov

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/runner/work/cmake-gcov/cmake-gcov/build

# Utility rule file for gcov.

# Include any custom commands dependencies for this target.
include CMakeFiles/gcov.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gcov.dir/progress.make

CMakeFiles/gcov:
	mkdir -p coverage
	/usr/bin/gmake test

gcov: CMakeFiles/gcov
gcov: CMakeFiles/gcov.dir/build.make
	cd /home/runner/work/cmake-gcov/cmake-gcov/build/coverage && echo ===================\ GCOV\ ====================
	cd /home/runner/work/cmake-gcov/cmake-gcov/build/coverage && gcov -b /home/runner/work/cmake-gcov/cmake-gcov/*.cpp -o /home/runner/work/cmake-gcov/cmake-gcov/build/CMakeFiles/RunAdder.dir | grep -A 5 Adder.cpp > CoverageSummary.tmp
	cd /home/runner/work/cmake-gcov/cmake-gcov/build/coverage && cat CoverageSummary.tmp
	cd /home/runner/work/cmake-gcov/cmake-gcov/build/coverage && echo --\ Coverage\ files\ have\ been\ output\ to\ /home/runner/work/cmake-gcov/cmake-gcov/build/coverage
.PHONY : gcov

# Rule to build all files generated by this target.
CMakeFiles/gcov.dir/build: gcov
.PHONY : CMakeFiles/gcov.dir/build

CMakeFiles/gcov.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gcov.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gcov.dir/clean

CMakeFiles/gcov.dir/depend:
	cd /home/runner/work/cmake-gcov/cmake-gcov/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/runner/work/cmake-gcov/cmake-gcov /home/runner/work/cmake-gcov/cmake-gcov /home/runner/work/cmake-gcov/cmake-gcov/build /home/runner/work/cmake-gcov/cmake-gcov/build /home/runner/work/cmake-gcov/cmake-gcov/build/CMakeFiles/gcov.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/gcov.dir/depend

