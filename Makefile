# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/angusjoshi/tarski/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/angusjoshi/tarski

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/opt/homebrew/Cellar/cmake/3.27.7/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/opt/homebrew/Cellar/cmake/3.27.7/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/angusjoshi/tarski/CMakeFiles /Users/angusjoshi/tarski//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/angusjoshi/tarski/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named src

# Build rule for target.
src: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 src
.PHONY : src

# fast build rule for target.
src/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/build
.PHONY : src/fast

analysis/runAnalysis.o: analysis/runAnalysis.cpp.o
.PHONY : analysis/runAnalysis.o

# target to build an object file
analysis/runAnalysis.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/analysis/runAnalysis.cpp.o
.PHONY : analysis/runAnalysis.cpp.o

analysis/runAnalysis.i: analysis/runAnalysis.cpp.i
.PHONY : analysis/runAnalysis.i

# target to preprocess a source file
analysis/runAnalysis.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/analysis/runAnalysis.cpp.i
.PHONY : analysis/runAnalysis.cpp.i

analysis/runAnalysis.s: analysis/runAnalysis.cpp.s
.PHONY : analysis/runAnalysis.s

# target to generate assembly for a file
analysis/runAnalysis.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/analysis/runAnalysis.cpp.s
.PHONY : analysis/runAnalysis.cpp.s

arrival/arrivalInstance.o: arrival/arrivalInstance.cpp.o
.PHONY : arrival/arrivalInstance.o

# target to build an object file
arrival/arrivalInstance.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/arrival/arrivalInstance.cpp.o
.PHONY : arrival/arrivalInstance.cpp.o

arrival/arrivalInstance.i: arrival/arrivalInstance.cpp.i
.PHONY : arrival/arrivalInstance.i

# target to preprocess a source file
arrival/arrivalInstance.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/arrival/arrivalInstance.cpp.i
.PHONY : arrival/arrivalInstance.cpp.i

arrival/arrivalInstance.s: arrival/arrivalInstance.cpp.s
.PHONY : arrival/arrivalInstance.s

# target to generate assembly for a file
arrival/arrivalInstance.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/arrival/arrivalInstance.cpp.s
.PHONY : arrival/arrivalInstance.cpp.s

arrival/arrivalUtil.o: arrival/arrivalUtil.cpp.o
.PHONY : arrival/arrivalUtil.o

# target to build an object file
arrival/arrivalUtil.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/arrival/arrivalUtil.cpp.o
.PHONY : arrival/arrivalUtil.cpp.o

arrival/arrivalUtil.i: arrival/arrivalUtil.cpp.i
.PHONY : arrival/arrivalUtil.i

# target to preprocess a source file
arrival/arrivalUtil.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/arrival/arrivalUtil.cpp.i
.PHONY : arrival/arrivalUtil.cpp.i

arrival/arrivalUtil.s: arrival/arrivalUtil.cpp.s
.PHONY : arrival/arrivalUtil.s

# target to generate assembly for a file
arrival/arrivalUtil.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/arrival/arrivalUtil.cpp.s
.PHONY : arrival/arrivalUtil.cpp.s

arrival/generateInstance.o: arrival/generateInstance.cpp.o
.PHONY : arrival/generateInstance.o

# target to build an object file
arrival/generateInstance.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/arrival/generateInstance.cpp.o
.PHONY : arrival/generateInstance.cpp.o

arrival/generateInstance.i: arrival/generateInstance.cpp.i
.PHONY : arrival/generateInstance.i

# target to preprocess a source file
arrival/generateInstance.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/arrival/generateInstance.cpp.i
.PHONY : arrival/generateInstance.cpp.i

arrival/generateInstance.s: arrival/generateInstance.cpp.s
.PHONY : arrival/generateInstance.s

# target to generate assembly for a file
arrival/generateInstance.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/arrival/generateInstance.cpp.s
.PHONY : arrival/generateInstance.cpp.s

arrival/preprocessInstance.o: arrival/preprocessInstance.cpp.o
.PHONY : arrival/preprocessInstance.o

# target to build an object file
arrival/preprocessInstance.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/arrival/preprocessInstance.cpp.o
.PHONY : arrival/preprocessInstance.cpp.o

