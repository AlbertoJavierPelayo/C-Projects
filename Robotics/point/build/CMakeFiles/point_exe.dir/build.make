# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/student/Documents/itesm/industrial/point

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/student/Documents/itesm/industrial/point/build

# Include any dependencies generated for this target.
include CMakeFiles/point_exe.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/point_exe.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/point_exe.dir/flags.make

CMakeFiles/point_exe.dir/src/main.cpp.o: CMakeFiles/point_exe.dir/flags.make
CMakeFiles/point_exe.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/Documents/itesm/industrial/point/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/point_exe.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/point_exe.dir/src/main.cpp.o -c /home/student/Documents/itesm/industrial/point/src/main.cpp

CMakeFiles/point_exe.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/point_exe.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/student/Documents/itesm/industrial/point/src/main.cpp > CMakeFiles/point_exe.dir/src/main.cpp.i

CMakeFiles/point_exe.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/point_exe.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/student/Documents/itesm/industrial/point/src/main.cpp -o CMakeFiles/point_exe.dir/src/main.cpp.s

CMakeFiles/point_exe.dir/src/point.cpp.o: CMakeFiles/point_exe.dir/flags.make
CMakeFiles/point_exe.dir/src/point.cpp.o: ../src/point.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/student/Documents/itesm/industrial/point/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/point_exe.dir/src/point.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/point_exe.dir/src/point.cpp.o -c /home/student/Documents/itesm/industrial/point/src/point.cpp

CMakeFiles/point_exe.dir/src/point.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/point_exe.dir/src/point.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/student/Documents/itesm/industrial/point/src/point.cpp > CMakeFiles/point_exe.dir/src/point.cpp.i

CMakeFiles/point_exe.dir/src/point.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/point_exe.dir/src/point.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/student/Documents/itesm/industrial/point/src/point.cpp -o CMakeFiles/point_exe.dir/src/point.cpp.s

# Object files for target point_exe
point_exe_OBJECTS = \
"CMakeFiles/point_exe.dir/src/main.cpp.o" \
"CMakeFiles/point_exe.dir/src/point.cpp.o"

# External object files for target point_exe
point_exe_EXTERNAL_OBJECTS =

point_exe: CMakeFiles/point_exe.dir/src/main.cpp.o
point_exe: CMakeFiles/point_exe.dir/src/point.cpp.o
point_exe: CMakeFiles/point_exe.dir/build.make
point_exe: CMakeFiles/point_exe.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/student/Documents/itesm/industrial/point/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable point_exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/point_exe.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/point_exe.dir/build: point_exe

.PHONY : CMakeFiles/point_exe.dir/build

CMakeFiles/point_exe.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/point_exe.dir/cmake_clean.cmake
.PHONY : CMakeFiles/point_exe.dir/clean

CMakeFiles/point_exe.dir/depend:
	cd /home/student/Documents/itesm/industrial/point/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/student/Documents/itesm/industrial/point /home/student/Documents/itesm/industrial/point /home/student/Documents/itesm/industrial/point/build /home/student/Documents/itesm/industrial/point/build /home/student/Documents/itesm/industrial/point/build/CMakeFiles/point_exe.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/point_exe.dir/depend

