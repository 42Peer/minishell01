# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/sumsong/CLionProjects/minishell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/sumsong/CLionProjects/minishell/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/minishell.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/minishell.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/minishell.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/minishell.dir/flags.make

CMakeFiles/minishell.dir/main.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/main.c.o: ../main.c
CMakeFiles/minishell.dir/main.c.o: CMakeFiles/minishell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sumsong/CLionProjects/minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/minishell.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/minishell.dir/main.c.o -MF CMakeFiles/minishell.dir/main.c.o.d -o CMakeFiles/minishell.dir/main.c.o -c /Users/sumsong/CLionProjects/minishell/main.c

CMakeFiles/minishell.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/sumsong/CLionProjects/minishell/main.c > CMakeFiles/minishell.dir/main.c.i

CMakeFiles/minishell.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/sumsong/CLionProjects/minishell/main.c -o CMakeFiles/minishell.dir/main.c.s

CMakeFiles/minishell.dir/tokenize.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/tokenize.c.o: ../tokenize.c
CMakeFiles/minishell.dir/tokenize.c.o: CMakeFiles/minishell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sumsong/CLionProjects/minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/minishell.dir/tokenize.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/minishell.dir/tokenize.c.o -MF CMakeFiles/minishell.dir/tokenize.c.o.d -o CMakeFiles/minishell.dir/tokenize.c.o -c /Users/sumsong/CLionProjects/minishell/tokenize.c

CMakeFiles/minishell.dir/tokenize.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/tokenize.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/sumsong/CLionProjects/minishell/tokenize.c > CMakeFiles/minishell.dir/tokenize.c.i

CMakeFiles/minishell.dir/tokenize.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/tokenize.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/sumsong/CLionProjects/minishell/tokenize.c -o CMakeFiles/minishell.dir/tokenize.c.s

CMakeFiles/minishell.dir/env_handle.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/env_handle.c.o: ../env_handle.c
CMakeFiles/minishell.dir/env_handle.c.o: CMakeFiles/minishell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sumsong/CLionProjects/minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/minishell.dir/env_handle.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/minishell.dir/env_handle.c.o -MF CMakeFiles/minishell.dir/env_handle.c.o.d -o CMakeFiles/minishell.dir/env_handle.c.o -c /Users/sumsong/CLionProjects/minishell/env_handle.c

CMakeFiles/minishell.dir/env_handle.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/env_handle.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/sumsong/CLionProjects/minishell/env_handle.c > CMakeFiles/minishell.dir/env_handle.c.i

CMakeFiles/minishell.dir/env_handle.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/env_handle.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/sumsong/CLionProjects/minishell/env_handle.c -o CMakeFiles/minishell.dir/env_handle.c.s

CMakeFiles/minishell.dir/make_tree.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/make_tree.c.o: ../make_tree.c
CMakeFiles/minishell.dir/make_tree.c.o: CMakeFiles/minishell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sumsong/CLionProjects/minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/minishell.dir/make_tree.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/minishell.dir/make_tree.c.o -MF CMakeFiles/minishell.dir/make_tree.c.o.d -o CMakeFiles/minishell.dir/make_tree.c.o -c /Users/sumsong/CLionProjects/minishell/make_tree.c

CMakeFiles/minishell.dir/make_tree.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/make_tree.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/sumsong/CLionProjects/minishell/make_tree.c > CMakeFiles/minishell.dir/make_tree.c.i

CMakeFiles/minishell.dir/make_tree.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/make_tree.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/sumsong/CLionProjects/minishell/make_tree.c -o CMakeFiles/minishell.dir/make_tree.c.s

CMakeFiles/minishell.dir/tree_parser.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/tree_parser.c.o: ../tree_parser.c
CMakeFiles/minishell.dir/tree_parser.c.o: CMakeFiles/minishell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sumsong/CLionProjects/minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/minishell.dir/tree_parser.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/minishell.dir/tree_parser.c.o -MF CMakeFiles/minishell.dir/tree_parser.c.o.d -o CMakeFiles/minishell.dir/tree_parser.c.o -c /Users/sumsong/CLionProjects/minishell/tree_parser.c

CMakeFiles/minishell.dir/tree_parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/tree_parser.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/sumsong/CLionProjects/minishell/tree_parser.c > CMakeFiles/minishell.dir/tree_parser.c.i

CMakeFiles/minishell.dir/tree_parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/tree_parser.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/sumsong/CLionProjects/minishell/tree_parser.c -o CMakeFiles/minishell.dir/tree_parser.c.s

