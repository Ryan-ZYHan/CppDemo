# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/hans/test/serial

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hans/test/serial/build

# Include any dependencies generated for this target.
include src/CMakeFiles/testUT.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/testUT.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/testUT.dir/flags.make

src/CMakeFiles/testUT.dir/__/include/FileExtension.cpp.o: src/CMakeFiles/testUT.dir/flags.make
src/CMakeFiles/testUT.dir/__/include/FileExtension.cpp.o: ../include/FileExtension.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hans/test/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/testUT.dir/__/include/FileExtension.cpp.o"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testUT.dir/__/include/FileExtension.cpp.o -c /home/hans/test/serial/include/FileExtension.cpp

src/CMakeFiles/testUT.dir/__/include/FileExtension.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testUT.dir/__/include/FileExtension.cpp.i"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hans/test/serial/include/FileExtension.cpp > CMakeFiles/testUT.dir/__/include/FileExtension.cpp.i

src/CMakeFiles/testUT.dir/__/include/FileExtension.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testUT.dir/__/include/FileExtension.cpp.s"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hans/test/serial/include/FileExtension.cpp -o CMakeFiles/testUT.dir/__/include/FileExtension.cpp.s

src/CMakeFiles/testUT.dir/__/include/FileExtension.cpp.o.requires:

.PHONY : src/CMakeFiles/testUT.dir/__/include/FileExtension.cpp.o.requires

src/CMakeFiles/testUT.dir/__/include/FileExtension.cpp.o.provides: src/CMakeFiles/testUT.dir/__/include/FileExtension.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/testUT.dir/build.make src/CMakeFiles/testUT.dir/__/include/FileExtension.cpp.o.provides.build
.PHONY : src/CMakeFiles/testUT.dir/__/include/FileExtension.cpp.o.provides

src/CMakeFiles/testUT.dir/__/include/FileExtension.cpp.o.provides.build: src/CMakeFiles/testUT.dir/__/include/FileExtension.cpp.o


src/CMakeFiles/testUT.dir/__/include/Change.cpp.o: src/CMakeFiles/testUT.dir/flags.make
src/CMakeFiles/testUT.dir/__/include/Change.cpp.o: ../include/Change.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hans/test/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/testUT.dir/__/include/Change.cpp.o"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testUT.dir/__/include/Change.cpp.o -c /home/hans/test/serial/include/Change.cpp

src/CMakeFiles/testUT.dir/__/include/Change.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testUT.dir/__/include/Change.cpp.i"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hans/test/serial/include/Change.cpp > CMakeFiles/testUT.dir/__/include/Change.cpp.i

src/CMakeFiles/testUT.dir/__/include/Change.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testUT.dir/__/include/Change.cpp.s"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hans/test/serial/include/Change.cpp -o CMakeFiles/testUT.dir/__/include/Change.cpp.s

src/CMakeFiles/testUT.dir/__/include/Change.cpp.o.requires:

.PHONY : src/CMakeFiles/testUT.dir/__/include/Change.cpp.o.requires

src/CMakeFiles/testUT.dir/__/include/Change.cpp.o.provides: src/CMakeFiles/testUT.dir/__/include/Change.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/testUT.dir/build.make src/CMakeFiles/testUT.dir/__/include/Change.cpp.o.provides.build
.PHONY : src/CMakeFiles/testUT.dir/__/include/Change.cpp.o.provides

src/CMakeFiles/testUT.dir/__/include/Change.cpp.o.provides.build: src/CMakeFiles/testUT.dir/__/include/Change.cpp.o


src/CMakeFiles/testUT.dir/__/include/Checkout.cpp.o: src/CMakeFiles/testUT.dir/flags.make
src/CMakeFiles/testUT.dir/__/include/Checkout.cpp.o: ../include/Checkout.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hans/test/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/testUT.dir/__/include/Checkout.cpp.o"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testUT.dir/__/include/Checkout.cpp.o -c /home/hans/test/serial/include/Checkout.cpp

