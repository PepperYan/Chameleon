# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /home/lemaker/software/clion-2018.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/lemaker/software/clion-2018.2.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lemaker/open-source/Chameleon

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lemaker/open-source/Chameleon/heldon-build

# Include any dependencies generated for this target.
include src/slave/CMakeFiles/docker_launch.dir/depend.make

# Include the progress variables for this target.
include src/slave/CMakeFiles/docker_launch.dir/progress.make

# Include the compile flags for this target's objects.
include src/slave/CMakeFiles/docker_launch.dir/flags.make

src/slave/CMakeFiles/docker_launch.dir/docker_launch.cpp.o: src/slave/CMakeFiles/docker_launch.dir/flags.make
src/slave/CMakeFiles/docker_launch.dir/docker_launch.cpp.o: ../src/slave/docker_launch.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lemaker/open-source/Chameleon/heldon-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/slave/CMakeFiles/docker_launch.dir/docker_launch.cpp.o"
	cd /home/lemaker/open-source/Chameleon/heldon-build/src/slave && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/docker_launch.dir/docker_launch.cpp.o -c /home/lemaker/open-source/Chameleon/src/slave/docker_launch.cpp

src/slave/CMakeFiles/docker_launch.dir/docker_launch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/docker_launch.dir/docker_launch.cpp.i"
	cd /home/lemaker/open-source/Chameleon/heldon-build/src/slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lemaker/open-source/Chameleon/src/slave/docker_launch.cpp > CMakeFiles/docker_launch.dir/docker_launch.cpp.i

src/slave/CMakeFiles/docker_launch.dir/docker_launch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/docker_launch.dir/docker_launch.cpp.s"
	cd /home/lemaker/open-source/Chameleon/heldon-build/src/slave && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lemaker/open-source/Chameleon/src/slave/docker_launch.cpp -o CMakeFiles/docker_launch.dir/docker_launch.cpp.s

# Object files for target docker_launch
docker_launch_OBJECTS = \
"CMakeFiles/docker_launch.dir/docker_launch.cpp.o"

# External object files for target docker_launch
docker_launch_EXTERNAL_OBJECTS =

src/slave/docker_launch: src/slave/CMakeFiles/docker_launch.dir/docker_launch.cpp.o
src/slave/docker_launch: src/slave/CMakeFiles/docker_launch.dir/build.make
src/slave/docker_launch: /home/heldon/chameleon/mesos/mesos-1.3.2/build/src/.libs/libmesos-1.3.2.so
src/slave/docker_launch: /usr/lib/x86_64-linux-gnu/libapr-1.so
src/slave/docker_launch: /usr/lib/x86_64-linux-gnu/libz.so
src/slave/docker_launch: /usr/lib/x86_64-linux-gnu/libapr-1.so
src/slave/docker_launch: /usr/lib/x86_64-linux-gnu/libz.so
src/slave/docker_launch: /usr/lib/x86_64-linux-gnu/libapr-1.so
src/slave/docker_launch: /usr/lib/x86_64-linux-gnu/libz.so
src/slave/docker_launch: src/slave/CMakeFiles/docker_launch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lemaker/open-source/Chameleon/heldon-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable docker_launch"
	cd /home/lemaker/open-source/Chameleon/heldon-build/src/slave && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/docker_launch.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/slave/CMakeFiles/docker_launch.dir/build: src/slave/docker_launch

.PHONY : src/slave/CMakeFiles/docker_launch.dir/build

src/slave/CMakeFiles/docker_launch.dir/clean:
	cd /home/lemaker/open-source/Chameleon/heldon-build/src/slave && $(CMAKE_COMMAND) -P CMakeFiles/docker_launch.dir/cmake_clean.cmake
.PHONY : src/slave/CMakeFiles/docker_launch.dir/clean

src/slave/CMakeFiles/docker_launch.dir/depend:
	cd /home/lemaker/open-source/Chameleon/heldon-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lemaker/open-source/Chameleon /home/lemaker/open-source/Chameleon/src/slave /home/lemaker/open-source/Chameleon/heldon-build /home/lemaker/open-source/Chameleon/heldon-build/src/slave /home/lemaker/open-source/Chameleon/heldon-build/src/slave/CMakeFiles/docker_launch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/slave/CMakeFiles/docker_launch.dir/depend
