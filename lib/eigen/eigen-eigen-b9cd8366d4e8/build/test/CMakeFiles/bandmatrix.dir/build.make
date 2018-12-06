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
include test/CMakeFiles/bandmatrix.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/bandmatrix.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/bandmatrix.dir/flags.make

test/CMakeFiles/bandmatrix.dir/bandmatrix.cpp.o: test/CMakeFiles/bandmatrix.dir/flags.make
test/CMakeFiles/bandmatrix.dir/bandmatrix.cpp.o: ../test/bandmatrix.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/bandmatrix.dir/bandmatrix.cpp.o"
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bandmatrix.dir/bandmatrix.cpp.o -c /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/test/bandmatrix.cpp

test/CMakeFiles/bandmatrix.dir/bandmatrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bandmatrix.dir/bandmatrix.cpp.i"
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/test/bandmatrix.cpp > CMakeFiles/bandmatrix.dir/bandmatrix.cpp.i

test/CMakeFiles/bandmatrix.dir/bandmatrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bandmatrix.dir/bandmatrix.cpp.s"
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/test/bandmatrix.cpp -o CMakeFiles/bandmatrix.dir/bandmatrix.cpp.s

test/CMakeFiles/bandmatrix.dir/bandmatrix.cpp.o.requires:

.PHONY : test/CMakeFiles/bandmatrix.dir/bandmatrix.cpp.o.requires

test/CMakeFiles/bandmatrix.dir/bandmatrix.cpp.o.provides: test/CMakeFiles/bandmatrix.dir/bandmatrix.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/bandmatrix.dir/build.make test/CMakeFiles/bandmatrix.dir/bandmatrix.cpp.o.provides.build
.PHONY : test/CMakeFiles/bandmatrix.dir/bandmatrix.cpp.o.provides

test/CMakeFiles/bandmatrix.dir/bandmatrix.cpp.o.provides.build: test/CMakeFiles/bandmatrix.dir/bandmatrix.cpp.o


# Object files for target bandmatrix
bandmatrix_OBJECTS = \
"CMakeFiles/bandmatrix.dir/bandmatrix.cpp.o"

# External object files for target bandmatrix
bandmatrix_EXTERNAL_OBJECTS =

test/bandmatrix: test/CMakeFiles/bandmatrix.dir/bandmatrix.cpp.o
test/bandmatrix: test/CMakeFiles/bandmatrix.dir/build.make
test/bandmatrix: test/CMakeFiles/bandmatrix.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bandmatrix"
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bandmatrix.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/bandmatrix.dir/build: test/bandmatrix

.PHONY : test/CMakeFiles/bandmatrix.dir/build

test/CMakeFiles/bandmatrix.dir/requires: test/CMakeFiles/bandmatrix.dir/bandmatrix.cpp.o.requires

.PHONY : test/CMakeFiles/bandmatrix.dir/requires

test/CMakeFiles/bandmatrix.dir/clean:
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/test && $(CMAKE_COMMAND) -P CMakeFiles/bandmatrix.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/bandmatrix.dir/clean

test/CMakeFiles/bandmatrix.dir/depend:
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8 /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/test /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/test /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/test/CMakeFiles/bandmatrix.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/bandmatrix.dir/depend

