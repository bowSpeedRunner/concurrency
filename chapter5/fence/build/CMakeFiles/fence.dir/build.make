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
CMAKE_SOURCE_DIR = /home/yjh/concurrency/chapter5/fence

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yjh/concurrency/chapter5/fence/build

# Include any dependencies generated for this target.
include CMakeFiles/fence.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/fence.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/fence.dir/flags.make

CMakeFiles/fence.dir/src/fence.cpp.o: CMakeFiles/fence.dir/flags.make
CMakeFiles/fence.dir/src/fence.cpp.o: ../src/fence.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yjh/concurrency/chapter5/fence/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/fence.dir/src/fence.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/fence.dir/src/fence.cpp.o -c /home/yjh/concurrency/chapter5/fence/src/fence.cpp

CMakeFiles/fence.dir/src/fence.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/fence.dir/src/fence.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yjh/concurrency/chapter5/fence/src/fence.cpp > CMakeFiles/fence.dir/src/fence.cpp.i

CMakeFiles/fence.dir/src/fence.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/fence.dir/src/fence.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yjh/concurrency/chapter5/fence/src/fence.cpp -o CMakeFiles/fence.dir/src/fence.cpp.s

# Object files for target fence
fence_OBJECTS = \
"CMakeFiles/fence.dir/src/fence.cpp.o"

# External object files for target fence
fence_EXTERNAL_OBJECTS =

fence: CMakeFiles/fence.dir/src/fence.cpp.o
fence: CMakeFiles/fence.dir/build.make
fence: CMakeFiles/fence.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yjh/concurrency/chapter5/fence/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable fence"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/fence.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/fence.dir/build: fence

.PHONY : CMakeFiles/fence.dir/build

CMakeFiles/fence.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fence.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fence.dir/clean

CMakeFiles/fence.dir/depend:
	cd /home/yjh/concurrency/chapter5/fence/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yjh/concurrency/chapter5/fence /home/yjh/concurrency/chapter5/fence /home/yjh/concurrency/chapter5/fence/build /home/yjh/concurrency/chapter5/fence/build /home/yjh/concurrency/chapter5/fence/build/CMakeFiles/fence.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/fence.dir/depend
