# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/paniquex/Programes/clion-2018.2.6/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/paniquex/Programes/clion-2018.2.6/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/paniquex/CLionProjects/code_colorer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/paniquex/CLionProjects/code_colorer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/code_colorer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/code_colorer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/code_colorer.dir/flags.make

CMakeFiles/code_colorer.dir/main.cpp.o: CMakeFiles/code_colorer.dir/flags.make
CMakeFiles/code_colorer.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paniquex/CLionProjects/code_colorer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/code_colorer.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/code_colorer.dir/main.cpp.o -c /home/paniquex/CLionProjects/code_colorer/main.cpp

CMakeFiles/code_colorer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/code_colorer.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paniquex/CLionProjects/code_colorer/main.cpp > CMakeFiles/code_colorer.dir/main.cpp.i

CMakeFiles/code_colorer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/code_colorer.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paniquex/CLionProjects/code_colorer/main.cpp -o CMakeFiles/code_colorer.dir/main.cpp.s

CMakeFiles/code_colorer.dir/input_file.cpp.o: CMakeFiles/code_colorer.dir/flags.make
CMakeFiles/code_colorer.dir/input_file.cpp.o: ../input_file.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paniquex/CLionProjects/code_colorer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/code_colorer.dir/input_file.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/code_colorer.dir/input_file.cpp.o -c /home/paniquex/CLionProjects/code_colorer/input_file.cpp

CMakeFiles/code_colorer.dir/input_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/code_colorer.dir/input_file.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paniquex/CLionProjects/code_colorer/input_file.cpp > CMakeFiles/code_colorer.dir/input_file.cpp.i

CMakeFiles/code_colorer.dir/input_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/code_colorer.dir/input_file.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paniquex/CLionProjects/code_colorer/input_file.cpp -o CMakeFiles/code_colorer.dir/input_file.cpp.s

CMakeFiles/code_colorer.dir/input_stdin_type.cpp.o: CMakeFiles/code_colorer.dir/flags.make
CMakeFiles/code_colorer.dir/input_stdin_type.cpp.o: ../input_stdin_type.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paniquex/CLionProjects/code_colorer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/code_colorer.dir/input_stdin_type.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/code_colorer.dir/input_stdin_type.cpp.o -c /home/paniquex/CLionProjects/code_colorer/input_stdin_type.cpp

CMakeFiles/code_colorer.dir/input_stdin_type.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/code_colorer.dir/input_stdin_type.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paniquex/CLionProjects/code_colorer/input_stdin_type.cpp > CMakeFiles/code_colorer.dir/input_stdin_type.cpp.i

CMakeFiles/code_colorer.dir/input_stdin_type.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/code_colorer.dir/input_stdin_type.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paniquex/CLionProjects/code_colorer/input_stdin_type.cpp -o CMakeFiles/code_colorer.dir/input_stdin_type.cpp.s

CMakeFiles/code_colorer.dir/analysing.cpp.o: CMakeFiles/code_colorer.dir/flags.make
CMakeFiles/code_colorer.dir/analysing.cpp.o: ../analysing.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paniquex/CLionProjects/code_colorer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/code_colorer.dir/analysing.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/code_colorer.dir/analysing.cpp.o -c /home/paniquex/CLionProjects/code_colorer/analysing.cpp

CMakeFiles/code_colorer.dir/analysing.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/code_colorer.dir/analysing.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paniquex/CLionProjects/code_colorer/analysing.cpp > CMakeFiles/code_colorer.dir/analysing.cpp.i

CMakeFiles/code_colorer.dir/analysing.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/code_colorer.dir/analysing.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paniquex/CLionProjects/code_colorer/analysing.cpp -o CMakeFiles/code_colorer.dir/analysing.cpp.s

CMakeFiles/code_colorer.dir/coloring.cpp.o: CMakeFiles/code_colorer.dir/flags.make
CMakeFiles/code_colorer.dir/coloring.cpp.o: ../coloring.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paniquex/CLionProjects/code_colorer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/code_colorer.dir/coloring.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/code_colorer.dir/coloring.cpp.o -c /home/paniquex/CLionProjects/code_colorer/coloring.cpp

