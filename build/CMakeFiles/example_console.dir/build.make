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
CMAKE_SOURCE_DIR = /home/makers/crazyflie-link-cpp-expanded

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/makers/crazyflie-link-cpp-expanded/build

# Include any dependencies generated for this target.
include CMakeFiles/example_console.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/example_console.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/example_console.dir/flags.make

CMakeFiles/example_console.dir/examples/console.cpp.o: CMakeFiles/example_console.dir/flags.make
CMakeFiles/example_console.dir/examples/console.cpp.o: ../examples/console.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/makers/crazyflie-link-cpp-expanded/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/example_console.dir/examples/console.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example_console.dir/examples/console.cpp.o -c /home/makers/crazyflie-link-cpp-expanded/examples/console.cpp

CMakeFiles/example_console.dir/examples/console.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example_console.dir/examples/console.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/makers/crazyflie-link-cpp-expanded/examples/console.cpp > CMakeFiles/example_console.dir/examples/console.cpp.i

CMakeFiles/example_console.dir/examples/console.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example_console.dir/examples/console.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/makers/crazyflie-link-cpp-expanded/examples/console.cpp -o CMakeFiles/example_console.dir/examples/console.cpp.s

CMakeFiles/example_console.dir/examples/console.cpp.o.requires:

.PHONY : CMakeFiles/example_console.dir/examples/console.cpp.o.requires

CMakeFiles/example_console.dir/examples/console.cpp.o.provides: CMakeFiles/example_console.dir/examples/console.cpp.o.requires
	$(MAKE) -f CMakeFiles/example_console.dir/build.make CMakeFiles/example_console.dir/examples/console.cpp.o.provides.build
.PHONY : CMakeFiles/example_console.dir/examples/console.cpp.o.provides

CMakeFiles/example_console.dir/examples/console.cpp.o.provides.build: CMakeFiles/example_console.dir/examples/console.cpp.o


# Object files for target example_console
example_console_OBJECTS = \
"CMakeFiles/example_console.dir/examples/console.cpp.o"

# External object files for target example_console
example_console_EXTERNAL_OBJECTS =

example_console: CMakeFiles/example_console.dir/examples/console.cpp.o
example_console: CMakeFiles/example_console.dir/build.make
example_console: libcrazyflieLinkCpp.a
example_console: /usr/lib/x86_64-linux-gnu/libusb-1.0.so
example_console: CMakeFiles/example_console.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/makers/crazyflie-link-cpp-expanded/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable example_console"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example_console.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/example_console.dir/build: example_console

.PHONY : CMakeFiles/example_console.dir/build

CMakeFiles/example_console.dir/requires: CMakeFiles/example_console.dir/examples/console.cpp.o.requires

.PHONY : CMakeFiles/example_console.dir/requires

CMakeFiles/example_console.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/example_console.dir/cmake_clean.cmake
.PHONY : CMakeFiles/example_console.dir/clean

CMakeFiles/example_console.dir/depend:
	cd /home/makers/crazyflie-link-cpp-expanded/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/makers/crazyflie-link-cpp-expanded /home/makers/crazyflie-link-cpp-expanded /home/makers/crazyflie-link-cpp-expanded/build /home/makers/crazyflie-link-cpp-expanded/build /home/makers/crazyflie-link-cpp-expanded/build/CMakeFiles/example_console.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/example_console.dir/depend

