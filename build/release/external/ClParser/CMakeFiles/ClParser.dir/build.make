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

# Include any dependencies generated for this target.
include external/ClParser/CMakeFiles/ClParser.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/ClParser/CMakeFiles/ClParser.dir/compiler_depend.make

# Include the progress variables for this target.
include external/ClParser/CMakeFiles/ClParser.dir/progress.make

# Include the compile flags for this target's objects.
include external/ClParser/CMakeFiles/ClParser.dir/flags.make

external/ClParser/CMakeFiles/ClParser.dir/src/Parser.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/flags.make
external/ClParser/CMakeFiles/ClParser.dir/src/Parser.cpp.o: /home/malte/code/simpleClai/external/ClParser/src/Parser.cpp
external/ClParser/CMakeFiles/ClParser.dir/src/Parser.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/malte/code/simpleClai/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object external/ClParser/CMakeFiles/ClParser.dir/src/Parser.cpp.o"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/ClParser/CMakeFiles/ClParser.dir/src/Parser.cpp.o -MF CMakeFiles/ClParser.dir/src/Parser.cpp.o.d -o CMakeFiles/ClParser.dir/src/Parser.cpp.o -c /home/malte/code/simpleClai/external/ClParser/src/Parser.cpp

external/ClParser/CMakeFiles/ClParser.dir/src/Parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ClParser.dir/src/Parser.cpp.i"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/malte/code/simpleClai/external/ClParser/src/Parser.cpp > CMakeFiles/ClParser.dir/src/Parser.cpp.i

external/ClParser/CMakeFiles/ClParser.dir/src/Parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ClParser.dir/src/Parser.cpp.s"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/malte/code/simpleClai/external/ClParser/src/Parser.cpp -o CMakeFiles/ClParser.dir/src/Parser.cpp.s

external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClParser.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/flags.make
external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClParser.cpp.o: /home/malte/code/simpleClai/external/ClParser/src/modules/ClParser.cpp
external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClParser.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/malte/code/simpleClai/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClParser.cpp.o"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClParser.cpp.o -MF CMakeFiles/ClParser.dir/src/modules/ClParser.cpp.o.d -o CMakeFiles/ClParser.dir/src/modules/ClParser.cpp.o -c /home/malte/code/simpleClai/external/ClParser/src/modules/ClParser.cpp

external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ClParser.dir/src/modules/ClParser.cpp.i"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/malte/code/simpleClai/external/ClParser/src/modules/ClParser.cpp > CMakeFiles/ClParser.dir/src/modules/ClParser.cpp.i

external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ClParser.dir/src/modules/ClParser.cpp.s"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/malte/code/simpleClai/external/ClParser/src/modules/ClParser.cpp -o CMakeFiles/ClParser.dir/src/modules/ClParser.cpp.s

external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClPosArg.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/flags.make
external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClPosArg.cpp.o: /home/malte/code/simpleClai/external/ClParser/src/modules/ClPosArg.cpp
external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClPosArg.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/malte/code/simpleClai/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClPosArg.cpp.o"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClPosArg.cpp.o -MF CMakeFiles/ClParser.dir/src/modules/ClPosArg.cpp.o.d -o CMakeFiles/ClParser.dir/src/modules/ClPosArg.cpp.o -c /home/malte/code/simpleClai/external/ClParser/src/modules/ClPosArg.cpp

external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClPosArg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ClParser.dir/src/modules/ClPosArg.cpp.i"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/malte/code/simpleClai/external/ClParser/src/modules/ClPosArg.cpp > CMakeFiles/ClParser.dir/src/modules/ClPosArg.cpp.i

external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClPosArg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ClParser.dir/src/modules/ClPosArg.cpp.s"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/malte/code/simpleClai/external/ClParser/src/modules/ClPosArg.cpp -o CMakeFiles/ClParser.dir/src/modules/ClPosArg.cpp.s

external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClOption.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/flags.make
external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClOption.cpp.o: /home/malte/code/simpleClai/external/ClParser/src/modules/ClOption.cpp
external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClOption.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/malte/code/simpleClai/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClOption.cpp.o"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClOption.cpp.o -MF CMakeFiles/ClParser.dir/src/modules/ClOption.cpp.o.d -o CMakeFiles/ClParser.dir/src/modules/ClOption.cpp.o -c /home/malte/code/simpleClai/external/ClParser/src/modules/ClOption.cpp

