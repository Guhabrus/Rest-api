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
CMAKE_SOURCE_DIR = /home/maksim/Myfolder/Magistr/Service/11/Serv1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/maksim/Myfolder/Magistr/Service/11/Serv1/build

# Include any dependencies generated for this target.
include CMakeFiles/best_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/best_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/best_server.dir/flags.make

CMakeFiles/best_server.dir/src/main.cpp.o: CMakeFiles/best_server.dir/flags.make
CMakeFiles/best_server.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maksim/Myfolder/Magistr/Service/11/Serv1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/best_server.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/best_server.dir/src/main.cpp.o -c /home/maksim/Myfolder/Magistr/Service/11/Serv1/src/main.cpp

CMakeFiles/best_server.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/best_server.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maksim/Myfolder/Magistr/Service/11/Serv1/src/main.cpp > CMakeFiles/best_server.dir/src/main.cpp.i

CMakeFiles/best_server.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/best_server.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maksim/Myfolder/Magistr/Service/11/Serv1/src/main.cpp -o CMakeFiles/best_server.dir/src/main.cpp.s

CMakeFiles/best_server.dir/src/Database/person.cpp.o: CMakeFiles/best_server.dir/flags.make
CMakeFiles/best_server.dir/src/Database/person.cpp.o: ../src/Database/person.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maksim/Myfolder/Magistr/Service/11/Serv1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/best_server.dir/src/Database/person.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/best_server.dir/src/Database/person.cpp.o -c /home/maksim/Myfolder/Magistr/Service/11/Serv1/src/Database/person.cpp

CMakeFiles/best_server.dir/src/Database/person.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/best_server.dir/src/Database/person.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maksim/Myfolder/Magistr/Service/11/Serv1/src/Database/person.cpp > CMakeFiles/best_server.dir/src/Database/person.cpp.i

CMakeFiles/best_server.dir/src/Database/person.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/best_server.dir/src/Database/person.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maksim/Myfolder/Magistr/Service/11/Serv1/src/Database/person.cpp -o CMakeFiles/best_server.dir/src/Database/person.cpp.s

CMakeFiles/best_server.dir/src/Server/web_server.cpp.o: CMakeFiles/best_server.dir/flags.make
CMakeFiles/best_server.dir/src/Server/web_server.cpp.o: ../src/Server/web_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maksim/Myfolder/Magistr/Service/11/Serv1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/best_server.dir/src/Server/web_server.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/best_server.dir/src/Server/web_server.cpp.o -c /home/maksim/Myfolder/Magistr/Service/11/Serv1/src/Server/web_server.cpp

CMakeFiles/best_server.dir/src/Server/web_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/best_server.dir/src/Server/web_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maksim/Myfolder/Magistr/Service/11/Serv1/src/Server/web_server.cpp > CMakeFiles/best_server.dir/src/Server/web_server.cpp.i

CMakeFiles/best_server.dir/src/Server/web_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/best_server.dir/src/Server/web_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maksim/Myfolder/Magistr/Service/11/Serv1/src/Server/web_server.cpp -o CMakeFiles/best_server.dir/src/Server/web_server.cpp.s

CMakeFiles/best_server.dir/src/Some_handlers/MyHendlers.cpp.o: CMakeFiles/best_server.dir/flags.make
CMakeFiles/best_server.dir/src/Some_handlers/MyHendlers.cpp.o: ../src/Some_handlers/MyHendlers.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/maksim/Myfolder/Magistr/Service/11/Serv1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/best_server.dir/src/Some_handlers/MyHendlers.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/best_server.dir/src/Some_handlers/MyHendlers.cpp.o -c /home/maksim/Myfolder/Magistr/Service/11/Serv1/src/Some_handlers/MyHendlers.cpp

CMakeFiles/best_server.dir/src/Some_handlers/MyHendlers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/best_server.dir/src/Some_handlers/MyHendlers.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/maksim/Myfolder/Magistr/Service/11/Serv1/src/Some_handlers/MyHendlers.cpp > CMakeFiles/best_server.dir/src/Some_handlers/MyHendlers.cpp.i

CMakeFiles/best_server.dir/src/Some_handlers/MyHendlers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/best_server.dir/src/Some_handlers/MyHendlers.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/maksim/Myfolder/Magistr/Service/11/Serv1/src/Some_handlers/MyHendlers.cpp -o CMakeFiles/best_server.dir/src/Some_handlers/MyHendlers.cpp.s

# Object files for target best_server
best_server_OBJECTS = \
"CMakeFiles/best_server.dir/src/main.cpp.o" \
"CMakeFiles/best_server.dir/src/Database/person.cpp.o" \
"CMakeFiles/best_server.dir/src/Server/web_server.cpp.o" \
"CMakeFiles/best_server.dir/src/Some_handlers/MyHendlers.cpp.o"