src/CMakeFiles/testUT.dir/__/include/Checkout.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testUT.dir/__/include/Checkout.cpp.i"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hans/test/serial/include/Checkout.cpp > CMakeFiles/testUT.dir/__/include/Checkout.cpp.i

src/CMakeFiles/testUT.dir/__/include/Checkout.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testUT.dir/__/include/Checkout.cpp.s"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hans/test/serial/include/Checkout.cpp -o CMakeFiles/testUT.dir/__/include/Checkout.cpp.s

src/CMakeFiles/testUT.dir/__/include/Checkout.cpp.o.requires:

.PHONY : src/CMakeFiles/testUT.dir/__/include/Checkout.cpp.o.requires

src/CMakeFiles/testUT.dir/__/include/Checkout.cpp.o.provides: src/CMakeFiles/testUT.dir/__/include/Checkout.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/testUT.dir/build.make src/CMakeFiles/testUT.dir/__/include/Checkout.cpp.o.provides.build
.PHONY : src/CMakeFiles/testUT.dir/__/include/Checkout.cpp.o.provides

src/CMakeFiles/testUT.dir/__/include/Checkout.cpp.o.provides.build: src/CMakeFiles/testUT.dir/__/include/Checkout.cpp.o


src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.o: src/CMakeFiles/testUT.dir/flags.make
src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.o: ../include/easylogger/plugins/file/elog_file.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hans/test/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.o"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.o   -c /home/hans/test/serial/include/easylogger/plugins/file/elog_file.c

src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.i"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hans/test/serial/include/easylogger/plugins/file/elog_file.c > CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.i

src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.s"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hans/test/serial/include/easylogger/plugins/file/elog_file.c -o CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.s

src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.o.requires:

.PHONY : src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.o.requires

src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.o.provides: src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.o.requires
	$(MAKE) -f src/CMakeFiles/testUT.dir/build.make src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.o.provides.build
.PHONY : src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.o.provides

src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.o.provides.build: src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.o


src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.o: src/CMakeFiles/testUT.dir/flags.make
src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.o: ../include/easylogger/plugins/file/elog_file_port.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hans/test/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.o"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.o   -c /home/hans/test/serial/include/easylogger/plugins/file/elog_file_port.c

src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.i"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hans/test/serial/include/easylogger/plugins/file/elog_file_port.c > CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.i

src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.s"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hans/test/serial/include/easylogger/plugins/file/elog_file_port.c -o CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.s

src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.o.requires:

.PHONY : src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.o.requires

src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.o.provides: src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.o.requires
	$(MAKE) -f src/CMakeFiles/testUT.dir/build.make src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.o.provides.build
.PHONY : src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.o.provides

src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.o.provides.build: src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.o


src/CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.o: src/CMakeFiles/testUT.dir/flags.make
src/CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.o: ../include/easylogger/port/elog_port.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hans/test/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.o"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.o   -c /home/hans/test/serial/include/easylogger/port/elog_port.c

src/CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.i"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hans/test/serial/include/easylogger/port/elog_port.c > CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.i

src/CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.s"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hans/test/serial/include/easylogger/port/elog_port.c -o CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.s

src/CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.o.requires:

.PHONY : src/CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.o.requires

src/CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.o.provides: src/CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.o.requires
	$(MAKE) -f src/CMakeFiles/testUT.dir/build.make src/CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.o.provides.build
.PHONY : src/CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.o.provides

src/CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.o.provides.build: src/CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.o


src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.o: src/CMakeFiles/testUT.dir/flags.make
src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.o: ../include/easylogger/src/elog.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hans/test/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.o"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.o   -c /home/hans/test/serial/include/easylogger/src/elog.c

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.i"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hans/test/serial/include/easylogger/src/elog.c > CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.i

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.s"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hans/test/serial/include/easylogger/src/elog.c -o CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.s

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.o.requires:

.PHONY : src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.o.requires

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.o.provides: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.o.requires
	$(MAKE) -f src/CMakeFiles/testUT.dir/build.make src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.o.provides.build
