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
CMAKE_SOURCE_DIR = "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test"

# Include any dependencies generated for this target.
include SDL_Test/CMakeFiles/SDLTest.dir/depend.make

# Include the progress variables for this target.
include SDL_Test/CMakeFiles/SDLTest.dir/progress.make

# Include the compile flags for this target's objects.
include SDL_Test/CMakeFiles/SDLTest.dir/flags.make

SDL_Test/CMakeFiles/SDLTest.dir/Main.cpp.o: SDL_Test/CMakeFiles/SDLTest.dir/flags.make
SDL_Test/CMakeFiles/SDLTest.dir/Main.cpp.o: Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object SDL_Test/CMakeFiles/SDLTest.dir/Main.cpp.o"
	cd "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test/SDL_Test" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/SDLTest.dir/Main.cpp.o -c "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test/Main.cpp"

SDL_Test/CMakeFiles/SDLTest.dir/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SDLTest.dir/Main.cpp.i"
	cd "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test/SDL_Test" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test/Main.cpp" > CMakeFiles/SDLTest.dir/Main.cpp.i

SDL_Test/CMakeFiles/SDLTest.dir/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SDLTest.dir/Main.cpp.s"
	cd "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test/SDL_Test" && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test/Main.cpp" -o CMakeFiles/SDLTest.dir/Main.cpp.s

# Object files for target SDLTest
SDLTest_OBJECTS = \
"CMakeFiles/SDLTest.dir/Main.cpp.o"

# External object files for target SDLTest
SDLTest_EXTERNAL_OBJECTS =

SDL_Test/SDLTest: SDL_Test/CMakeFiles/SDLTest.dir/Main.cpp.o
SDL_Test/SDLTest: SDL_Test/CMakeFiles/SDLTest.dir/build.make
SDL_Test/SDLTest: SDL_Test/CMakeFiles/SDLTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SDLTest"
	cd "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test/SDL_Test" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SDLTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
SDL_Test/CMakeFiles/SDLTest.dir/build: SDL_Test/SDLTest

.PHONY : SDL_Test/CMakeFiles/SDLTest.dir/build

SDL_Test/CMakeFiles/SDLTest.dir/clean:
	cd "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test/SDL_Test" && $(CMAKE_COMMAND) -P CMakeFiles/SDLTest.dir/cmake_clean.cmake
.PHONY : SDL_Test/CMakeFiles/SDLTest.dir/clean

SDL_Test/CMakeFiles/SDLTest.dir/depend:
	cd "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie" "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test" "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test" "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test/SDL_Test" "/home/immaculee/projet_c++/sdl_project/test_SDL - Kopie/SDL_Test/SDL_Test/CMakeFiles/SDLTest.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : SDL_Test/CMakeFiles/SDLTest.dir/depend
