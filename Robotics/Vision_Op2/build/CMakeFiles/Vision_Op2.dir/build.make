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
CMAKE_SOURCE_DIR = /home/alberto/Documentos/itesm/industrial/Vision_Op2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alberto/Documentos/itesm/industrial/Vision_Op2/build

# Include any dependencies generated for this target.
include CMakeFiles/Vision_Op2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Vision_Op2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Vision_Op2.dir/flags.make

CMakeFiles/Vision_Op2.dir/src/main.cpp.o: CMakeFiles/Vision_Op2.dir/flags.make
CMakeFiles/Vision_Op2.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alberto/Documentos/itesm/industrial/Vision_Op2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Vision_Op2.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Vision_Op2.dir/src/main.cpp.o -c /home/alberto/Documentos/itesm/industrial/Vision_Op2/src/main.cpp

CMakeFiles/Vision_Op2.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Vision_Op2.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alberto/Documentos/itesm/industrial/Vision_Op2/src/main.cpp > CMakeFiles/Vision_Op2.dir/src/main.cpp.i

CMakeFiles/Vision_Op2.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Vision_Op2.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alberto/Documentos/itesm/industrial/Vision_Op2/src/main.cpp -o CMakeFiles/Vision_Op2.dir/src/main.cpp.s

# Object files for target Vision_Op2
Vision_Op2_OBJECTS = \
"CMakeFiles/Vision_Op2.dir/src/main.cpp.o"

# External object files for target Vision_Op2
Vision_Op2_EXTERNAL_OBJECTS =

Vision_Op2: CMakeFiles/Vision_Op2.dir/src/main.cpp.o
Vision_Op2: CMakeFiles/Vision_Op2.dir/build.make
Vision_Op2: /usr/local/lib/libopencv_gapi.so.4.6.0
Vision_Op2: /usr/local/lib/libopencv_highgui.so.4.6.0
Vision_Op2: /usr/local/lib/libopencv_ml.so.4.6.0
Vision_Op2: /usr/local/lib/libopencv_objdetect.so.4.6.0
Vision_Op2: /usr/local/lib/libopencv_photo.so.4.6.0
Vision_Op2: /usr/local/lib/libopencv_stitching.so.4.6.0
Vision_Op2: /usr/local/lib/libopencv_video.so.4.6.0
Vision_Op2: /usr/local/lib/libopencv_videoio.so.4.6.0
Vision_Op2: /usr/local/lib/libopencv_imgcodecs.so.4.6.0
Vision_Op2: /usr/local/lib/libopencv_dnn.so.4.6.0
Vision_Op2: /usr/local/lib/libopencv_calib3d.so.4.6.0
Vision_Op2: /usr/local/lib/libopencv_features2d.so.4.6.0
Vision_Op2: /usr/local/lib/libopencv_flann.so.4.6.0
Vision_Op2: /usr/local/lib/libopencv_imgproc.so.4.6.0
Vision_Op2: /usr/local/lib/libopencv_core.so.4.6.0
Vision_Op2: CMakeFiles/Vision_Op2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alberto/Documentos/itesm/industrial/Vision_Op2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Vision_Op2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Vision_Op2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Vision_Op2.dir/build: Vision_Op2

.PHONY : CMakeFiles/Vision_Op2.dir/build

CMakeFiles/Vision_Op2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Vision_Op2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Vision_Op2.dir/clean

CMakeFiles/Vision_Op2.dir/depend:
	cd /home/alberto/Documentos/itesm/industrial/Vision_Op2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alberto/Documentos/itesm/industrial/Vision_Op2 /home/alberto/Documentos/itesm/industrial/Vision_Op2 /home/alberto/Documentos/itesm/industrial/Vision_Op2/build /home/alberto/Documentos/itesm/industrial/Vision_Op2/build /home/alberto/Documentos/itesm/industrial/Vision_Op2/build/CMakeFiles/Vision_Op2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Vision_Op2.dir/depend

