# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/jachinshen/Projects/Cpp/Opencv/YellowLine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jachinshen/Projects/Cpp/Opencv/YellowLine/build

# Include any dependencies generated for this target.
include CMakeFiles/YellowLine.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/YellowLine.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/YellowLine.dir/flags.make

CMakeFiles/YellowLine.dir/src/YellowLine.cpp.o: CMakeFiles/YellowLine.dir/flags.make
CMakeFiles/YellowLine.dir/src/YellowLine.cpp.o: ../src/YellowLine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jachinshen/Projects/Cpp/Opencv/YellowLine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/YellowLine.dir/src/YellowLine.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/YellowLine.dir/src/YellowLine.cpp.o -c /home/jachinshen/Projects/Cpp/Opencv/YellowLine/src/YellowLine.cpp

CMakeFiles/YellowLine.dir/src/YellowLine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/YellowLine.dir/src/YellowLine.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jachinshen/Projects/Cpp/Opencv/YellowLine/src/YellowLine.cpp > CMakeFiles/YellowLine.dir/src/YellowLine.cpp.i

CMakeFiles/YellowLine.dir/src/YellowLine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/YellowLine.dir/src/YellowLine.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jachinshen/Projects/Cpp/Opencv/YellowLine/src/YellowLine.cpp -o CMakeFiles/YellowLine.dir/src/YellowLine.cpp.s

CMakeFiles/YellowLine.dir/src/YellowLine.cpp.o.requires:

.PHONY : CMakeFiles/YellowLine.dir/src/YellowLine.cpp.o.requires

CMakeFiles/YellowLine.dir/src/YellowLine.cpp.o.provides: CMakeFiles/YellowLine.dir/src/YellowLine.cpp.o.requires
	$(MAKE) -f CMakeFiles/YellowLine.dir/build.make CMakeFiles/YellowLine.dir/src/YellowLine.cpp.o.provides.build
.PHONY : CMakeFiles/YellowLine.dir/src/YellowLine.cpp.o.provides

CMakeFiles/YellowLine.dir/src/YellowLine.cpp.o.provides.build: CMakeFiles/YellowLine.dir/src/YellowLine.cpp.o


CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.o: CMakeFiles/YellowLine.dir/flags.make
CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.o: ../src/LeastSquare.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jachinshen/Projects/Cpp/Opencv/YellowLine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.o -c /home/jachinshen/Projects/Cpp/Opencv/YellowLine/src/LeastSquare.cpp

CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jachinshen/Projects/Cpp/Opencv/YellowLine/src/LeastSquare.cpp > CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.i

CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jachinshen/Projects/Cpp/Opencv/YellowLine/src/LeastSquare.cpp -o CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.s

CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.o.requires:

.PHONY : CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.o.requires

CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.o.provides: CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.o.requires
	$(MAKE) -f CMakeFiles/YellowLine.dir/build.make CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.o.provides.build
.PHONY : CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.o.provides

CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.o.provides.build: CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.o


# Object files for target YellowLine
YellowLine_OBJECTS = \
"CMakeFiles/YellowLine.dir/src/YellowLine.cpp.o" \
"CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.o"

# External object files for target YellowLine
YellowLine_EXTERNAL_OBJECTS =

YellowLine: CMakeFiles/YellowLine.dir/src/YellowLine.cpp.o
YellowLine: CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.o
YellowLine: CMakeFiles/YellowLine.dir/build.make
YellowLine: /usr/local/lib/libopencv_videostab.so.2.4.8
YellowLine: /usr/local/lib/libopencv_ts.a
YellowLine: /usr/local/lib/libopencv_superres.so.2.4.8
YellowLine: /usr/local/lib/libopencv_stitching.so.2.4.8
YellowLine: /usr/local/lib/libopencv_contrib.so.2.4.8
YellowLine: /usr/local/lib/libopencv_nonfree.so.2.4.8
YellowLine: /usr/local/lib/libopencv_ocl.so.2.4.8
YellowLine: /usr/local/lib/libopencv_gpu.so.2.4.8
YellowLine: /usr/local/lib/libopencv_photo.so.2.4.8
YellowLine: /usr/local/lib/libopencv_objdetect.so.2.4.8
YellowLine: /usr/local/lib/libopencv_legacy.so.2.4.8
YellowLine: /usr/local/lib/libopencv_video.so.2.4.8
YellowLine: /usr/local/lib/libopencv_ml.so.2.4.8
YellowLine: /usr/local/lib/libopencv_calib3d.so.2.4.8
YellowLine: /usr/local/lib/libopencv_features2d.so.2.4.8
YellowLine: /usr/local/lib/libopencv_highgui.so.2.4.8
YellowLine: /usr/local/lib/libopencv_imgproc.so.2.4.8
YellowLine: /usr/local/lib/libopencv_flann.so.2.4.8
YellowLine: /usr/local/lib/libopencv_core.so.2.4.8
YellowLine: CMakeFiles/YellowLine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jachinshen/Projects/Cpp/Opencv/YellowLine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable YellowLine"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/YellowLine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/YellowLine.dir/build: YellowLine

.PHONY : CMakeFiles/YellowLine.dir/build

CMakeFiles/YellowLine.dir/requires: CMakeFiles/YellowLine.dir/src/YellowLine.cpp.o.requires
CMakeFiles/YellowLine.dir/requires: CMakeFiles/YellowLine.dir/src/LeastSquare.cpp.o.requires

.PHONY : CMakeFiles/YellowLine.dir/requires

CMakeFiles/YellowLine.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/YellowLine.dir/cmake_clean.cmake
.PHONY : CMakeFiles/YellowLine.dir/clean

CMakeFiles/YellowLine.dir/depend:
	cd /home/jachinshen/Projects/Cpp/Opencv/YellowLine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jachinshen/Projects/Cpp/Opencv/YellowLine /home/jachinshen/Projects/Cpp/Opencv/YellowLine /home/jachinshen/Projects/Cpp/Opencv/YellowLine/build /home/jachinshen/Projects/Cpp/Opencv/YellowLine/build /home/jachinshen/Projects/Cpp/Opencv/YellowLine/build/CMakeFiles/YellowLine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/YellowLine.dir/depend

