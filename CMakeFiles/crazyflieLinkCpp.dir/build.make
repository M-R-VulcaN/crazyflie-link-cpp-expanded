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
CMAKE_SOURCE_DIR = /home/makeruser/nitay/crazyflie-link-cpp-expanded

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/makeruser/nitay/crazyflie-link-cpp-expanded

# Include any dependencies generated for this target.
include CMakeFiles/crazyflieLinkCpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/crazyflieLinkCpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/crazyflieLinkCpp.dir/flags.make

CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.o: CMakeFiles/crazyflieLinkCpp.dir/flags.make
CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.o: src/USBManager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/makeruser/nitay/crazyflie-link-cpp-expanded/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.o -c /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/USBManager.cpp

CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/USBManager.cpp > CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.i

CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/USBManager.cpp -o CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.s

CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.o.requires:

.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.o.requires

CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.o.provides: CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.o.requires
	$(MAKE) -f CMakeFiles/crazyflieLinkCpp.dir/build.make CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.o.provides.build
.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.o.provides

CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.o.provides.build: CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.o


CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.o: CMakeFiles/crazyflieLinkCpp.dir/flags.make
CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.o: src/Connection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/makeruser/nitay/crazyflie-link-cpp-expanded/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.o -c /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/Connection.cpp

CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/Connection.cpp > CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.i

CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/Connection.cpp -o CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.s

CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.o.requires:

.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.o.requires

CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.o.provides: CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.o.requires
	$(MAKE) -f CMakeFiles/crazyflieLinkCpp.dir/build.make CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.o.provides.build
.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.o.provides

CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.o.provides.build: CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.o


CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.o: CMakeFiles/crazyflieLinkCpp.dir/flags.make
CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.o: src/USBDevice.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/makeruser/nitay/crazyflie-link-cpp-expanded/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.o -c /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/USBDevice.cpp

CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/USBDevice.cpp > CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.i

CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/USBDevice.cpp -o CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.s

CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.o.requires:

.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.o.requires

CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.o.provides: CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.o.requires
	$(MAKE) -f CMakeFiles/crazyflieLinkCpp.dir/build.make CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.o.provides.build
.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.o.provides

CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.o.provides.build: CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.o


CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.o: CMakeFiles/crazyflieLinkCpp.dir/flags.make
CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.o: src/Crazyradio.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/makeruser/nitay/crazyflie-link-cpp-expanded/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.o -c /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/Crazyradio.cpp

CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/Crazyradio.cpp > CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.i

CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/Crazyradio.cpp -o CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.s

CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.o.requires:

.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.o.requires

CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.o.provides: CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.o.requires
	$(MAKE) -f CMakeFiles/crazyflieLinkCpp.dir/build.make CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.o.provides.build
.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.o.provides

CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.o.provides.build: CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.o


CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.o: CMakeFiles/crazyflieLinkCpp.dir/flags.make
CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.o: src/CrazyradioThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/makeruser/nitay/crazyflie-link-cpp-expanded/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.o -c /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/CrazyradioThread.cpp

CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/CrazyradioThread.cpp > CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.i

CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/CrazyradioThread.cpp -o CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.s

CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.o.requires:

.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.o.requires

CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.o.provides: CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.o.requires
	$(MAKE) -f CMakeFiles/crazyflieLinkCpp.dir/build.make CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.o.provides.build
.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.o.provides

CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.o.provides.build: CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.o


CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.o: CMakeFiles/crazyflieLinkCpp.dir/flags.make
CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.o: src/CrazyflieUSB.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/makeruser/nitay/crazyflie-link-cpp-expanded/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.o -c /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/CrazyflieUSB.cpp

CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/CrazyflieUSB.cpp > CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.i

CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/CrazyflieUSB.cpp -o CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.s

CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.o.requires:

.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.o.requires

CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.o.provides: CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.o.requires
	$(MAKE) -f CMakeFiles/crazyflieLinkCpp.dir/build.make CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.o.provides.build
.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.o.provides

CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.o.provides.build: CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.o


CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.o: CMakeFiles/crazyflieLinkCpp.dir/flags.make
CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.o: src/CrazyflieUSBThread.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/makeruser/nitay/crazyflie-link-cpp-expanded/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.o -c /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/CrazyflieUSBThread.cpp

CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/CrazyflieUSBThread.cpp > CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.i

CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/CrazyflieUSBThread.cpp -o CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.s

CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.o.requires:

.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.o.requires

CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.o.provides: CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.o.requires
	$(MAKE) -f CMakeFiles/crazyflieLinkCpp.dir/build.make CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.o.provides.build
.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.o.provides

CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.o.provides.build: CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.o


CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.o: CMakeFiles/crazyflieLinkCpp.dir/flags.make
CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.o: src/Version.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/makeruser/nitay/crazyflie-link-cpp-expanded/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.o -c /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/Version.cpp

CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/Version.cpp > CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.i

CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/Version.cpp -o CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.s

CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.o.requires:

.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.o.requires

CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.o.provides: CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.o.requires
	$(MAKE) -f CMakeFiles/crazyflieLinkCpp.dir/build.make CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.o.provides.build
.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.o.provides

CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.o.provides.build: CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.o


CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.o: CMakeFiles/crazyflieLinkCpp.dir/flags.make
CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.o: src/Toc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/makeruser/nitay/crazyflie-link-cpp-expanded/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.o -c /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/Toc.cpp

CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/Toc.cpp > CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.i

CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/Toc.cpp -o CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.s

CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.o.requires:

.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.o.requires

CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.o.provides: CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.o.requires
	$(MAKE) -f CMakeFiles/crazyflieLinkCpp.dir/build.make CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.o.provides.build
.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.o.provides

CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.o.provides.build: CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.o


CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.o: CMakeFiles/crazyflieLinkCpp.dir/flags.make
CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.o: src/Param.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/makeruser/nitay/crazyflie-link-cpp-expanded/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.o -c /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/Param.cpp

CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/Param.cpp > CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.i

CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/Param.cpp -o CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.s

CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.o.requires:

.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.o.requires

CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.o.provides: CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.o.requires
	$(MAKE) -f CMakeFiles/crazyflieLinkCpp.dir/build.make CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.o.provides.build
.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.o.provides

CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.o.provides.build: CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.o


CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.o: CMakeFiles/crazyflieLinkCpp.dir/flags.make
CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.o: src/ConnectionWrapper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/makeruser/nitay/crazyflie-link-cpp-expanded/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.o -c /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/ConnectionWrapper.cpp

CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/ConnectionWrapper.cpp > CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.i

CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/makeruser/nitay/crazyflie-link-cpp-expanded/src/ConnectionWrapper.cpp -o CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.s

CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.o.requires:

.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.o.requires

CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.o.provides: CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.o.requires
	$(MAKE) -f CMakeFiles/crazyflieLinkCpp.dir/build.make CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.o.provides.build
.PHONY : CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.o.provides

CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.o.provides.build: CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.o


# Object files for target crazyflieLinkCpp
crazyflieLinkCpp_OBJECTS = \
"CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.o" \
"CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.o" \
"CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.o" \
"CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.o" \
"CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.o" \
"CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.o" \
"CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.o" \
"CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.o" \
"CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.o" \
"CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.o" \
"CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.o"

# External object files for target crazyflieLinkCpp
crazyflieLinkCpp_EXTERNAL_OBJECTS =

libcrazyflieLinkCpp.a: CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.o
libcrazyflieLinkCpp.a: CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.o
libcrazyflieLinkCpp.a: CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.o
libcrazyflieLinkCpp.a: CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.o
libcrazyflieLinkCpp.a: CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.o
libcrazyflieLinkCpp.a: CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.o
libcrazyflieLinkCpp.a: CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.o
libcrazyflieLinkCpp.a: CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.o
libcrazyflieLinkCpp.a: CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.o
libcrazyflieLinkCpp.a: CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.o
libcrazyflieLinkCpp.a: CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.o
libcrazyflieLinkCpp.a: CMakeFiles/crazyflieLinkCpp.dir/build.make
libcrazyflieLinkCpp.a: CMakeFiles/crazyflieLinkCpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/makeruser/nitay/crazyflie-link-cpp-expanded/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Linking CXX static library libcrazyflieLinkCpp.a"
	$(CMAKE_COMMAND) -P CMakeFiles/crazyflieLinkCpp.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crazyflieLinkCpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/crazyflieLinkCpp.dir/build: libcrazyflieLinkCpp.a

.PHONY : CMakeFiles/crazyflieLinkCpp.dir/build

CMakeFiles/crazyflieLinkCpp.dir/requires: CMakeFiles/crazyflieLinkCpp.dir/src/USBManager.cpp.o.requires
CMakeFiles/crazyflieLinkCpp.dir/requires: CMakeFiles/crazyflieLinkCpp.dir/src/Connection.cpp.o.requires
CMakeFiles/crazyflieLinkCpp.dir/requires: CMakeFiles/crazyflieLinkCpp.dir/src/USBDevice.cpp.o.requires
CMakeFiles/crazyflieLinkCpp.dir/requires: CMakeFiles/crazyflieLinkCpp.dir/src/Crazyradio.cpp.o.requires
CMakeFiles/crazyflieLinkCpp.dir/requires: CMakeFiles/crazyflieLinkCpp.dir/src/CrazyradioThread.cpp.o.requires
CMakeFiles/crazyflieLinkCpp.dir/requires: CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSB.cpp.o.requires
CMakeFiles/crazyflieLinkCpp.dir/requires: CMakeFiles/crazyflieLinkCpp.dir/src/CrazyflieUSBThread.cpp.o.requires
CMakeFiles/crazyflieLinkCpp.dir/requires: CMakeFiles/crazyflieLinkCpp.dir/src/Version.cpp.o.requires
CMakeFiles/crazyflieLinkCpp.dir/requires: CMakeFiles/crazyflieLinkCpp.dir/src/Toc.cpp.o.requires
CMakeFiles/crazyflieLinkCpp.dir/requires: CMakeFiles/crazyflieLinkCpp.dir/src/Param.cpp.o.requires
CMakeFiles/crazyflieLinkCpp.dir/requires: CMakeFiles/crazyflieLinkCpp.dir/src/ConnectionWrapper.cpp.o.requires

.PHONY : CMakeFiles/crazyflieLinkCpp.dir/requires

CMakeFiles/crazyflieLinkCpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/crazyflieLinkCpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/crazyflieLinkCpp.dir/clean

CMakeFiles/crazyflieLinkCpp.dir/depend:
	cd /home/makeruser/nitay/crazyflie-link-cpp-expanded && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/makeruser/nitay/crazyflie-link-cpp-expanded /home/makeruser/nitay/crazyflie-link-cpp-expanded /home/makeruser/nitay/crazyflie-link-cpp-expanded /home/makeruser/nitay/crazyflie-link-cpp-expanded /home/makeruser/nitay/crazyflie-link-cpp-expanded/CMakeFiles/crazyflieLinkCpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/crazyflieLinkCpp.dir/depend

