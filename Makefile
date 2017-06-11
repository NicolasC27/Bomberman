# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/nicolas/rendu/cpp_indie_studio

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nicolas/rendu/cpp_indie_studio

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/usr/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/usr/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/usr/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/cmake-gui -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/nicolas/rendu/cpp_indie_studio/CMakeFiles /home/nicolas/rendu/cpp_indie_studio/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/nicolas/rendu/cpp_indie_studio/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named bomberman

# Build rule for target.
bomberman: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 bomberman
.PHONY : bomberman

# fast build rule for target.
bomberman/fast:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/build
.PHONY : bomberman/fast

src/Collision.o: src/Collision.cpp.o

.PHONY : src/Collision.o

# target to build an object file
src/Collision.cpp.o:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Collision.cpp.o
.PHONY : src/Collision.cpp.o

src/Collision.i: src/Collision.cpp.i

.PHONY : src/Collision.i

# target to preprocess a source file
src/Collision.cpp.i:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Collision.cpp.i
.PHONY : src/Collision.cpp.i

src/Collision.s: src/Collision.cpp.s

.PHONY : src/Collision.s

# target to generate assembly for a file
src/Collision.cpp.s:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Collision.cpp.s
.PHONY : src/Collision.cpp.s

src/Common/Manager/CameraManager.o: src/Common/Manager/CameraManager.cpp.o

.PHONY : src/Common/Manager/CameraManager.o

# target to build an object file
src/Common/Manager/CameraManager.cpp.o:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Common/Manager/CameraManager.cpp.o
.PHONY : src/Common/Manager/CameraManager.cpp.o

src/Common/Manager/CameraManager.i: src/Common/Manager/CameraManager.cpp.i

.PHONY : src/Common/Manager/CameraManager.i

# target to preprocess a source file
src/Common/Manager/CameraManager.cpp.i:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Common/Manager/CameraManager.cpp.i
.PHONY : src/Common/Manager/CameraManager.cpp.i

src/Common/Manager/CameraManager.s: src/Common/Manager/CameraManager.cpp.s

.PHONY : src/Common/Manager/CameraManager.s

# target to generate assembly for a file
src/Common/Manager/CameraManager.cpp.s:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Common/Manager/CameraManager.cpp.s
.PHONY : src/Common/Manager/CameraManager.cpp.s

src/Common/Manager/GameManager.o: src/Common/Manager/GameManager.cpp.o

.PHONY : src/Common/Manager/GameManager.o

# target to build an object file
src/Common/Manager/GameManager.cpp.o:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Common/Manager/GameManager.cpp.o
.PHONY : src/Common/Manager/GameManager.cpp.o

src/Common/Manager/GameManager.i: src/Common/Manager/GameManager.cpp.i

.PHONY : src/Common/Manager/GameManager.i

# target to preprocess a source file
src/Common/Manager/GameManager.cpp.i:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Common/Manager/GameManager.cpp.i
.PHONY : src/Common/Manager/GameManager.cpp.i

src/Common/Manager/GameManager.s: src/Common/Manager/GameManager.cpp.s

.PHONY : src/Common/Manager/GameManager.s

# target to generate assembly for a file
src/Common/Manager/GameManager.cpp.s:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Common/Manager/GameManager.cpp.s
.PHONY : src/Common/Manager/GameManager.cpp.s

src/Common/Manager/NodeManager.o: src/Common/Manager/NodeManager.cpp.o

.PHONY : src/Common/Manager/NodeManager.o

# target to build an object file
src/Common/Manager/NodeManager.cpp.o:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Common/Manager/NodeManager.cpp.o
.PHONY : src/Common/Manager/NodeManager.cpp.o

src/Common/Manager/NodeManager.i: src/Common/Manager/NodeManager.cpp.i

.PHONY : src/Common/Manager/NodeManager.i

# target to preprocess a source file
src/Common/Manager/NodeManager.cpp.i:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Common/Manager/NodeManager.cpp.i
.PHONY : src/Common/Manager/NodeManager.cpp.i