external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClOption.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ClParser.dir/src/modules/ClOption.cpp.i"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/malte/code/simpleClai/external/ClParser/src/modules/ClOption.cpp > CMakeFiles/ClParser.dir/src/modules/ClOption.cpp.i

external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClOption.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ClParser.dir/src/modules/ClOption.cpp.s"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/malte/code/simpleClai/external/ClParser/src/modules/ClOption.cpp -o CMakeFiles/ClParser.dir/src/modules/ClOption.cpp.s

external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClCommand.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/flags.make
external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClCommand.cpp.o: /home/malte/code/simpleClai/external/ClParser/src/modules/ClCommand.cpp
external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClCommand.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/malte/code/simpleClai/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClCommand.cpp.o"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClCommand.cpp.o -MF CMakeFiles/ClParser.dir/src/modules/ClCommand.cpp.o.d -o CMakeFiles/ClParser.dir/src/modules/ClCommand.cpp.o -c /home/malte/code/simpleClai/external/ClParser/src/modules/ClCommand.cpp

external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClCommand.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ClParser.dir/src/modules/ClCommand.cpp.i"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/malte/code/simpleClai/external/ClParser/src/modules/ClCommand.cpp > CMakeFiles/ClParser.dir/src/modules/ClCommand.cpp.i

external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClCommand.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ClParser.dir/src/modules/ClCommand.cpp.s"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/malte/code/simpleClai/external/ClParser/src/modules/ClCommand.cpp -o CMakeFiles/ClParser.dir/src/modules/ClCommand.cpp.s

external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/commandFunctionality.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/flags.make
external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/commandFunctionality.cpp.o: /home/malte/code/simpleClai/external/ClParser/src/modules/parent/commandFunctionality.cpp
external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/commandFunctionality.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/malte/code/simpleClai/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/commandFunctionality.cpp.o"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/commandFunctionality.cpp.o -MF CMakeFiles/ClParser.dir/src/modules/parent/commandFunctionality.cpp.o.d -o CMakeFiles/ClParser.dir/src/modules/parent/commandFunctionality.cpp.o -c /home/malte/code/simpleClai/external/ClParser/src/modules/parent/commandFunctionality.cpp

external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/commandFunctionality.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ClParser.dir/src/modules/parent/commandFunctionality.cpp.i"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/malte/code/simpleClai/external/ClParser/src/modules/parent/commandFunctionality.cpp > CMakeFiles/ClParser.dir/src/modules/parent/commandFunctionality.cpp.i

external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/commandFunctionality.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ClParser.dir/src/modules/parent/commandFunctionality.cpp.s"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/malte/code/simpleClai/external/ClParser/src/modules/parent/commandFunctionality.cpp -o CMakeFiles/ClParser.dir/src/modules/parent/commandFunctionality.cpp.s

external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/optionHandleFunctionality.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/flags.make
external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/optionHandleFunctionality.cpp.o: /home/malte/code/simpleClai/external/ClParser/src/modules/parent/optionHandleFunctionality.cpp
external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/optionHandleFunctionality.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/malte/code/simpleClai/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/optionHandleFunctionality.cpp.o"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/optionHandleFunctionality.cpp.o -MF CMakeFiles/ClParser.dir/src/modules/parent/optionHandleFunctionality.cpp.o.d -o CMakeFiles/ClParser.dir/src/modules/parent/optionHandleFunctionality.cpp.o -c /home/malte/code/simpleClai/external/ClParser/src/modules/parent/optionHandleFunctionality.cpp

external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/optionHandleFunctionality.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ClParser.dir/src/modules/parent/optionHandleFunctionality.cpp.i"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/malte/code/simpleClai/external/ClParser/src/modules/parent/optionHandleFunctionality.cpp > CMakeFiles/ClParser.dir/src/modules/parent/optionHandleFunctionality.cpp.i

