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
include CMakeFiles/sdlplay.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/sdlplay.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sdlplay.dir/flags.make

CMakeFiles/sdlplay.dir/sdl2play.cpp.o: CMakeFiles/sdlplay.dir/flags.make
CMakeFiles/sdlplay.dir/sdl2play.cpp.o: sdl2play.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pi/Projects/sdl/sdlplay/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sdlplay.dir/sdl2play.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sdlplay.dir/sdl2play.cpp.o -c /home/pi/Projects/sdl/sdlplay/sdl2play.cpp

CMakeFiles/sdlplay.dir/sdl2play.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sdlplay.dir/sdl2play.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pi/Projects/sdl/sdlplay/sdl2play.cpp > CMakeFiles/sdlplay.dir/sdl2play.cpp.i

CMakeFiles/sdlplay.dir/sdl2play.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sdlplay.dir/sdl2play.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pi/Projects/sdl/sdlplay/sdl2play.cpp -o CMakeFiles/sdlplay.dir/sdl2play.cpp.s

CMakeFiles/sdlplay.dir/sdl2play.cpp.o.requires:

.PHONY : CMakeFiles/sdlplay.dir/sdl2play.cpp.o.requires

CMakeFiles/sdlplay.dir/sdl2play.cpp.o.provides: CMakeFiles/sdlplay.dir/sdl2play.cpp.o.requires
	$(MAKE) -f CMakeFiles/sdlplay.dir/build.make CMakeFiles/sdlplay.dir/sdl2play.cpp.o.provides.build
.PHONY : CMakeFiles/sdlplay.dir/sdl2play.cpp.o.provides

CMakeFiles/sdlplay.dir/sdl2play.cpp.o.provides.build: CMakeFiles/sdlplay.dir/sdl2play.cpp.o


# Object files for target sdlplay
sdlplay_OBJECTS = \
"CMakeFiles/sdlplay.dir/sdl2play.cpp.o"

# External object files for target sdlplay
sdlplay_EXTERNAL_OBJECTS =

sdlplay: CMakeFiles/sdlplay.dir/sdl2play.cpp.o
sdlplay: CMakeFiles/sdlplay.dir/build.make
sdlplay: CMakeFiles/sdlplay.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pi/Projects/sdl/sdlplay/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sdlplay"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sdlplay.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sdlplay.dir/build: sdlplay

.PHONY : CMakeFiles/sdlplay.dir/build

CMakeFiles/sdlplay.dir/requires: CMakeFiles/sdlplay.dir/sdl2play.cpp.o.requires

.PHONY : CMakeFiles/sdlplay.dir/requires

CMakeFiles/sdlplay.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sdlplay.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sdlplay.dir/clean

CMakeFiles/sdlplay.dir/depend:
	cd /home/pi/Projects/sdl/sdlplay && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pi/Projects/sdl/sdlplay /home/pi/Projects/sdl/sdlplay /home/pi/Projects/sdl/sdlplay /home/pi/Projects/sdl/sdlplay /home/pi/Projects/sdl/sdlplay/CMakeFiles/sdlplay.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sdlplay.dir/depend

