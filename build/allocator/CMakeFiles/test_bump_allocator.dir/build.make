# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/john/fibre-scheduler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/john/fibre-scheduler/build

# Include any dependencies generated for this target.
include allocator/CMakeFiles/test_bump_allocator.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include allocator/CMakeFiles/test_bump_allocator.dir/compiler_depend.make

# Include the progress variables for this target.
include allocator/CMakeFiles/test_bump_allocator.dir/progress.make

# Include the compile flags for this target's objects.
include allocator/CMakeFiles/test_bump_allocator.dir/flags.make

allocator/CMakeFiles/test_bump_allocator.dir/codegen:
.PHONY : allocator/CMakeFiles/test_bump_allocator.dir/codegen

allocator/CMakeFiles/test_bump_allocator.dir/test_bump_allocator.cpp.o: allocator/CMakeFiles/test_bump_allocator.dir/flags.make
allocator/CMakeFiles/test_bump_allocator.dir/test_bump_allocator.cpp.o: /Users/john/fibre-scheduler/allocator/test_bump_allocator.cpp
allocator/CMakeFiles/test_bump_allocator.dir/test_bump_allocator.cpp.o: allocator/CMakeFiles/test_bump_allocator.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/john/fibre-scheduler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object allocator/CMakeFiles/test_bump_allocator.dir/test_bump_allocator.cpp.o"
	cd /Users/john/fibre-scheduler/build/allocator && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT allocator/CMakeFiles/test_bump_allocator.dir/test_bump_allocator.cpp.o -MF CMakeFiles/test_bump_allocator.dir/test_bump_allocator.cpp.o.d -o CMakeFiles/test_bump_allocator.dir/test_bump_allocator.cpp.o -c /Users/john/fibre-scheduler/allocator/test_bump_allocator.cpp

allocator/CMakeFiles/test_bump_allocator.dir/test_bump_allocator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/test_bump_allocator.dir/test_bump_allocator.cpp.i"
	cd /Users/john/fibre-scheduler/build/allocator && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/john/fibre-scheduler/allocator/test_bump_allocator.cpp > CMakeFiles/test_bump_allocator.dir/test_bump_allocator.cpp.i

allocator/CMakeFiles/test_bump_allocator.dir/test_bump_allocator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/test_bump_allocator.dir/test_bump_allocator.cpp.s"
	cd /Users/john/fibre-scheduler/build/allocator && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/john/fibre-scheduler/allocator/test_bump_allocator.cpp -o CMakeFiles/test_bump_allocator.dir/test_bump_allocator.cpp.s

# Object files for target test_bump_allocator
test_bump_allocator_OBJECTS = \
"CMakeFiles/test_bump_allocator.dir/test_bump_allocator.cpp.o"

# External object files for target test_bump_allocator
test_bump_allocator_EXTERNAL_OBJECTS =

allocator/test_bump_allocator: allocator/CMakeFiles/test_bump_allocator.dir/test_bump_allocator.cpp.o
allocator/test_bump_allocator: allocator/CMakeFiles/test_bump_allocator.dir/build.make
allocator/test_bump_allocator: allocator/CMakeFiles/test_bump_allocator.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/john/fibre-scheduler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_bump_allocator"
	cd /Users/john/fibre-scheduler/build/allocator && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_bump_allocator.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
allocator/CMakeFiles/test_bump_allocator.dir/build: allocator/test_bump_allocator
.PHONY : allocator/CMakeFiles/test_bump_allocator.dir/build

allocator/CMakeFiles/test_bump_allocator.dir/clean:
	cd /Users/john/fibre-scheduler/build/allocator && $(CMAKE_COMMAND) -P CMakeFiles/test_bump_allocator.dir/cmake_clean.cmake
.PHONY : allocator/CMakeFiles/test_bump_allocator.dir/clean

allocator/CMakeFiles/test_bump_allocator.dir/depend:
	cd /Users/john/fibre-scheduler/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/john/fibre-scheduler /Users/john/fibre-scheduler/allocator /Users/john/fibre-scheduler/build /Users/john/fibre-scheduler/build/allocator /Users/john/fibre-scheduler/build/allocator/CMakeFiles/test_bump_allocator.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : allocator/CMakeFiles/test_bump_allocator.dir/depend