external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/optionHandleFunctionality.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ClParser.dir/src/modules/parent/optionHandleFunctionality.cpp.s"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/malte/code/simpleClai/external/ClParser/src/modules/parent/optionHandleFunctionality.cpp -o CMakeFiles/ClParser.dir/src/modules/parent/optionHandleFunctionality.cpp.s

external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/posArgHandleFunctionality.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/flags.make
external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/posArgHandleFunctionality.cpp.o: /home/malte/code/simpleClai/external/ClParser/src/modules/parent/posArgHandleFunctionality.cpp
external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/posArgHandleFunctionality.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/malte/code/simpleClai/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/posArgHandleFunctionality.cpp.o"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/posArgHandleFunctionality.cpp.o -MF CMakeFiles/ClParser.dir/src/modules/parent/posArgHandleFunctionality.cpp.o.d -o CMakeFiles/ClParser.dir/src/modules/parent/posArgHandleFunctionality.cpp.o -c /home/malte/code/simpleClai/external/ClParser/src/modules/parent/posArgHandleFunctionality.cpp

external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/posArgHandleFunctionality.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ClParser.dir/src/modules/parent/posArgHandleFunctionality.cpp.i"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/malte/code/simpleClai/external/ClParser/src/modules/parent/posArgHandleFunctionality.cpp > CMakeFiles/ClParser.dir/src/modules/parent/posArgHandleFunctionality.cpp.i

external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/posArgHandleFunctionality.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ClParser.dir/src/modules/parent/posArgHandleFunctionality.cpp.s"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/malte/code/simpleClai/external/ClParser/src/modules/parent/posArgHandleFunctionality.cpp -o CMakeFiles/ClParser.dir/src/modules/parent/posArgHandleFunctionality.cpp.s

external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/generalFunctionality.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/flags.make
external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/generalFunctionality.cpp.o: /home/malte/code/simpleClai/external/ClParser/src/modules/parent/generalFunctionality.cpp
external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/generalFunctionality.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/malte/code/simpleClai/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/generalFunctionality.cpp.o"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/generalFunctionality.cpp.o -MF CMakeFiles/ClParser.dir/src/modules/parent/generalFunctionality.cpp.o.d -o CMakeFiles/ClParser.dir/src/modules/parent/generalFunctionality.cpp.o -c /home/malte/code/simpleClai/external/ClParser/src/modules/parent/generalFunctionality.cpp

external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/generalFunctionality.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ClParser.dir/src/modules/parent/generalFunctionality.cpp.i"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/malte/code/simpleClai/external/ClParser/src/modules/parent/generalFunctionality.cpp > CMakeFiles/ClParser.dir/src/modules/parent/generalFunctionality.cpp.i

external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/generalFunctionality.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ClParser.dir/src/modules/parent/generalFunctionality.cpp.s"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/malte/code/simpleClai/external/ClParser/src/modules/parent/generalFunctionality.cpp -o CMakeFiles/ClParser.dir/src/modules/parent/generalFunctionality.cpp.s

external/ClParser/CMakeFiles/ClParser.dir/src/modules/utility/helperFunctions.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/flags.make
external/ClParser/CMakeFiles/ClParser.dir/src/modules/utility/helperFunctions.cpp.o: /home/malte/code/simpleClai/external/ClParser/src/modules/utility/helperFunctions.cpp
external/ClParser/CMakeFiles/ClParser.dir/src/modules/utility/helperFunctions.cpp.o: external/ClParser/CMakeFiles/ClParser.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/malte/code/simpleClai/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object external/ClParser/CMakeFiles/ClParser.dir/src/modules/utility/helperFunctions.cpp.o"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT external/ClParser/CMakeFiles/ClParser.dir/src/modules/utility/helperFunctions.cpp.o -MF CMakeFiles/ClParser.dir/src/modules/utility/helperFunctions.cpp.o.d -o CMakeFiles/ClParser.dir/src/modules/utility/helperFunctions.cpp.o -c /home/malte/code/simpleClai/external/ClParser/src/modules/utility/helperFunctions.cpp