src/Common/Manager/NodeManager.s: src/Common/Manager/NodeManager.cpp.s

.PHONY : src/Common/Manager/NodeManager.s

# target to generate assembly for a file
src/Common/Manager/NodeManager.cpp.s:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Common/Manager/NodeManager.cpp.s
.PHONY : src/Common/Manager/NodeManager.cpp.s

src/Controller/EventManager.o: src/Controller/EventManager.cpp.o

.PHONY : src/Controller/EventManager.o

# target to build an object file
src/Controller/EventManager.cpp.o:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Controller/EventManager.cpp.o
.PHONY : src/Controller/EventManager.cpp.o

src/Controller/EventManager.i: src/Controller/EventManager.cpp.i

.PHONY : src/Controller/EventManager.i

# target to preprocess a source file
src/Controller/EventManager.cpp.i:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Controller/EventManager.cpp.i
.PHONY : src/Controller/EventManager.cpp.i

src/Controller/EventManager.s: src/Controller/EventManager.cpp.s

.PHONY : src/Controller/EventManager.s

# target to generate assembly for a file
src/Controller/EventManager.cpp.s:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Controller/EventManager.cpp.s
.PHONY : src/Controller/EventManager.cpp.s

src/MapManager.o: src/MapManager.cpp.o

.PHONY : src/MapManager.o

# target to build an object file
src/MapManager.cpp.o:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/MapManager.cpp.o
.PHONY : src/MapManager.cpp.o

src/MapManager.i: src/MapManager.cpp.i

.PHONY : src/MapManager.i

# target to preprocess a source file
src/MapManager.cpp.i:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/MapManager.cpp.i
.PHONY : src/MapManager.cpp.i

src/MapManager.s: src/MapManager.cpp.s

.PHONY : src/MapManager.s

# target to generate assembly for a file
src/MapManager.cpp.s:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/MapManager.cpp.s
.PHONY : src/MapManager.cpp.s

src/Objects/ACharacter.o: src/Objects/ACharacter.cpp.o

.PHONY : src/Objects/ACharacter.o

# target to build an object file
src/Objects/ACharacter.cpp.o:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Objects/ACharacter.cpp.o
.PHONY : src/Objects/ACharacter.cpp.o

src/Objects/ACharacter.i: src/Objects/ACharacter.cpp.i

.PHONY : src/Objects/ACharacter.i

# target to preprocess a source file
src/Objects/ACharacter.cpp.i:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Objects/ACharacter.cpp.i
.PHONY : src/Objects/ACharacter.cpp.i

src/Objects/ACharacter.s: src/Objects/ACharacter.cpp.s

.PHONY : src/Objects/ACharacter.s

# target to generate assembly for a file
src/Objects/ACharacter.cpp.s:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Objects/ACharacter.cpp.s
.PHONY : src/Objects/ACharacter.cpp.s

src/Objects/AGameObject.o: src/Objects/AGameObject.cpp.o

.PHONY : src/Objects/AGameObject.o

# target to build an object file
src/Objects/AGameObject.cpp.o:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Objects/AGameObject.cpp.o
.PHONY : src/Objects/AGameObject.cpp.o

src/Objects/AGameObject.i: src/Objects/AGameObject.cpp.i

.PHONY : src/Objects/AGameObject.i

# target to preprocess a source file
src/Objects/AGameObject.cpp.i:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Objects/AGameObject.cpp.i
.PHONY : src/Objects/AGameObject.cpp.i

src/Objects/AGameObject.s: src/Objects/AGameObject.cpp.s

.PHONY : src/Objects/AGameObject.s

# target to generate assembly for a file
src/Objects/AGameObject.cpp.s:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Objects/AGameObject.cpp.s
.PHONY : src/Objects/AGameObject.cpp.s

src/Objects/Ground.o: src/Objects/Ground.cpp.o

.PHONY : src/Objects/Ground.o

# target to build an object file
src/Objects/Ground.cpp.o:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Objects/Ground.cpp.o
.PHONY : src/Objects/Ground.cpp.o

src/Objects/Ground.i: src/Objects/Ground.cpp.i