arrival/preprocessInstance.i: arrival/preprocessInstance.cpp.i
.PHONY : arrival/preprocessInstance.i

# target to preprocess a source file
arrival/preprocessInstance.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/arrival/preprocessInstance.cpp.i
.PHONY : arrival/preprocessInstance.cpp.i

arrival/preprocessInstance.s: arrival/preprocessInstance.cpp.s
.PHONY : arrival/preprocessInstance.s

# target to generate assembly for a file
arrival/preprocessInstance.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/arrival/preprocessInstance.cpp.s
.PHONY : arrival/preprocessInstance.cpp.s

arrival/simpleWalk.o: arrival/simpleWalk.cpp.o
.PHONY : arrival/simpleWalk.o

# target to build an object file
arrival/simpleWalk.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/arrival/simpleWalk.cpp.o
.PHONY : arrival/simpleWalk.cpp.o

arrival/simpleWalk.i: arrival/simpleWalk.cpp.i
.PHONY : arrival/simpleWalk.i

# target to preprocess a source file
arrival/simpleWalk.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/arrival/simpleWalk.cpp.i
.PHONY : arrival/simpleWalk.cpp.i

arrival/simpleWalk.s: arrival/simpleWalk.cpp.s
.PHONY : arrival/simpleWalk.s

# target to generate assembly for a file
arrival/simpleWalk.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/arrival/simpleWalk.cpp.s
.PHONY : arrival/simpleWalk.cpp.s

config.o: config.cpp.o
.PHONY : config.o

# target to build an object file
config.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/config.cpp.o
.PHONY : config.cpp.o

config.i: config.cpp.i
.PHONY : config.i

# target to preprocess a source file
config.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/config.cpp.i
.PHONY : config.cpp.i

config.s: config.cpp.s
.PHONY : config.s

# target to generate assembly for a file
config.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/config.cpp.s
.PHONY : config.cpp.s

fixpoint/findFixpointByMonotoneDecomp.o: fixpoint/findFixpointByMonotoneDecomp.cpp.o
.PHONY : fixpoint/findFixpointByMonotoneDecomp.o

# target to build an object file
fixpoint/findFixpointByMonotoneDecomp.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/findFixpointByMonotoneDecomp.cpp.o
.PHONY : fixpoint/findFixpointByMonotoneDecomp.cpp.o

fixpoint/findFixpointByMonotoneDecomp.i: fixpoint/findFixpointByMonotoneDecomp.cpp.i
.PHONY : fixpoint/findFixpointByMonotoneDecomp.i

# target to preprocess a source file
fixpoint/findFixpointByMonotoneDecomp.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/findFixpointByMonotoneDecomp.cpp.i
.PHONY : fixpoint/findFixpointByMonotoneDecomp.cpp.i

fixpoint/findFixpointByMonotoneDecomp.s: fixpoint/findFixpointByMonotoneDecomp.cpp.s
.PHONY : fixpoint/findFixpointByMonotoneDecomp.s

# target to generate assembly for a file
fixpoint/findFixpointByMonotoneDecomp.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/findFixpointByMonotoneDecomp.cpp.s
.PHONY : fixpoint/findFixpointByMonotoneDecomp.cpp.s

fixpoint/fixDecompAlgorithm.o: fixpoint/fixDecompAlgorithm.cpp.o
.PHONY : fixpoint/fixDecompAlgorithm.o

# target to build an object file
fixpoint/fixDecompAlgorithm.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/fixDecompAlgorithm.cpp.o
.PHONY : fixpoint/fixDecompAlgorithm.cpp.o

fixpoint/fixDecompAlgorithm.i: fixpoint/fixDecompAlgorithm.cpp.i
.PHONY : fixpoint/fixDecompAlgorithm.i

# target to preprocess a source file
fixpoint/fixDecompAlgorithm.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/fixDecompAlgorithm.cpp.i
.PHONY : fixpoint/fixDecompAlgorithm.cpp.i

fixpoint/fixDecompAlgorithm.s: fixpoint/fixDecompAlgorithm.cpp.s
.PHONY : fixpoint/fixDecompAlgorithm.s