external/ClParser/CMakeFiles/ClParser.dir/src/modules/utility/helperFunctions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ClParser.dir/src/modules/utility/helperFunctions.cpp.i"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/malte/code/simpleClai/external/ClParser/src/modules/utility/helperFunctions.cpp > CMakeFiles/ClParser.dir/src/modules/utility/helperFunctions.cpp.i

external/ClParser/CMakeFiles/ClParser.dir/src/modules/utility/helperFunctions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ClParser.dir/src/modules/utility/helperFunctions.cpp.s"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/malte/code/simpleClai/external/ClParser/src/modules/utility/helperFunctions.cpp -o CMakeFiles/ClParser.dir/src/modules/utility/helperFunctions.cpp.s

# Object files for target ClParser
ClParser_OBJECTS = \
"CMakeFiles/ClParser.dir/src/Parser.cpp.o" \
"CMakeFiles/ClParser.dir/src/modules/ClParser.cpp.o" \
"CMakeFiles/ClParser.dir/src/modules/ClPosArg.cpp.o" \
"CMakeFiles/ClParser.dir/src/modules/ClOption.cpp.o" \
"CMakeFiles/ClParser.dir/src/modules/ClCommand.cpp.o" \
"CMakeFiles/ClParser.dir/src/modules/parent/commandFunctionality.cpp.o" \
"CMakeFiles/ClParser.dir/src/modules/parent/optionHandleFunctionality.cpp.o" \
"CMakeFiles/ClParser.dir/src/modules/parent/posArgHandleFunctionality.cpp.o" \
"CMakeFiles/ClParser.dir/src/modules/parent/generalFunctionality.cpp.o" \
"CMakeFiles/ClParser.dir/src/modules/utility/helperFunctions.cpp.o"

# External object files for target ClParser
ClParser_EXTERNAL_OBJECTS =

external/ClParser/libClParser.a: external/ClParser/CMakeFiles/ClParser.dir/src/Parser.cpp.o
external/ClParser/libClParser.a: external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClParser.cpp.o
external/ClParser/libClParser.a: external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClPosArg.cpp.o
external/ClParser/libClParser.a: external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClOption.cpp.o
external/ClParser/libClParser.a: external/ClParser/CMakeFiles/ClParser.dir/src/modules/ClCommand.cpp.o
external/ClParser/libClParser.a: external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/commandFunctionality.cpp.o
external/ClParser/libClParser.a: external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/optionHandleFunctionality.cpp.o
external/ClParser/libClParser.a: external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/posArgHandleFunctionality.cpp.o
external/ClParser/libClParser.a: external/ClParser/CMakeFiles/ClParser.dir/src/modules/parent/generalFunctionality.cpp.o
external/ClParser/libClParser.a: external/ClParser/CMakeFiles/ClParser.dir/src/modules/utility/helperFunctions.cpp.o
external/ClParser/libClParser.a: external/ClParser/CMakeFiles/ClParser.dir/build.make
external/ClParser/libClParser.a: external/ClParser/CMakeFiles/ClParser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/malte/code/simpleClai/build/release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX static library libClParser.a"
	cd /home/malte/code/simpleClai/build/release/external/ClParser && $(CMAKE_COMMAND) -P CMakeFiles/ClParser.dir/cmake_clean_target.cmake
	cd /home/malte/code/simpleClai/build/release/external/ClParser && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ClParser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/ClParser/CMakeFiles/ClParser.dir/build: external/ClParser/libClParser.a
.PHONY : external/ClParser/CMakeFiles/ClParser.dir/build

external/ClParser/CMakeFiles/ClParser.dir/clean:
	cd /home/malte/code/simpleClai/build/release/external/ClParser && $(CMAKE_COMMAND) -P CMakeFiles/ClParser.dir/cmake_clean.cmake
.PHONY : external/ClParser/CMakeFiles/ClParser.dir/clean

external/ClParser/CMakeFiles/ClParser.dir/depend:
	cd /home/malte/code/simpleClai/build/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/malte/code/simpleClai /home/malte/code/simpleClai/external/ClParser /home/malte/code/simpleClai/build/release /home/malte/code/simpleClai/build/release/external/ClParser /home/malte/code/simpleClai/build/release/external/ClParser/CMakeFiles/ClParser.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : external/ClParser/CMakeFiles/ClParser.dir/depend
