# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build

# Include any dependencies generated for this target.
include test/CMakeFiles/nesting_ops_1.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/nesting_ops_1.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/nesting_ops_1.dir/flags.make

test/CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.o: test/CMakeFiles/nesting_ops_1.dir/flags.make
test/CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.o: ../test/nesting_ops.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.o"
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.o -c /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/test/nesting_ops.cpp

test/CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.i"
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/test/nesting_ops.cpp > CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.i

test/CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.s"
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/test/nesting_ops.cpp -o CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.s

test/CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.o.requires:

.PHONY : test/CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.o.requires

test/CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.o.provides: test/CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/nesting_ops_1.dir/build.make test/CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.o.provides.build
.PHONY : test/CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.o.provides

test/CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.o.provides.build: test/CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.o


# Object files for target nesting_ops_1
nesting_ops_1_OBJECTS = \
"CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.o"

# External object files for target nesting_ops_1
nesting_ops_1_EXTERNAL_OBJECTS =

test/nesting_ops_1: test/CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.o
test/nesting_ops_1: test/CMakeFiles/nesting_ops_1.dir/build.make
test/nesting_ops_1: test/CMakeFiles/nesting_ops_1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable nesting_ops_1"
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/nesting_ops_1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/nesting_ops_1.dir/build: test/nesting_ops_1

.PHONY : test/CMakeFiles/nesting_ops_1.dir/build

test/CMakeFiles/nesting_ops_1.dir/requires: test/CMakeFiles/nesting_ops_1.dir/nesting_ops.cpp.o.requires

.PHONY : test/CMakeFiles/nesting_ops_1.dir/requires

test/CMakeFiles/nesting_ops_1.dir/clean:
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/test && $(CMAKE_COMMAND) -P CMakeFiles/nesting_ops_1.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/nesting_ops_1.dir/clean

test/CMakeFiles/nesting_ops_1.dir/depend:
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8 /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/test /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/test /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/test/CMakeFiles/nesting_ops_1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/nesting_ops_1.dir/depend