# target to generate assembly for a file
fixpoint/fixDecompAlgorithm.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/fixDecompAlgorithm.cpp.s
.PHONY : fixpoint/fixDecompAlgorithm.cpp.s

fixpoint/innerAlgorithm.o: fixpoint/innerAlgorithm.cpp.o
.PHONY : fixpoint/innerAlgorithm.o

# target to build an object file
fixpoint/innerAlgorithm.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/innerAlgorithm.cpp.o
.PHONY : fixpoint/innerAlgorithm.cpp.o

fixpoint/innerAlgorithm.i: fixpoint/innerAlgorithm.cpp.i
.PHONY : fixpoint/innerAlgorithm.i

# target to preprocess a source file
fixpoint/innerAlgorithm.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/innerAlgorithm.cpp.i
.PHONY : fixpoint/innerAlgorithm.cpp.i

fixpoint/innerAlgorithm.s: fixpoint/innerAlgorithm.cpp.s
.PHONY : fixpoint/innerAlgorithm.s

# target to generate assembly for a file
fixpoint/innerAlgorithm.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/innerAlgorithm.cpp.s
.PHONY : fixpoint/innerAlgorithm.cpp.s

fixpoint/kleeneTarski.o: fixpoint/kleeneTarski.cpp.o
.PHONY : fixpoint/kleeneTarski.o

# target to build an object file
fixpoint/kleeneTarski.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/kleeneTarski.cpp.o
.PHONY : fixpoint/kleeneTarski.cpp.o

fixpoint/kleeneTarski.i: fixpoint/kleeneTarski.cpp.i
.PHONY : fixpoint/kleeneTarski.i

# target to preprocess a source file
fixpoint/kleeneTarski.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/kleeneTarski.cpp.i
.PHONY : fixpoint/kleeneTarski.cpp.i

fixpoint/kleeneTarski.s: fixpoint/kleeneTarski.cpp.s
.PHONY : fixpoint/kleeneTarski.s

# target to generate assembly for a file
fixpoint/kleeneTarski.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/kleeneTarski.cpp.s
.PHONY : fixpoint/kleeneTarski.cpp.s

fixpoint/latticeUtil.o: fixpoint/latticeUtil.cpp.o
.PHONY : fixpoint/latticeUtil.o

# target to build an object file
fixpoint/latticeUtil.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/latticeUtil.cpp.o
.PHONY : fixpoint/latticeUtil.cpp.o

fixpoint/latticeUtil.i: fixpoint/latticeUtil.cpp.i
.PHONY : fixpoint/latticeUtil.i

# target to preprocess a source file
fixpoint/latticeUtil.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/latticeUtil.cpp.i
.PHONY : fixpoint/latticeUtil.cpp.i

fixpoint/latticeUtil.s: fixpoint/latticeUtil.cpp.s
.PHONY : fixpoint/latticeUtil.s

# target to generate assembly for a file
fixpoint/latticeUtil.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/latticeUtil.cpp.s
.PHONY : fixpoint/latticeUtil.cpp.s

fixpoint/monotoneDecompAlgorithm.o: fixpoint/monotoneDecompAlgorithm.cpp.o
.PHONY : fixpoint/monotoneDecompAlgorithm.o

# target to build an object file
fixpoint/monotoneDecompAlgorithm.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/monotoneDecompAlgorithm.cpp.o
.PHONY : fixpoint/monotoneDecompAlgorithm.cpp.o

fixpoint/monotoneDecompAlgorithm.i: fixpoint/monotoneDecompAlgorithm.cpp.i
.PHONY : fixpoint/monotoneDecompAlgorithm.i

# target to preprocess a source file
fixpoint/monotoneDecompAlgorithm.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/monotoneDecompAlgorithm.cpp.i
.PHONY : fixpoint/monotoneDecompAlgorithm.cpp.i

fixpoint/monotoneDecompAlgorithm.s: fixpoint/monotoneDecompAlgorithm.cpp.s
.PHONY : fixpoint/monotoneDecompAlgorithm.s

# target to generate assembly for a file
fixpoint/monotoneDecompAlgorithm.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/monotoneDecompAlgorithm.cpp.s
.PHONY : fixpoint/monotoneDecompAlgorithm.cpp.s

