# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2024.3.3\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2024.3.3\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Administrator\Desktop\mctj\8-76\lab1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Administrator\Desktop\mctj\8-76\lab1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lab1lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lab1lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lab1lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab1lib.dir/flags.make

CMakeFiles/lab1lib.dir/Class.cc.obj: CMakeFiles/lab1lib.dir/flags.make
CMakeFiles/lab1lib.dir/Class.cc.obj: C:/Users/Administrator/Desktop/mctj/8-76/lab1/Class.cc
CMakeFiles/lab1lib.dir/Class.cc.obj: CMakeFiles/lab1lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Administrator\Desktop\mctj\8-76\lab1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab1lib.dir/Class.cc.obj"
	D:\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lab1lib.dir/Class.cc.obj -MF CMakeFiles\lab1lib.dir\Class.cc.obj.d -o CMakeFiles\lab1lib.dir\Class.cc.obj -c C:\Users\Administrator\Desktop\mctj\8-76\lab1\Class.cc

CMakeFiles/lab1lib.dir/Class.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lab1lib.dir/Class.cc.i"
	D:\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Administrator\Desktop\mctj\8-76\lab1\Class.cc > CMakeFiles\lab1lib.dir\Class.cc.i

CMakeFiles/lab1lib.dir/Class.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lab1lib.dir/Class.cc.s"
	D:\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Administrator\Desktop\mctj\8-76\lab1\Class.cc -o CMakeFiles\lab1lib.dir\Class.cc.s

CMakeFiles/lab1lib.dir/Student.cc.obj: CMakeFiles/lab1lib.dir/flags.make
CMakeFiles/lab1lib.dir/Student.cc.obj: C:/Users/Administrator/Desktop/mctj/8-76/lab1/Student.cc
CMakeFiles/lab1lib.dir/Student.cc.obj: CMakeFiles/lab1lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Administrator\Desktop\mctj\8-76\lab1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/lab1lib.dir/Student.cc.obj"
	D:\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/lab1lib.dir/Student.cc.obj -MF CMakeFiles\lab1lib.dir\Student.cc.obj.d -o CMakeFiles\lab1lib.dir\Student.cc.obj -c C:\Users\Administrator\Desktop\mctj\8-76\lab1\Student.cc

CMakeFiles/lab1lib.dir/Student.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/lab1lib.dir/Student.cc.i"
	D:\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\Administrator\Desktop\mctj\8-76\lab1\Student.cc > CMakeFiles\lab1lib.dir\Student.cc.i

CMakeFiles/lab1lib.dir/Student.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/lab1lib.dir/Student.cc.s"
	D:\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\Administrator\Desktop\mctj\8-76\lab1\Student.cc -o CMakeFiles\lab1lib.dir\Student.cc.s

# Object files for target lab1lib
lab1lib_OBJECTS = \
"CMakeFiles/lab1lib.dir/Class.cc.obj" \
"CMakeFiles/lab1lib.dir/Student.cc.obj"

# External object files for target lab1lib
lab1lib_EXTERNAL_OBJECTS =

liblab1lib.a: CMakeFiles/lab1lib.dir/Class.cc.obj
liblab1lib.a: CMakeFiles/lab1lib.dir/Student.cc.obj
liblab1lib.a: CMakeFiles/lab1lib.dir/build.make
liblab1lib.a: CMakeFiles/lab1lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Administrator\Desktop\mctj\8-76\lab1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library liblab1lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles\lab1lib.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\lab1lib.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab1lib.dir/build: liblab1lib.a
.PHONY : CMakeFiles/lab1lib.dir/build

CMakeFiles/lab1lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\lab1lib.dir\cmake_clean.cmake
.PHONY : CMakeFiles/lab1lib.dir/clean

CMakeFiles/lab1lib.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Administrator\Desktop\mctj\8-76\lab1 C:\Users\Administrator\Desktop\mctj\8-76\lab1 C:\Users\Administrator\Desktop\mctj\8-76\lab1\cmake-build-debug C:\Users\Administrator\Desktop\mctj\8-76\lab1\cmake-build-debug C:\Users\Administrator\Desktop\mctj\8-76\lab1\cmake-build-debug\CMakeFiles\lab1lib.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/lab1lib.dir/depend

