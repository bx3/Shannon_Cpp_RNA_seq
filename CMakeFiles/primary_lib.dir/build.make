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
CMAKE_SOURCE_DIR = /home/bowen/Shannon_parallel_hash

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bowen/Shannon_parallel_hash

# Include any dependencies generated for this target.
include CMakeFiles/primary_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/primary_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/primary_lib.dir/flags.make

CMakeFiles/primary_lib.dir/src/log.cpp.o: CMakeFiles/primary_lib.dir/flags.make
CMakeFiles/primary_lib.dir/src/log.cpp.o: src/log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bowen/Shannon_parallel_hash/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/primary_lib.dir/src/log.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/primary_lib.dir/src/log.cpp.o -c /home/bowen/Shannon_parallel_hash/src/log.cpp

CMakeFiles/primary_lib.dir/src/log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/primary_lib.dir/src/log.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bowen/Shannon_parallel_hash/src/log.cpp > CMakeFiles/primary_lib.dir/src/log.cpp.i

CMakeFiles/primary_lib.dir/src/log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/primary_lib.dir/src/log.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bowen/Shannon_parallel_hash/src/log.cpp -o CMakeFiles/primary_lib.dir/src/log.cpp.s

CMakeFiles/primary_lib.dir/src/log.cpp.o.requires:

.PHONY : CMakeFiles/primary_lib.dir/src/log.cpp.o.requires

CMakeFiles/primary_lib.dir/src/log.cpp.o.provides: CMakeFiles/primary_lib.dir/src/log.cpp.o.requires
	$(MAKE) -f CMakeFiles/primary_lib.dir/build.make CMakeFiles/primary_lib.dir/src/log.cpp.o.provides.build
.PHONY : CMakeFiles/primary_lib.dir/src/log.cpp.o.provides

CMakeFiles/primary_lib.dir/src/log.cpp.o.provides.build: CMakeFiles/primary_lib.dir/src/log.cpp.o


CMakeFiles/primary_lib.dir/src/basic_log.cpp.o: CMakeFiles/primary_lib.dir/flags.make
CMakeFiles/primary_lib.dir/src/basic_log.cpp.o: src/basic_log.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bowen/Shannon_parallel_hash/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/primary_lib.dir/src/basic_log.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/primary_lib.dir/src/basic_log.cpp.o -c /home/bowen/Shannon_parallel_hash/src/basic_log.cpp

CMakeFiles/primary_lib.dir/src/basic_log.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/primary_lib.dir/src/basic_log.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bowen/Shannon_parallel_hash/src/basic_log.cpp > CMakeFiles/primary_lib.dir/src/basic_log.cpp.i

CMakeFiles/primary_lib.dir/src/basic_log.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/primary_lib.dir/src/basic_log.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bowen/Shannon_parallel_hash/src/basic_log.cpp -o CMakeFiles/primary_lib.dir/src/basic_log.cpp.s

CMakeFiles/primary_lib.dir/src/basic_log.cpp.o.requires:

.PHONY : CMakeFiles/primary_lib.dir/src/basic_log.cpp.o.requires

CMakeFiles/primary_lib.dir/src/basic_log.cpp.o.provides: CMakeFiles/primary_lib.dir/src/basic_log.cpp.o.requires
	$(MAKE) -f CMakeFiles/primary_lib.dir/build.make CMakeFiles/primary_lib.dir/src/basic_log.cpp.o.provides.build
.PHONY : CMakeFiles/primary_lib.dir/src/basic_log.cpp.o.provides

CMakeFiles/primary_lib.dir/src/basic_log.cpp.o.provides.build: CMakeFiles/primary_lib.dir/src/basic_log.cpp.o


CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.o: CMakeFiles/primary_lib.dir/flags.make
CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.o: src/local_file_structure.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bowen/Shannon_parallel_hash/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.o -c /home/bowen/Shannon_parallel_hash/src/local_file_structure.cpp

CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bowen/Shannon_parallel_hash/src/local_file_structure.cpp > CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.i

CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bowen/Shannon_parallel_hash/src/local_file_structure.cpp -o CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.s

CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.o.requires:

.PHONY : CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.o.requires

CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.o.provides: CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.o.requires
	$(MAKE) -f CMakeFiles/primary_lib.dir/build.make CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.o.provides.build
.PHONY : CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.o.provides

CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.o.provides.build: CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.o


CMakeFiles/primary_lib.dir/src/json_parser.cpp.o: CMakeFiles/primary_lib.dir/flags.make
CMakeFiles/primary_lib.dir/src/json_parser.cpp.o: src/json_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bowen/Shannon_parallel_hash/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/primary_lib.dir/src/json_parser.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/primary_lib.dir/src/json_parser.cpp.o -c /home/bowen/Shannon_parallel_hash/src/json_parser.cpp

CMakeFiles/primary_lib.dir/src/json_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/primary_lib.dir/src/json_parser.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bowen/Shannon_parallel_hash/src/json_parser.cpp > CMakeFiles/primary_lib.dir/src/json_parser.cpp.i

CMakeFiles/primary_lib.dir/src/json_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/primary_lib.dir/src/json_parser.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bowen/Shannon_parallel_hash/src/json_parser.cpp -o CMakeFiles/primary_lib.dir/src/json_parser.cpp.s

CMakeFiles/primary_lib.dir/src/json_parser.cpp.o.requires:

.PHONY : CMakeFiles/primary_lib.dir/src/json_parser.cpp.o.requires

CMakeFiles/primary_lib.dir/src/json_parser.cpp.o.provides: CMakeFiles/primary_lib.dir/src/json_parser.cpp.o.requires
	$(MAKE) -f CMakeFiles/primary_lib.dir/build.make CMakeFiles/primary_lib.dir/src/json_parser.cpp.o.provides.build