fixpoint/monotoneFunction.o: fixpoint/monotoneFunction.cpp.o
.PHONY : fixpoint/monotoneFunction.o

# target to build an object file
fixpoint/monotoneFunction.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/monotoneFunction.cpp.o
.PHONY : fixpoint/monotoneFunction.cpp.o

fixpoint/monotoneFunction.i: fixpoint/monotoneFunction.cpp.i
.PHONY : fixpoint/monotoneFunction.i

# target to preprocess a source file
fixpoint/monotoneFunction.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/monotoneFunction.cpp.i
.PHONY : fixpoint/monotoneFunction.cpp.i

fixpoint/monotoneFunction.s: fixpoint/monotoneFunction.cpp.s
.PHONY : fixpoint/monotoneFunction.s

# target to generate assembly for a file
fixpoint/monotoneFunction.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/monotoneFunction.cpp.s
.PHONY : fixpoint/monotoneFunction.cpp.s

fixpoint/recursiveBinarySearch.o: fixpoint/recursiveBinarySearch.cpp.o
.PHONY : fixpoint/recursiveBinarySearch.o

# target to build an object file
fixpoint/recursiveBinarySearch.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/recursiveBinarySearch.cpp.o
.PHONY : fixpoint/recursiveBinarySearch.cpp.o

fixpoint/recursiveBinarySearch.i: fixpoint/recursiveBinarySearch.cpp.i
.PHONY : fixpoint/recursiveBinarySearch.i

# target to preprocess a source file
fixpoint/recursiveBinarySearch.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/recursiveBinarySearch.cpp.i
.PHONY : fixpoint/recursiveBinarySearch.cpp.i

fixpoint/recursiveBinarySearch.s: fixpoint/recursiveBinarySearch.cpp.s
.PHONY : fixpoint/recursiveBinarySearch.s

# target to generate assembly for a file
fixpoint/recursiveBinarySearch.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/recursiveBinarySearch.cpp.s
.PHONY : fixpoint/recursiveBinarySearch.cpp.s

fixpoint/threeDimensionAlgorithm.o: fixpoint/threeDimensionAlgorithm.cpp.o
.PHONY : fixpoint/threeDimensionAlgorithm.o

# target to build an object file
fixpoint/threeDimensionAlgorithm.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/threeDimensionAlgorithm.cpp.o
.PHONY : fixpoint/threeDimensionAlgorithm.cpp.o

fixpoint/threeDimensionAlgorithm.i: fixpoint/threeDimensionAlgorithm.cpp.i
.PHONY : fixpoint/threeDimensionAlgorithm.i

# target to preprocess a source file
fixpoint/threeDimensionAlgorithm.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/threeDimensionAlgorithm.cpp.i
.PHONY : fixpoint/threeDimensionAlgorithm.cpp.i

fixpoint/threeDimensionAlgorithm.s: fixpoint/threeDimensionAlgorithm.cpp.s
.PHONY : fixpoint/threeDimensionAlgorithm.s

# target to generate assembly for a file
fixpoint/threeDimensionAlgorithm.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/fixpoint/threeDimensionAlgorithm.cpp.s
.PHONY : fixpoint/threeDimensionAlgorithm.cpp.s

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/main.cpp.s
.PHONY : main.cpp.s

shapley-stochastic-game/shapleyStochasticGame.o: shapley-stochastic-game/shapleyStochasticGame.cpp.o
.PHONY : shapley-stochastic-game/shapleyStochasticGame.o

# target to build an object file
shapley-stochastic-game/shapleyStochasticGame.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/shapley-stochastic-game/shapleyStochasticGame.cpp.o
.PHONY : shapley-stochastic-game/shapleyStochasticGame.cpp.o

shapley-stochastic-game/shapleyStochasticGame.i: shapley-stochastic-game/shapleyStochasticGame.cpp.i
.PHONY : shapley-stochastic-game/shapleyStochasticGame.i

# target to preprocess a source file
shapley-stochastic-game/shapleyStochasticGame.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/shapley-stochastic-game/shapleyStochasticGame.cpp.i
.PHONY : shapley-stochastic-game/shapleyStochasticGame.cpp.i