# External object files for target best_server
best_server_EXTERNAL_OBJECTS =

best_server: CMakeFiles/best_server.dir/src/main.cpp.o
best_server: CMakeFiles/best_server.dir/src/Database/person.cpp.o
best_server: CMakeFiles/best_server.dir/src/Server/web_server.cpp.o
best_server: CMakeFiles/best_server.dir/src/Some_handlers/MyHendlers.cpp.o
best_server: CMakeFiles/best_server.dir/build.make
best_server: /usr/local/lib/libPocoNetSSL.so.81
best_server: /usr/lib/x86_64-linux-gnu/libz.so
best_server: /usr/local/lib/libPocoUtil.so.81
best_server: /usr/local/lib/libPocoXML.so.81
best_server: /usr/local/lib/libPocoJSON.so.81
best_server: /usr/local/lib/libPocoNet.so.81
best_server: /usr/local/lib/libPocoCrypto.so.81
best_server: /usr/local/lib/libPocoFoundation.so.81
best_server: /usr/lib/x86_64-linux-gnu/libssl.so
best_server: /usr/lib/x86_64-linux-gnu/libcrypto.so
best_server: CMakeFiles/best_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maksim/Myfolder/Magistr/Service/11/Serv1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable best_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/best_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/best_server.dir/build: best_server

.PHONY : CMakeFiles/best_server.dir/build

# Object files for target best_server
best_server_OBJECTS = \
"CMakeFiles/best_server.dir/src/main.cpp.o" \
"CMakeFiles/best_server.dir/src/Database/person.cpp.o" \
"CMakeFiles/best_server.dir/src/Server/web_server.cpp.o" \
"CMakeFiles/best_server.dir/src/Some_handlers/MyHendlers.cpp.o"

# External object files for target best_server
best_server_EXTERNAL_OBJECTS =

CMakeFiles/CMakeRelink.dir/best_server: CMakeFiles/best_server.dir/src/main.cpp.o
CMakeFiles/CMakeRelink.dir/best_server: CMakeFiles/best_server.dir/src/Database/person.cpp.o
CMakeFiles/CMakeRelink.dir/best_server: CMakeFiles/best_server.dir/src/Server/web_server.cpp.o
CMakeFiles/CMakeRelink.dir/best_server: CMakeFiles/best_server.dir/src/Some_handlers/MyHendlers.cpp.o
CMakeFiles/CMakeRelink.dir/best_server: CMakeFiles/best_server.dir/build.make
CMakeFiles/CMakeRelink.dir/best_server: /usr/local/lib/libPocoNetSSL.so.81
CMakeFiles/CMakeRelink.dir/best_server: /usr/lib/x86_64-linux-gnu/libz.so
CMakeFiles/CMakeRelink.dir/best_server: /usr/local/lib/libPocoUtil.so.81
CMakeFiles/CMakeRelink.dir/best_server: /usr/local/lib/libPocoXML.so.81
CMakeFiles/CMakeRelink.dir/best_server: /usr/local/lib/libPocoJSON.so.81
CMakeFiles/CMakeRelink.dir/best_server: /usr/local/lib/libPocoNet.so.81
CMakeFiles/CMakeRelink.dir/best_server: /usr/local/lib/libPocoCrypto.so.81
CMakeFiles/CMakeRelink.dir/best_server: /usr/local/lib/libPocoFoundation.so.81
CMakeFiles/CMakeRelink.dir/best_server: /usr/lib/x86_64-linux-gnu/libssl.so
CMakeFiles/CMakeRelink.dir/best_server: /usr/lib/x86_64-linux-gnu/libcrypto.so
CMakeFiles/CMakeRelink.dir/best_server: CMakeFiles/best_server.dir/relink.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/maksim/Myfolder/Magistr/Service/11/Serv1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable CMakeFiles/CMakeRelink.dir/best_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/best_server.dir/relink.txt --verbose=$(VERBOSE)

# Rule to relink during preinstall.
CMakeFiles/best_server.dir/preinstall: CMakeFiles/CMakeRelink.dir/best_server

.PHONY : CMakeFiles/best_server.dir/preinstall

CMakeFiles/best_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/best_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/best_server.dir/clean

CMakeFiles/best_server.dir/depend:
	cd /home/maksim/Myfolder/Magistr/Service/11/Serv1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/maksim/Myfolder/Magistr/Service/11/Serv1 /home/maksim/Myfolder/Magistr/Service/11/Serv1 /home/maksim/Myfolder/Magistr/Service/11/Serv1/build /home/maksim/Myfolder/Magistr/Service/11/Serv1/build /home/maksim/Myfolder/Magistr/Service/11/Serv1/build/CMakeFiles/best_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/best_server.dir/depend
