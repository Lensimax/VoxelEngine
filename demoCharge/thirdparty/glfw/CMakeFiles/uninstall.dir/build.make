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
CMAKE_SOURCE_DIR = /home/thespygeek/Demonstration/voxelEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thespygeek/Demonstration/voxelEngine/build

# Utility rule file for uninstall.

# Include the progress variables for this target.
include thirdparty/glfw/CMakeFiles/uninstall.dir/progress.make

thirdparty/glfw/CMakeFiles/uninstall:
	cd /home/thespygeek/Demonstration/voxelEngine/build/thirdparty/glfw && /usr/bin/cmake -P /home/thespygeek/Demonstration/voxelEngine/build/thirdparty/glfw/cmake_uninstall.cmake

uninstall: thirdparty/glfw/CMakeFiles/uninstall
uninstall: thirdparty/glfw/CMakeFiles/uninstall.dir/build.make

.PHONY : uninstall

# Rule to build all files generated by this target.
thirdparty/glfw/CMakeFiles/uninstall.dir/build: uninstall

.PHONY : thirdparty/glfw/CMakeFiles/uninstall.dir/build

thirdparty/glfw/CMakeFiles/uninstall.dir/clean:
	cd /home/thespygeek/Demonstration/voxelEngine/build/thirdparty/glfw && $(CMAKE_COMMAND) -P CMakeFiles/uninstall.dir/cmake_clean.cmake
.PHONY : thirdparty/glfw/CMakeFiles/uninstall.dir/clean

thirdparty/glfw/CMakeFiles/uninstall.dir/depend:
	cd /home/thespygeek/Demonstration/voxelEngine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thespygeek/Demonstration/voxelEngine /home/thespygeek/Demonstration/voxelEngine/thirdparty/glfw /home/thespygeek/Demonstration/voxelEngine/build /home/thespygeek/Demonstration/voxelEngine/build/thirdparty/glfw /home/thespygeek/Demonstration/voxelEngine/build/thirdparty/glfw/CMakeFiles/uninstall.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : thirdparty/glfw/CMakeFiles/uninstall.dir/depend