shapley-stochastic-game/shapleyStochasticGame.s: shapley-stochastic-game/shapleyStochasticGame.cpp.s
.PHONY : shapley-stochastic-game/shapleyStochasticGame.s

# target to generate assembly for a file
shapley-stochastic-game/shapleyStochasticGame.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/shapley-stochastic-game/shapleyStochasticGame.cpp.s
.PHONY : shapley-stochastic-game/shapleyStochasticGame.cpp.s

shapley-stochastic-game/shapleyStochasticGameGenerator.o: shapley-stochastic-game/shapleyStochasticGameGenerator.cpp.o
.PHONY : shapley-stochastic-game/shapleyStochasticGameGenerator.o

# target to build an object file
shapley-stochastic-game/shapleyStochasticGameGenerator.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/shapley-stochastic-game/shapleyStochasticGameGenerator.cpp.o
.PHONY : shapley-stochastic-game/shapleyStochasticGameGenerator.cpp.o

shapley-stochastic-game/shapleyStochasticGameGenerator.i: shapley-stochastic-game/shapleyStochasticGameGenerator.cpp.i
.PHONY : shapley-stochastic-game/shapleyStochasticGameGenerator.i

# target to preprocess a source file
shapley-stochastic-game/shapleyStochasticGameGenerator.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/shapley-stochastic-game/shapleyStochasticGameGenerator.cpp.i
.PHONY : shapley-stochastic-game/shapleyStochasticGameGenerator.cpp.i

shapley-stochastic-game/shapleyStochasticGameGenerator.s: shapley-stochastic-game/shapleyStochasticGameGenerator.cpp.s
.PHONY : shapley-stochastic-game/shapleyStochasticGameGenerator.s

# target to generate assembly for a file
shapley-stochastic-game/shapleyStochasticGameGenerator.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/shapley-stochastic-game/shapleyStochasticGameGenerator.cpp.s
.PHONY : shapley-stochastic-game/shapleyStochasticGameGenerator.cpp.s

simple-stochatic-game/simpleStochasticGame.o: simple-stochatic-game/simpleStochasticGame.cpp.o
.PHONY : simple-stochatic-game/simpleStochasticGame.o

# target to build an object file
simple-stochatic-game/simpleStochasticGame.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/simple-stochatic-game/simpleStochasticGame.cpp.o
.PHONY : simple-stochatic-game/simpleStochasticGame.cpp.o

simple-stochatic-game/simpleStochasticGame.i: simple-stochatic-game/simpleStochasticGame.cpp.i
.PHONY : simple-stochatic-game/simpleStochasticGame.i

# target to preprocess a source file
simple-stochatic-game/simpleStochasticGame.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/simple-stochatic-game/simpleStochasticGame.cpp.i
.PHONY : simple-stochatic-game/simpleStochasticGame.cpp.i

simple-stochatic-game/simpleStochasticGame.s: simple-stochatic-game/simpleStochasticGame.cpp.s
.PHONY : simple-stochatic-game/simpleStochasticGame.s

# target to generate assembly for a file
simple-stochatic-game/simpleStochasticGame.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/simple-stochatic-game/simpleStochasticGame.cpp.s
.PHONY : simple-stochatic-game/simpleStochasticGame.cpp.s

simple-stochatic-game/simpleStochasticGameGenerator.o: simple-stochatic-game/simpleStochasticGameGenerator.cpp.o
.PHONY : simple-stochatic-game/simpleStochasticGameGenerator.o

# target to build an object file
simple-stochatic-game/simpleStochasticGameGenerator.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/simple-stochatic-game/simpleStochasticGameGenerator.cpp.o
.PHONY : simple-stochatic-game/simpleStochasticGameGenerator.cpp.o

simple-stochatic-game/simpleStochasticGameGenerator.i: simple-stochatic-game/simpleStochasticGameGenerator.cpp.i
.PHONY : simple-stochatic-game/simpleStochasticGameGenerator.i

# target to preprocess a source file
simple-stochatic-game/simpleStochasticGameGenerator.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/simple-stochatic-game/simpleStochasticGameGenerator.cpp.i
.PHONY : simple-stochatic-game/simpleStochasticGameGenerator.cpp.i