.PHONY : CMakeFiles/primary_lib.dir/src/json_parser.cpp.o.provides

CMakeFiles/primary_lib.dir/src/json_parser.cpp.o.provides.build: CMakeFiles/primary_lib.dir/src/json_parser.cpp.o


CMakeFiles/primary_lib.dir/src/encoding.cpp.o: CMakeFiles/primary_lib.dir/flags.make
CMakeFiles/primary_lib.dir/src/encoding.cpp.o: src/encoding.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bowen/Shannon_parallel_hash/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/primary_lib.dir/src/encoding.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/primary_lib.dir/src/encoding.cpp.o -c /home/bowen/Shannon_parallel_hash/src/encoding.cpp

CMakeFiles/primary_lib.dir/src/encoding.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/primary_lib.dir/src/encoding.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bowen/Shannon_parallel_hash/src/encoding.cpp > CMakeFiles/primary_lib.dir/src/encoding.cpp.i

CMakeFiles/primary_lib.dir/src/encoding.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/primary_lib.dir/src/encoding.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bowen/Shannon_parallel_hash/src/encoding.cpp -o CMakeFiles/primary_lib.dir/src/encoding.cpp.s

CMakeFiles/primary_lib.dir/src/encoding.cpp.o.requires:

.PHONY : CMakeFiles/primary_lib.dir/src/encoding.cpp.o.requires

CMakeFiles/primary_lib.dir/src/encoding.cpp.o.provides: CMakeFiles/primary_lib.dir/src/encoding.cpp.o.requires
	$(MAKE) -f CMakeFiles/primary_lib.dir/build.make CMakeFiles/primary_lib.dir/src/encoding.cpp.o.provides.build
.PHONY : CMakeFiles/primary_lib.dir/src/encoding.cpp.o.provides

CMakeFiles/primary_lib.dir/src/encoding.cpp.o.provides.build: CMakeFiles/primary_lib.dir/src/encoding.cpp.o


CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.o: CMakeFiles/primary_lib.dir/flags.make
CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.o: src/shannon_C_seq_helper.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bowen/Shannon_parallel_hash/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.o -c /home/bowen/Shannon_parallel_hash/src/shannon_C_seq_helper.cpp

CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bowen/Shannon_parallel_hash/src/shannon_C_seq_helper.cpp > CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.i

CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bowen/Shannon_parallel_hash/src/shannon_C_seq_helper.cpp -o CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.s

CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.o.requires:

.PHONY : CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.o.requires

CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.o.provides: CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.o.requires
	$(MAKE) -f CMakeFiles/primary_lib.dir/build.make CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.o.provides.build
.PHONY : CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.o.provides

CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.o.provides.build: CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.o


# Object files for target primary_lib
primary_lib_OBJECTS = \
"CMakeFiles/primary_lib.dir/src/log.cpp.o" \
"CMakeFiles/primary_lib.dir/src/basic_log.cpp.o" \
"CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.o" \
"CMakeFiles/primary_lib.dir/src/json_parser.cpp.o" \
"CMakeFiles/primary_lib.dir/src/encoding.cpp.o" \
"CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.o"

# External object files for target primary_lib
primary_lib_EXTERNAL_OBJECTS =

lib_shannon/libprimary_lib.a: CMakeFiles/primary_lib.dir/src/log.cpp.o
lib_shannon/libprimary_lib.a: CMakeFiles/primary_lib.dir/src/basic_log.cpp.o
lib_shannon/libprimary_lib.a: CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.o
lib_shannon/libprimary_lib.a: CMakeFiles/primary_lib.dir/src/json_parser.cpp.o
lib_shannon/libprimary_lib.a: CMakeFiles/primary_lib.dir/src/encoding.cpp.o
lib_shannon/libprimary_lib.a: CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.o
lib_shannon/libprimary_lib.a: CMakeFiles/primary_lib.dir/build.make
lib_shannon/libprimary_lib.a: CMakeFiles/primary_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bowen/Shannon_parallel_hash/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX static library lib_shannon/libprimary_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/primary_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/primary_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/primary_lib.dir/build: lib_shannon/libprimary_lib.a

.PHONY : CMakeFiles/primary_lib.dir/build

CMakeFiles/primary_lib.dir/requires: CMakeFiles/primary_lib.dir/src/log.cpp.o.requires
CMakeFiles/primary_lib.dir/requires: CMakeFiles/primary_lib.dir/src/basic_log.cpp.o.requires
CMakeFiles/primary_lib.dir/requires: CMakeFiles/primary_lib.dir/src/local_file_structure.cpp.o.requires
CMakeFiles/primary_lib.dir/requires: CMakeFiles/primary_lib.dir/src/json_parser.cpp.o.requires
CMakeFiles/primary_lib.dir/requires: CMakeFiles/primary_lib.dir/src/encoding.cpp.o.requires
CMakeFiles/primary_lib.dir/requires: CMakeFiles/primary_lib.dir/src/shannon_C_seq_helper.cpp.o.requires

.PHONY : CMakeFiles/primary_lib.dir/requires

CMakeFiles/primary_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/primary_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/primary_lib.dir/clean

CMakeFiles/primary_lib.dir/depend:
	cd /home/bowen/Shannon_parallel_hash && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bowen/Shannon_parallel_hash /home/bowen/Shannon_parallel_hash /home/bowen/Shannon_parallel_hash /home/bowen/Shannon_parallel_hash /home/bowen/Shannon_parallel_hash/CMakeFiles/primary_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/primary_lib.dir/depend

