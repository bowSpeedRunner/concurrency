# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yjh/concurrency/chapter5/seq_cst

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yjh/concurrency/chapter5/seq_cst/build

# Include any dependencies generated for this target.
include CMakeFiles/seq_cst.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/seq_cst.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/seq_cst.dir/flags.make

CMakeFiles/seq_cst.dir/src/seq_cst.cpp.o: CMakeFiles/seq_cst.dir/flags.make
CMakeFiles/seq_cst.dir/src/seq_cst.cpp.o: ../src/seq_cst.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yjh/concurrency/chapter5/seq_cst/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/seq_cst.dir/src/seq_cst.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/seq_cst.dir/src/seq_cst.cpp.o -c /home/yjh/concurrency/chapter5/seq_cst/src/seq_cst.cpp

CMakeFiles/seq_cst.dir/src/seq_cst.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/seq_cst.dir/src/seq_cst.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yjh/concurrency/chapter5/seq_cst/src/seq_cst.cpp > CMakeFiles/seq_cst.dir/src/seq_cst.cpp.i

CMakeFiles/seq_cst.dir/src/seq_cst.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/seq_cst.dir/src/seq_cst.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yjh/concurrency/chapter5/seq_cst/src/seq_cst.cpp -o CMakeFiles/seq_cst.dir/src/seq_cst.cpp.s

# Object files for target seq_cst
seq_cst_OBJECTS = \
"CMakeFiles/seq_cst.dir/src/seq_cst.cpp.o"

# External object files for target seq_cst
seq_cst_EXTERNAL_OBJECTS =

seq_cst: CMakeFiles/seq_cst.dir/src/seq_cst.cpp.o
seq_cst: CMakeFiles/seq_cst.dir/build.make
seq_cst: CMakeFiles/seq_cst.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yjh/concurrency/chapter5/seq_cst/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable seq_cst"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/seq_cst.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/seq_cst.dir/build: seq_cst

.PHONY : CMakeFiles/seq_cst.dir/build

CMakeFiles/seq_cst.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/seq_cst.dir/cmake_clean.cmake
.PHONY : CMakeFiles/seq_cst.dir/clean

CMakeFiles/seq_cst.dir/depend:
	cd /home/yjh/concurrency/chapter5/seq_cst/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yjh/concurrency/chapter5/seq_cst /home/yjh/concurrency/chapter5/seq_cst /home/yjh/concurrency/chapter5/seq_cst/build /home/yjh/concurrency/chapter5/seq_cst/build /home/yjh/concurrency/chapter5/seq_cst/build/CMakeFiles/seq_cst.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/seq_cst.dir/depend

