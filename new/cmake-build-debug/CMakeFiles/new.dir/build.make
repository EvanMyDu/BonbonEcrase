# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2024.2.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2024.2.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\gabri\Documents\GitHub\new

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\gabri\Documents\GitHub\new\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/new.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/new.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/new.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/new.dir/flags.make

CMakeFiles/new.dir/src/ImageHandler.c.obj: CMakeFiles/new.dir/flags.make
CMakeFiles/new.dir/src/ImageHandler.c.obj: CMakeFiles/new.dir/includes_C.rsp
CMakeFiles/new.dir/src/ImageHandler.c.obj: C:/Users/gabri/Documents/GitHub/new/src/ImageHandler.c
CMakeFiles/new.dir/src/ImageHandler.c.obj: CMakeFiles/new.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\gabri\Documents\GitHub\new\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/new.dir/src/ImageHandler.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/new.dir/src/ImageHandler.c.obj -MF CMakeFiles\new.dir\src\ImageHandler.c.obj.d -o CMakeFiles\new.dir\src\ImageHandler.c.obj -c C:\Users\gabri\Documents\GitHub\new\src\ImageHandler.c

CMakeFiles/new.dir/src/ImageHandler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/new.dir/src/ImageHandler.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\gabri\Documents\GitHub\new\src\ImageHandler.c > CMakeFiles\new.dir\src\ImageHandler.c.i

CMakeFiles/new.dir/src/ImageHandler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/new.dir/src/ImageHandler.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\gabri\Documents\GitHub\new\src\ImageHandler.c -o CMakeFiles\new.dir\src\ImageHandler.c.s

CMakeFiles/new.dir/src/Menu.c.obj: CMakeFiles/new.dir/flags.make
CMakeFiles/new.dir/src/Menu.c.obj: CMakeFiles/new.dir/includes_C.rsp
CMakeFiles/new.dir/src/Menu.c.obj: C:/Users/gabri/Documents/GitHub/new/src/Menu.c
CMakeFiles/new.dir/src/Menu.c.obj: CMakeFiles/new.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\gabri\Documents\GitHub\new\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/new.dir/src/Menu.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/new.dir/src/Menu.c.obj -MF CMakeFiles\new.dir\src\Menu.c.obj.d -o CMakeFiles\new.dir\src\Menu.c.obj -c C:\Users\gabri\Documents\GitHub\new\src\Menu.c

CMakeFiles/new.dir/src/Menu.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/new.dir/src/Menu.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\gabri\Documents\GitHub\new\src\Menu.c > CMakeFiles\new.dir\src\Menu.c.i

CMakeFiles/new.dir/src/Menu.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/new.dir/src/Menu.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.2\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\gabri\Documents\GitHub\new\src\Menu.c -o CMakeFiles\new.dir\src\Menu.c.s

# Object files for target new
new_OBJECTS = \
"CMakeFiles/new.dir/src/ImageHandler.c.obj" \
"CMakeFiles/new.dir/src/Menu.c.obj"

# External object files for target new
new_EXTERNAL_OBJECTS =

new.exe: CMakeFiles/new.dir/src/ImageHandler.c.obj
new.exe: CMakeFiles/new.dir/src/Menu.c.obj
new.exe: CMakeFiles/new.dir/build.make
new.exe: CMakeFiles/new.dir/linkLibs.rsp
new.exe: CMakeFiles/new.dir/objects1.rsp
new.exe: CMakeFiles/new.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\gabri\Documents\GitHub\new\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable new.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\new.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/new.dir/build: new.exe
.PHONY : CMakeFiles/new.dir/build

CMakeFiles/new.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\new.dir\cmake_clean.cmake
.PHONY : CMakeFiles/new.dir/clean

CMakeFiles/new.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\gabri\Documents\GitHub\new C:\Users\gabri\Documents\GitHub\new C:\Users\gabri\Documents\GitHub\new\cmake-build-debug C:\Users\gabri\Documents\GitHub\new\cmake-build-debug C:\Users\gabri\Documents\GitHub\new\cmake-build-debug\CMakeFiles\new.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/new.dir/depend
