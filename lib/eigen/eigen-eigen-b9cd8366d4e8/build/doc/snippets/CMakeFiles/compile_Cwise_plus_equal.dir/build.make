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
include doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/depend.make

# Include the progress variables for this target.
include doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/progress.make

# Include the compile flags for this target's objects.
include doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/flags.make

doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o: doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/flags.make
doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o: doc/snippets/compile_Cwise_plus_equal.cpp
doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o: ../doc/snippets/Cwise_plus_equal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o"
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/doc/snippets && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o -c /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/doc/snippets/compile_Cwise_plus_equal.cpp

doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.i"
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/doc/snippets && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/doc/snippets/compile_Cwise_plus_equal.cpp > CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.i

doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.s"
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/doc/snippets && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/doc/snippets/compile_Cwise_plus_equal.cpp -o CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.s

doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o.requires:

.PHONY : doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o.requires

doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o.provides: doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o.requires
	$(MAKE) -f doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/build.make doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o.provides.build
.PHONY : doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o.provides

doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o.provides.build: doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o


# Object files for target compile_Cwise_plus_equal
compile_Cwise_plus_equal_OBJECTS = \
"CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o"

# External object files for target compile_Cwise_plus_equal
compile_Cwise_plus_equal_EXTERNAL_OBJECTS =

doc/snippets/compile_Cwise_plus_equal: doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o
doc/snippets/compile_Cwise_plus_equal: doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/build.make
doc/snippets/compile_Cwise_plus_equal: doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable compile_Cwise_plus_equal"
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/doc/snippets && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compile_Cwise_plus_equal.dir/link.txt --verbose=$(VERBOSE)
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/doc/snippets && ./compile_Cwise_plus_equal >/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/doc/snippets/Cwise_plus_equal.out

# Rule to build all files generated by this target.
doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/build: doc/snippets/compile_Cwise_plus_equal

.PHONY : doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/build

doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/requires: doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/compile_Cwise_plus_equal.cpp.o.requires

.PHONY : doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/requires

doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/clean:
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/doc/snippets && $(CMAKE_COMMAND) -P CMakeFiles/compile_Cwise_plus_equal.dir/cmake_clean.cmake
.PHONY : doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/clean

doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/depend:
	cd /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8 /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/doc/snippets /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/doc/snippets /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/build/doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/snippets/CMakeFiles/compile_Cwise_plus_equal.dir/depend

