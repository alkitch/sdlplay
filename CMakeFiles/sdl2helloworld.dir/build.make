# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_SOURCE_DIR = /home/pi/Projects/sdl/sdlplay

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Projects/sdl/sdlplay

# Include any dependencies generated for this target.
include CMakeFiles/sdl2helloworld.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sdl2helloworld.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sdl2helloworld.dir/flags.make

CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.o: CMakeFiles/sdl2helloworld.dir/flags.make
CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.o: sdl2helloworld.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Projects/sdl/sdlplay/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.o -c /home/pi/Projects/sdl/sdlplay/sdl2helloworld.cpp

CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Projects/sdl/sdlplay/sdl2helloworld.cpp > CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.i

CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Projects/sdl/sdlplay/sdl2helloworld.cpp -o CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.s

CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.o.requires:

.PHONY : CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.o.requires

CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.o.provides: CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.o.requires
	$(MAKE) -f CMakeFiles/sdl2helloworld.dir/build.make CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.o.provides.build
.PHONY : CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.o.provides

CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.o.provides.build: CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.o


# Object files for target sdl2helloworld
sdl2helloworld_OBJECTS = \
"CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.o"

# External object files for target sdl2helloworld
sdl2helloworld_EXTERNAL_OBJECTS =

sdl2helloworld: CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.o
sdl2helloworld: CMakeFiles/sdl2helloworld.dir/build.make
sdl2helloworld: /usr/lib/arm-linux-gnueabihf/libSDL2_ttf.so
sdl2helloworld: /usr/lib/arm-linux-gnueabihf/libSDL2_ttf.so
sdl2helloworld: /usr/lib/arm-linux-gnueabihf/libSDL2_ttf.so
sdl2helloworld: /usr/lib/arm-linux-gnueabihf/libSDL2_ttf.so
sdl2helloworld: CMakeFiles/sdl2helloworld.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Projects/sdl/sdlplay/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sdl2helloworld"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sdl2helloworld.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sdl2helloworld.dir/build: sdl2helloworld

.PHONY : CMakeFiles/sdl2helloworld.dir/build

CMakeFiles/sdl2helloworld.dir/requires: CMakeFiles/sdl2helloworld.dir/sdl2helloworld.cpp.o.requires

.PHONY : CMakeFiles/sdl2helloworld.dir/requires

CMakeFiles/sdl2helloworld.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sdl2helloworld.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sdl2helloworld.dir/clean

CMakeFiles/sdl2helloworld.dir/depend:
	cd /home/pi/Projects/sdl/sdlplay && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Projects/sdl/sdlplay /home/pi/Projects/sdl/sdlplay /home/pi/Projects/sdl/sdlplay /home/pi/Projects/sdl/sdlplay /home/pi/Projects/sdl/sdlplay/CMakeFiles/sdl2helloworld.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sdl2helloworld.dir/depend

