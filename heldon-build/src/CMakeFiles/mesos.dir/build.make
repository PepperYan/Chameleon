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
include src/CMakeFiles/mesos.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/mesos.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/mesos.dir/flags.make

src/messages/mesos.pb.cc:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/lemaker/open-source/Chameleon/heldon-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating messages/mesos.pb.cc, messages/mesos.pb.h"
	cd /home/lemaker/open-source/Chameleon/heldon-build/src && ../3rdparty/protobuf_2_6/bin/protoc --cpp_out=/home/lemaker/open-source/Chameleon/heldon-build/src/messages --proto_path=/home/lemaker/open-source/Chameleon/src/messages /home/lemaker/open-source/Chameleon/src/messages/mesos.proto

src/messages/mesos.pb.h: src/messages/mesos.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate src/messages/mesos.pb.h

src/CMakeFiles/mesos.dir/messages/mesos.pb.cc.o: src/CMakeFiles/mesos.dir/flags.make
src/CMakeFiles/mesos.dir/messages/mesos.pb.cc.o: src/messages/mesos.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/lemaker/open-source/Chameleon/heldon-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/mesos.dir/messages/mesos.pb.cc.o"
	cd /home/lemaker/open-source/Chameleon/heldon-build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mesos.dir/messages/mesos.pb.cc.o -c /home/lemaker/open-source/Chameleon/heldon-build/src/messages/mesos.pb.cc

src/CMakeFiles/mesos.dir/messages/mesos.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mesos.dir/messages/mesos.pb.cc.i"
	cd /home/lemaker/open-source/Chameleon/heldon-build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lemaker/open-source/Chameleon/heldon-build/src/messages/mesos.pb.cc > CMakeFiles/mesos.dir/messages/mesos.pb.cc.i

src/CMakeFiles/mesos.dir/messages/mesos.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mesos.dir/messages/mesos.pb.cc.s"
	cd /home/lemaker/open-source/Chameleon/heldon-build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lemaker/open-source/Chameleon/heldon-build/src/messages/mesos.pb.cc -o CMakeFiles/mesos.dir/messages/mesos.pb.cc.s

# Object files for target mesos
mesos_OBJECTS = \
"CMakeFiles/mesos.dir/messages/mesos.pb.cc.o"

# External object files for target mesos
mesos_EXTERNAL_OBJECTS =

src/libmesos.a: src/CMakeFiles/mesos.dir/messages/mesos.pb.cc.o
src/libmesos.a: src/CMakeFiles/mesos.dir/build.make
src/libmesos.a: src/CMakeFiles/mesos.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/lemaker/open-source/Chameleon/heldon-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libmesos.a"
	cd /home/lemaker/open-source/Chameleon/heldon-build/src && $(CMAKE_COMMAND) -P CMakeFiles/mesos.dir/cmake_clean_target.cmake
	cd /home/lemaker/open-source/Chameleon/heldon-build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mesos.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/mesos.dir/build: src/libmesos.a

.PHONY : src/CMakeFiles/mesos.dir/build

src/CMakeFiles/mesos.dir/clean:
	cd /home/lemaker/open-source/Chameleon/heldon-build/src && $(CMAKE_COMMAND) -P CMakeFiles/mesos.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/mesos.dir/clean

src/CMakeFiles/mesos.dir/depend: src/messages/mesos.pb.cc
src/CMakeFiles/mesos.dir/depend: src/messages/mesos.pb.h
	cd /home/lemaker/open-source/Chameleon/heldon-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lemaker/open-source/Chameleon /home/lemaker/open-source/Chameleon/src /home/lemaker/open-source/Chameleon/heldon-build /home/lemaker/open-source/Chameleon/heldon-build/src /home/lemaker/open-source/Chameleon/heldon-build/src/CMakeFiles/mesos.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/mesos.dir/depend
