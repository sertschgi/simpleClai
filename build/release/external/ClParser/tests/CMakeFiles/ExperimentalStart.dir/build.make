# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /opt/cmake-3.28.2-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.28.2-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/malte/code/simpleClai

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/malte/code/simpleClai/build/release

# Utility rule file for ExperimentalStart.

# Include any custom commands dependencies for this target.
include external/ClParser/tests/CMakeFiles/ExperimentalStart.dir/compiler_depend.make

# Include the progress variables for this target.
include external/ClParser/tests/CMakeFiles/ExperimentalStart.dir/progress.make

external/ClParser/tests/CMakeFiles/ExperimentalStart:
	cd /home/malte/code/simpleClai/build/release/external/ClParser/tests && /opt/cmake-3.28.2-linux-x86_64/bin/ctest -D ExperimentalStart

ExperimentalStart: external/ClParser/tests/CMakeFiles/ExperimentalStart
ExperimentalStart: external/ClParser/tests/CMakeFiles/ExperimentalStart.dir/build.make
.PHONY : ExperimentalStart

# Rule to build all files generated by this target.
external/ClParser/tests/CMakeFiles/ExperimentalStart.dir/build: ExperimentalStart
.PHONY : external/ClParser/tests/CMakeFiles/ExperimentalStart.dir/build

external/ClParser/tests/CMakeFiles/ExperimentalStart.dir/clean:
	cd /home/malte/code/simpleClai/build/release/external/ClParser/tests && $(CMAKE_COMMAND) -P CMakeFiles/ExperimentalStart.dir/cmake_clean.cmake
.PHONY : external/ClParser/tests/CMakeFiles/ExperimentalStart.dir/clean

external/ClParser/tests/CMakeFiles/ExperimentalStart.dir/depend:
	cd /home/malte/code/simpleClai/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/malte/code/simpleClai /home/malte/code/simpleClai/external/ClParser/tests /home/malte/code/simpleClai/build/release /home/malte/code/simpleClai/build/release/external/ClParser/tests /home/malte/code/simpleClai/build/release/external/ClParser/tests/CMakeFiles/ExperimentalStart.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : external/ClParser/tests/CMakeFiles/ExperimentalStart.dir/depend