.PHONY : src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.o.provides

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.o.provides.build: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.o


src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.o: src/CMakeFiles/testUT.dir/flags.make
src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.o: ../include/easylogger/src/elog_async.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hans/test/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.o"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.o   -c /home/hans/test/serial/include/easylogger/src/elog_async.c

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.i"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hans/test/serial/include/easylogger/src/elog_async.c > CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.i

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.s"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hans/test/serial/include/easylogger/src/elog_async.c -o CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.s

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.o.requires:

.PHONY : src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.o.requires

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.o.provides: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.o.requires
	$(MAKE) -f src/CMakeFiles/testUT.dir/build.make src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.o.provides.build
.PHONY : src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.o.provides

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.o.provides.build: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.o


src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.o: src/CMakeFiles/testUT.dir/flags.make
src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.o: ../include/easylogger/src/elog_buf.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hans/test/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.o"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.o   -c /home/hans/test/serial/include/easylogger/src/elog_buf.c

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.i"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hans/test/serial/include/easylogger/src/elog_buf.c > CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.i

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.s"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hans/test/serial/include/easylogger/src/elog_buf.c -o CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.s

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.o.requires:

.PHONY : src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.o.requires

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.o.provides: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.o.requires
	$(MAKE) -f src/CMakeFiles/testUT.dir/build.make src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.o.provides.build
.PHONY : src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.o.provides

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.o.provides.build: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.o


src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.o: src/CMakeFiles/testUT.dir/flags.make
src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.o: ../include/easylogger/src/elog_utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hans/test/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.o"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.o   -c /home/hans/test/serial/include/easylogger/src/elog_utils.c

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.i"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/hans/test/serial/include/easylogger/src/elog_utils.c > CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.i

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.s"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-gcc-7 $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/hans/test/serial/include/easylogger/src/elog_utils.c -o CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.s

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.o.requires:

.PHONY : src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.o.requires

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.o.provides: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.o.requires
	$(MAKE) -f src/CMakeFiles/testUT.dir/build.make src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.o.provides.build
.PHONY : src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.o.provides

src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.o.provides.build: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.o


src/CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.o: src/CMakeFiles/testUT.dir/flags.make
src/CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.o: ../src/usb2RS485/SerialPort.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hans/test/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object src/CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.o"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.o -c /home/hans/test/serial/src/usb2RS485/SerialPort.cpp

src/CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.i"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hans/test/serial/src/usb2RS485/SerialPort.cpp > CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.i

src/CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.s"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hans/test/serial/src/usb2RS485/SerialPort.cpp -o CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.s

src/CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.o.requires:

.PHONY : src/CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.o.requires

src/CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.o.provides: src/CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/testUT.dir/build.make src/CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.o.provides.build
.PHONY : src/CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.o.provides

src/CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.o.provides.build: src/CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.o


src/CMakeFiles/testUT.dir/weld/handle.cpp.o: src/CMakeFiles/testUT.dir/flags.make
src/CMakeFiles/testUT.dir/weld/handle.cpp.o: ../src/weld/handle.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hans/test/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object src/CMakeFiles/testUT.dir/weld/handle.cpp.o"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-g++-7  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testUT.dir/weld/handle.cpp.o -c /home/hans/test/serial/src/weld/handle.cpp

src/CMakeFiles/testUT.dir/weld/handle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testUT.dir/weld/handle.cpp.i"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hans/test/serial/src/weld/handle.cpp > CMakeFiles/testUT.dir/weld/handle.cpp.i

src/CMakeFiles/testUT.dir/weld/handle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testUT.dir/weld/handle.cpp.s"
	cd /home/hans/test/serial/build/src && /usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hans/test/serial/src/weld/handle.cpp -o CMakeFiles/testUT.dir/weld/handle.cpp.s

src/CMakeFiles/testUT.dir/weld/handle.cpp.o.requires:

.PHONY : src/CMakeFiles/testUT.dir/weld/handle.cpp.o.requires