CMakeFiles/minishell.dir/quote.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/quote.c.o: ../quote.c
CMakeFiles/minishell.dir/quote.c.o: CMakeFiles/minishell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sumsong/CLionProjects/minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/minishell.dir/quote.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/minishell.dir/quote.c.o -MF CMakeFiles/minishell.dir/quote.c.o.d -o CMakeFiles/minishell.dir/quote.c.o -c /Users/sumsong/CLionProjects/minishell/quote.c

CMakeFiles/minishell.dir/quote.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/quote.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/sumsong/CLionProjects/minishell/quote.c > CMakeFiles/minishell.dir/quote.c.i

CMakeFiles/minishell.dir/quote.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/quote.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/sumsong/CLionProjects/minishell/quote.c -o CMakeFiles/minishell.dir/quote.c.s

CMakeFiles/minishell.dir/utils.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/utils.c.o: ../utils.c
CMakeFiles/minishell.dir/utils.c.o: CMakeFiles/minishell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sumsong/CLionProjects/minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/minishell.dir/utils.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/minishell.dir/utils.c.o -MF CMakeFiles/minishell.dir/utils.c.o.d -o CMakeFiles/minishell.dir/utils.c.o -c /Users/sumsong/CLionProjects/minishell/utils.c

CMakeFiles/minishell.dir/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/utils.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/sumsong/CLionProjects/minishell/utils.c > CMakeFiles/minishell.dir/utils.c.i

CMakeFiles/minishell.dir/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/utils.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/sumsong/CLionProjects/minishell/utils.c -o CMakeFiles/minishell.dir/utils.c.s

CMakeFiles/minishell.dir/test.c.o: CMakeFiles/minishell.dir/flags.make
CMakeFiles/minishell.dir/test.c.o: ../test.c
CMakeFiles/minishell.dir/test.c.o: CMakeFiles/minishell.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/sumsong/CLionProjects/minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/minishell.dir/test.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/minishell.dir/test.c.o -MF CMakeFiles/minishell.dir/test.c.o.d -o CMakeFiles/minishell.dir/test.c.o -c /Users/sumsong/CLionProjects/minishell/test.c

CMakeFiles/minishell.dir/test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell.dir/test.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/sumsong/CLionProjects/minishell/test.c > CMakeFiles/minishell.dir/test.c.i

CMakeFiles/minishell.dir/test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell.dir/test.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/sumsong/CLionProjects/minishell/test.c -o CMakeFiles/minishell.dir/test.c.s

# Object files for target minishell
minishell_OBJECTS = \
"CMakeFiles/minishell.dir/main.c.o" \
"CMakeFiles/minishell.dir/tokenize.c.o" \
"CMakeFiles/minishell.dir/env_handle.c.o" \
"CMakeFiles/minishell.dir/make_tree.c.o" \
"CMakeFiles/minishell.dir/tree_parser.c.o" \
"CMakeFiles/minishell.dir/quote.c.o" \
"CMakeFiles/minishell.dir/utils.c.o" \
"CMakeFiles/minishell.dir/test.c.o"

# External object files for target minishell
minishell_EXTERNAL_OBJECTS =

minishell: CMakeFiles/minishell.dir/main.c.o
minishell: CMakeFiles/minishell.dir/tokenize.c.o
minishell: CMakeFiles/minishell.dir/env_handle.c.o
minishell: CMakeFiles/minishell.dir/make_tree.c.o
minishell: CMakeFiles/minishell.dir/tree_parser.c.o
minishell: CMakeFiles/minishell.dir/quote.c.o
minishell: CMakeFiles/minishell.dir/utils.c.o
minishell: CMakeFiles/minishell.dir/test.c.o
minishell: CMakeFiles/minishell.dir/build.make
minishell: CMakeFiles/minishell.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/sumsong/CLionProjects/minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable minishell"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minishell.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/minishell.dir/build: minishell
.PHONY : CMakeFiles/minishell.dir/build

CMakeFiles/minishell.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/minishell.dir/cmake_clean.cmake
.PHONY : CMakeFiles/minishell.dir/clean

CMakeFiles/minishell.dir/depend:
	cd /Users/sumsong/CLionProjects/minishell/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/sumsong/CLionProjects/minishell /Users/sumsong/CLionProjects/minishell /Users/sumsong/CLionProjects/minishell/cmake-build-debug /Users/sumsong/CLionProjects/minishell/cmake-build-debug /Users/sumsong/CLionProjects/minishell/cmake-build-debug/CMakeFiles/minishell.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/minishell.dir/depend