.PHONY : src/Objects/Ground.i

# target to preprocess a source file
src/Objects/Ground.cpp.i:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Objects/Ground.cpp.i
.PHONY : src/Objects/Ground.cpp.i

src/Objects/Ground.s: src/Objects/Ground.cpp.s

.PHONY : src/Objects/Ground.s

# target to generate assembly for a file
src/Objects/Ground.cpp.s:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Objects/Ground.cpp.s
.PHONY : src/Objects/Ground.cpp.s

src/Objects/Player.o: src/Objects/Player.cpp.o

.PHONY : src/Objects/Player.o

# target to build an object file
src/Objects/Player.cpp.o:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Objects/Player.cpp.o
.PHONY : src/Objects/Player.cpp.o

src/Objects/Player.i: src/Objects/Player.cpp.i

.PHONY : src/Objects/Player.i

# target to preprocess a source file
src/Objects/Player.cpp.i:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Objects/Player.cpp.i
.PHONY : src/Objects/Player.cpp.i

src/Objects/Player.s: src/Objects/Player.cpp.s

.PHONY : src/Objects/Player.s

# target to generate assembly for a file
src/Objects/Player.cpp.s:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Objects/Player.cpp.s
.PHONY : src/Objects/Player.cpp.s

src/Objects/Wall.o: src/Objects/Wall.cpp.o

.PHONY : src/Objects/Wall.o

# target to build an object file
src/Objects/Wall.cpp.o:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Objects/Wall.cpp.o
.PHONY : src/Objects/Wall.cpp.o

src/Objects/Wall.i: src/Objects/Wall.cpp.i

.PHONY : src/Objects/Wall.i

# target to preprocess a source file
src/Objects/Wall.cpp.i:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Objects/Wall.cpp.i
.PHONY : src/Objects/Wall.cpp.i

src/Objects/Wall.s: src/Objects/Wall.cpp.s

.PHONY : src/Objects/Wall.s

# target to generate assembly for a file
src/Objects/Wall.cpp.s:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/Objects/Wall.cpp.s
.PHONY : src/Objects/Wall.cpp.s

src/main.o: src/main.cpp.o

.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) -f CMakeFiles/bomberman.dir/build.make CMakeFiles/bomberman.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... install/strip"
	@echo "... install/local"
	@echo "... install"
	@echo "... bomberman"
	@echo "... list_install_components"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... src/Collision.o"
	@echo "... src/Collision.i"
	@echo "... src/Collision.s"
	@echo "... src/Common/Manager/CameraManager.o"
	@echo "... src/Common/Manager/CameraManager.i"
	@echo "... src/Common/Manager/CameraManager.s"
	@echo "... src/Common/Manager/GameManager.o"
	@echo "... src/Common/Manager/GameManager.i"
	@echo "... src/Common/Manager/GameManager.s"
	@echo "... src/Common/Manager/NodeManager.o"
	@echo "... src/Common/Manager/NodeManager.i"
	@echo "... src/Common/Manager/NodeManager.s"
	@echo "... src/Controller/EventManager.o"
	@echo "... src/Controller/EventManager.i"
	@echo "... src/Controller/EventManager.s"
	@echo "... src/MapManager.o"
	@echo "... src/MapManager.i"
	@echo "... src/MapManager.s"
	@echo "... src/Objects/ACharacter.o"
	@echo "... src/Objects/ACharacter.i"
	@echo "... src/Objects/ACharacter.s"
	@echo "... src/Objects/AGameObject.o"
	@echo "... src/Objects/AGameObject.i"
	@echo "... src/Objects/AGameObject.s"
	@echo "... src/Objects/Ground.o"
	@echo "... src/Objects/Ground.i"
	@echo "... src/Objects/Ground.s"
	@echo "... src/Objects/Player.o"
	@echo "... src/Objects/Player.i"
	@echo "... src/Objects/Player.s"
	@echo "... src/Objects/Wall.o"
	@echo "... src/Objects/Wall.i"
	@echo "... src/Objects/Wall.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