src/CMakeFiles/testUT.dir/weld/handle.cpp.o.provides: src/CMakeFiles/testUT.dir/weld/handle.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/testUT.dir/build.make src/CMakeFiles/testUT.dir/weld/handle.cpp.o.provides.build
.PHONY : src/CMakeFiles/testUT.dir/weld/handle.cpp.o.provides

src/CMakeFiles/testUT.dir/weld/handle.cpp.o.provides.build: src/CMakeFiles/testUT.dir/weld/handle.cpp.o


# Object files for target testUT
testUT_OBJECTS = \
"CMakeFiles/testUT.dir/__/include/FileExtension.cpp.o" \
"CMakeFiles/testUT.dir/__/include/Change.cpp.o" \
"CMakeFiles/testUT.dir/__/include/Checkout.cpp.o" \
"CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.o" \
"CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.o" \
"CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.o" \
"CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.o" \
"CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.o" \
"CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.o" \
"CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.o" \
"CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.o" \
"CMakeFiles/testUT.dir/weld/handle.cpp.o"

# External object files for target testUT
testUT_EXTERNAL_OBJECTS =

testUT: src/CMakeFiles/testUT.dir/__/include/FileExtension.cpp.o
testUT: src/CMakeFiles/testUT.dir/__/include/Change.cpp.o
testUT: src/CMakeFiles/testUT.dir/__/include/Checkout.cpp.o
testUT: src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.o
testUT: src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.o
testUT: src/CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.o
testUT: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.o
testUT: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.o
testUT: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.o
testUT: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.o
testUT: src/CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.o
testUT: src/CMakeFiles/testUT.dir/weld/handle.cpp.o
testUT: src/CMakeFiles/testUT.dir/build.make
testUT: ../libs/libHR_Pro.so
testUT: /usr/local/lib/libserialport.so
testUT: src/CMakeFiles/testUT.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hans/test/serial/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable ../testUT"
	cd /home/hans/test/serial/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testUT.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/testUT.dir/build: testUT

.PHONY : src/CMakeFiles/testUT.dir/build

src/CMakeFiles/testUT.dir/requires: src/CMakeFiles/testUT.dir/__/include/FileExtension.cpp.o.requires
src/CMakeFiles/testUT.dir/requires: src/CMakeFiles/testUT.dir/__/include/Change.cpp.o.requires
src/CMakeFiles/testUT.dir/requires: src/CMakeFiles/testUT.dir/__/include/Checkout.cpp.o.requires
src/CMakeFiles/testUT.dir/requires: src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file.c.o.requires
src/CMakeFiles/testUT.dir/requires: src/CMakeFiles/testUT.dir/__/include/easylogger/plugins/file/elog_file_port.c.o.requires
src/CMakeFiles/testUT.dir/requires: src/CMakeFiles/testUT.dir/__/include/easylogger/port/elog_port.c.o.requires
src/CMakeFiles/testUT.dir/requires: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog.c.o.requires
src/CMakeFiles/testUT.dir/requires: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_async.c.o.requires
src/CMakeFiles/testUT.dir/requires: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_buf.c.o.requires
src/CMakeFiles/testUT.dir/requires: src/CMakeFiles/testUT.dir/__/include/easylogger/src/elog_utils.c.o.requires
src/CMakeFiles/testUT.dir/requires: src/CMakeFiles/testUT.dir/usb2RS485/SerialPort.cpp.o.requires
src/CMakeFiles/testUT.dir/requires: src/CMakeFiles/testUT.dir/weld/handle.cpp.o.requires

.PHONY : src/CMakeFiles/testUT.dir/requires

src/CMakeFiles/testUT.dir/clean:
	cd /home/hans/test/serial/build/src && $(CMAKE_COMMAND) -P CMakeFiles/testUT.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/testUT.dir/clean

src/CMakeFiles/testUT.dir/depend:
	cd /home/hans/test/serial/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hans/test/serial /home/hans/test/serial/src /home/hans/test/serial/build /home/hans/test/serial/build/src /home/hans/test/serial/build/src/CMakeFiles/testUT.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/testUT.dir/depend