CMakeFiles/code_colorer.dir/coloring.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/code_colorer.dir/coloring.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paniquex/CLionProjects/code_colorer/coloring.cpp > CMakeFiles/code_colorer.dir/coloring.cpp.i

CMakeFiles/code_colorer.dir/coloring.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/code_colorer.dir/coloring.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paniquex/CLionProjects/code_colorer/coloring.cpp -o CMakeFiles/code_colorer.dir/coloring.cpp.s

CMakeFiles/code_colorer.dir/counting.cpp.o: CMakeFiles/code_colorer.dir/flags.make
CMakeFiles/code_colorer.dir/counting.cpp.o: ../counting.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paniquex/CLionProjects/code_colorer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/code_colorer.dir/counting.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/code_colorer.dir/counting.cpp.o -c /home/paniquex/CLionProjects/code_colorer/counting.cpp

CMakeFiles/code_colorer.dir/counting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/code_colorer.dir/counting.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paniquex/CLionProjects/code_colorer/counting.cpp > CMakeFiles/code_colorer.dir/counting.cpp.i

CMakeFiles/code_colorer.dir/counting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/code_colorer.dir/counting.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paniquex/CLionProjects/code_colorer/counting.cpp -o CMakeFiles/code_colorer.dir/counting.cpp.s

CMakeFiles/code_colorer.dir/token.cpp.o: CMakeFiles/code_colorer.dir/flags.make
CMakeFiles/code_colorer.dir/token.cpp.o: ../token.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/paniquex/CLionProjects/code_colorer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/code_colorer.dir/token.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/code_colorer.dir/token.cpp.o -c /home/paniquex/CLionProjects/code_colorer/token.cpp

CMakeFiles/code_colorer.dir/token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/code_colorer.dir/token.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/paniquex/CLionProjects/code_colorer/token.cpp > CMakeFiles/code_colorer.dir/token.cpp.i

CMakeFiles/code_colorer.dir/token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/code_colorer.dir/token.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/paniquex/CLionProjects/code_colorer/token.cpp -o CMakeFiles/code_colorer.dir/token.cpp.s

# Object files for target code_colorer
code_colorer_OBJECTS = \
"CMakeFiles/code_colorer.dir/main.cpp.o" \
"CMakeFiles/code_colorer.dir/input_file.cpp.o" \
"CMakeFiles/code_colorer.dir/input_stdin_type.cpp.o" \
"CMakeFiles/code_colorer.dir/analysing.cpp.o" \
"CMakeFiles/code_colorer.dir/coloring.cpp.o" \
"CMakeFiles/code_colorer.dir/counting.cpp.o" \
"CMakeFiles/code_colorer.dir/token.cpp.o"

# External object files for target code_colorer
code_colorer_EXTERNAL_OBJECTS =

code_colorer: CMakeFiles/code_colorer.dir/main.cpp.o
code_colorer: CMakeFiles/code_colorer.dir/input_file.cpp.o
code_colorer: CMakeFiles/code_colorer.dir/input_stdin_type.cpp.o
code_colorer: CMakeFiles/code_colorer.dir/analysing.cpp.o
code_colorer: CMakeFiles/code_colorer.dir/coloring.cpp.o
code_colorer: CMakeFiles/code_colorer.dir/counting.cpp.o
code_colorer: CMakeFiles/code_colorer.dir/token.cpp.o
code_colorer: CMakeFiles/code_colorer.dir/build.make
code_colorer: CMakeFiles/code_colorer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/paniquex/CLionProjects/code_colorer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable code_colorer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/code_colorer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/code_colorer.dir/build: code_colorer

.PHONY : CMakeFiles/code_colorer.dir/build

CMakeFiles/code_colorer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/code_colorer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/code_colorer.dir/clean

CMakeFiles/code_colorer.dir/depend:
	cd /home/paniquex/CLionProjects/code_colorer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/paniquex/CLionProjects/code_colorer /home/paniquex/CLionProjects/code_colorer /home/paniquex/CLionProjects/code_colorer/cmake-build-debug /home/paniquex/CLionProjects/code_colorer/cmake-build-debug /home/paniquex/CLionProjects/code_colorer/cmake-build-debug/CMakeFiles/code_colorer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/code_colorer.dir/depend