simple-stochatic-game/simpleStochasticGameGenerator.s: simple-stochatic-game/simpleStochasticGameGenerator.cpp.s
.PHONY : simple-stochatic-game/simpleStochasticGameGenerator.s

# target to generate assembly for a file
simple-stochatic-game/simpleStochasticGameGenerator.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/src.dir/build.make CMakeFiles/src.dir/simple-stochatic-game/simpleStochasticGameGenerator.cpp.s
.PHONY : simple-stochatic-game/simpleStochasticGameGenerator.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... src"
	@echo "... analysis/runAnalysis.o"
	@echo "... analysis/runAnalysis.i"
	@echo "... analysis/runAnalysis.s"
	@echo "... arrival/arrivalInstance.o"
	@echo "... arrival/arrivalInstance.i"
	@echo "... arrival/arrivalInstance.s"
	@echo "... arrival/arrivalUtil.o"
	@echo "... arrival/arrivalUtil.i"
	@echo "... arrival/arrivalUtil.s"
	@echo "... arrival/generateInstance.o"
	@echo "... arrival/generateInstance.i"
	@echo "... arrival/generateInstance.s"
	@echo "... arrival/preprocessInstance.o"
	@echo "... arrival/preprocessInstance.i"
	@echo "... arrival/preprocessInstance.s"
	@echo "... arrival/simpleWalk.o"
	@echo "... arrival/simpleWalk.i"
	@echo "... arrival/simpleWalk.s"
	@echo "... config.o"
	@echo "... config.i"
	@echo "... config.s"
	@echo "... fixpoint/findFixpointByMonotoneDecomp.o"
	@echo "... fixpoint/findFixpointByMonotoneDecomp.i"
	@echo "... fixpoint/findFixpointByMonotoneDecomp.s"
	@echo "... fixpoint/fixDecompAlgorithm.o"
	@echo "... fixpoint/fixDecompAlgorithm.i"
	@echo "... fixpoint/fixDecompAlgorithm.s"
	@echo "... fixpoint/innerAlgorithm.o"
	@echo "... fixpoint/innerAlgorithm.i"
	@echo "... fixpoint/innerAlgorithm.s"
	@echo "... fixpoint/kleeneTarski.o"
	@echo "... fixpoint/kleeneTarski.i"
	@echo "... fixpoint/kleeneTarski.s"
	@echo "... fixpoint/latticeUtil.o"
	@echo "... fixpoint/latticeUtil.i"
	@echo "... fixpoint/latticeUtil.s"
	@echo "... fixpoint/monotoneDecompAlgorithm.o"
	@echo "... fixpoint/monotoneDecompAlgorithm.i"
	@echo "... fixpoint/monotoneDecompAlgorithm.s"
	@echo "... fixpoint/monotoneFunction.o"
	@echo "... fixpoint/monotoneFunction.i"
	@echo "... fixpoint/monotoneFunction.s"
	@echo "... fixpoint/recursiveBinarySearch.o"
	@echo "... fixpoint/recursiveBinarySearch.i"
	@echo "... fixpoint/recursiveBinarySearch.s"
	@echo "... fixpoint/threeDimensionAlgorithm.o"
	@echo "... fixpoint/threeDimensionAlgorithm.i"
	@echo "... fixpoint/threeDimensionAlgorithm.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... shapley-stochastic-game/shapleyStochasticGame.o"
	@echo "... shapley-stochastic-game/shapleyStochasticGame.i"
	@echo "... shapley-stochastic-game/shapleyStochasticGame.s"
	@echo "... shapley-stochastic-game/shapleyStochasticGameGenerator.o"
	@echo "... shapley-stochastic-game/shapleyStochasticGameGenerator.i"
	@echo "... shapley-stochastic-game/shapleyStochasticGameGenerator.s"
	@echo "... simple-stochatic-game/simpleStochasticGame.o"
	@echo "... simple-stochatic-game/simpleStochasticGame.i"
	@echo "... simple-stochatic-game/simpleStochasticGame.s"
	@echo "... simple-stochatic-game/simpleStochasticGameGenerator.o"
	@echo "... simple-stochatic-game/simpleStochasticGameGenerator.i"
	@echo "... simple-stochatic-game/simpleStochasticGameGenerator.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

