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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vgate/Geant4_Example/examples/basic/B2/ProCom

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build

# Include any dependencies generated for this target.
include CMakeFiles/exampleB2b.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/exampleB2b.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/exampleB2b.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/exampleB2b.dir/flags.make

CMakeFiles/exampleB2b.dir/exampleB2b.cc.o: CMakeFiles/exampleB2b.dir/flags.make
CMakeFiles/exampleB2b.dir/exampleB2b.cc.o: ../exampleB2b.cc
CMakeFiles/exampleB2b.dir/exampleB2b.cc.o: CMakeFiles/exampleB2b.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/exampleB2b.dir/exampleB2b.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exampleB2b.dir/exampleB2b.cc.o -MF CMakeFiles/exampleB2b.dir/exampleB2b.cc.o.d -o CMakeFiles/exampleB2b.dir/exampleB2b.cc.o -c /home/vgate/Geant4_Example/examples/basic/B2/ProCom/exampleB2b.cc

CMakeFiles/exampleB2b.dir/exampleB2b.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB2b.dir/exampleB2b.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vgate/Geant4_Example/examples/basic/B2/ProCom/exampleB2b.cc > CMakeFiles/exampleB2b.dir/exampleB2b.cc.i

CMakeFiles/exampleB2b.dir/exampleB2b.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB2b.dir/exampleB2b.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vgate/Geant4_Example/examples/basic/B2/ProCom/exampleB2b.cc -o CMakeFiles/exampleB2b.dir/exampleB2b.cc.s

CMakeFiles/exampleB2b.dir/src/ActionInitialization.cc.o: CMakeFiles/exampleB2b.dir/flags.make
CMakeFiles/exampleB2b.dir/src/ActionInitialization.cc.o: ../src/ActionInitialization.cc
CMakeFiles/exampleB2b.dir/src/ActionInitialization.cc.o: CMakeFiles/exampleB2b.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/exampleB2b.dir/src/ActionInitialization.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exampleB2b.dir/src/ActionInitialization.cc.o -MF CMakeFiles/exampleB2b.dir/src/ActionInitialization.cc.o.d -o CMakeFiles/exampleB2b.dir/src/ActionInitialization.cc.o -c /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/ActionInitialization.cc

CMakeFiles/exampleB2b.dir/src/ActionInitialization.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB2b.dir/src/ActionInitialization.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/ActionInitialization.cc > CMakeFiles/exampleB2b.dir/src/ActionInitialization.cc.i

CMakeFiles/exampleB2b.dir/src/ActionInitialization.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB2b.dir/src/ActionInitialization.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/ActionInitialization.cc -o CMakeFiles/exampleB2b.dir/src/ActionInitialization.cc.s

CMakeFiles/exampleB2b.dir/src/ChamberParameterisation.cc.o: CMakeFiles/exampleB2b.dir/flags.make
CMakeFiles/exampleB2b.dir/src/ChamberParameterisation.cc.o: ../src/ChamberParameterisation.cc
CMakeFiles/exampleB2b.dir/src/ChamberParameterisation.cc.o: CMakeFiles/exampleB2b.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/exampleB2b.dir/src/ChamberParameterisation.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exampleB2b.dir/src/ChamberParameterisation.cc.o -MF CMakeFiles/exampleB2b.dir/src/ChamberParameterisation.cc.o.d -o CMakeFiles/exampleB2b.dir/src/ChamberParameterisation.cc.o -c /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/ChamberParameterisation.cc

CMakeFiles/exampleB2b.dir/src/ChamberParameterisation.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB2b.dir/src/ChamberParameterisation.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/ChamberParameterisation.cc > CMakeFiles/exampleB2b.dir/src/ChamberParameterisation.cc.i

CMakeFiles/exampleB2b.dir/src/ChamberParameterisation.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB2b.dir/src/ChamberParameterisation.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/ChamberParameterisation.cc -o CMakeFiles/exampleB2b.dir/src/ChamberParameterisation.cc.s

CMakeFiles/exampleB2b.dir/src/DetectorConstruction.cc.o: CMakeFiles/exampleB2b.dir/flags.make
CMakeFiles/exampleB2b.dir/src/DetectorConstruction.cc.o: ../src/DetectorConstruction.cc
CMakeFiles/exampleB2b.dir/src/DetectorConstruction.cc.o: CMakeFiles/exampleB2b.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/exampleB2b.dir/src/DetectorConstruction.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exampleB2b.dir/src/DetectorConstruction.cc.o -MF CMakeFiles/exampleB2b.dir/src/DetectorConstruction.cc.o.d -o CMakeFiles/exampleB2b.dir/src/DetectorConstruction.cc.o -c /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/DetectorConstruction.cc

CMakeFiles/exampleB2b.dir/src/DetectorConstruction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB2b.dir/src/DetectorConstruction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/DetectorConstruction.cc > CMakeFiles/exampleB2b.dir/src/DetectorConstruction.cc.i

CMakeFiles/exampleB2b.dir/src/DetectorConstruction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB2b.dir/src/DetectorConstruction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/DetectorConstruction.cc -o CMakeFiles/exampleB2b.dir/src/DetectorConstruction.cc.s

CMakeFiles/exampleB2b.dir/src/DetectorMessenger.cc.o: CMakeFiles/exampleB2b.dir/flags.make
CMakeFiles/exampleB2b.dir/src/DetectorMessenger.cc.o: ../src/DetectorMessenger.cc
CMakeFiles/exampleB2b.dir/src/DetectorMessenger.cc.o: CMakeFiles/exampleB2b.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/exampleB2b.dir/src/DetectorMessenger.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exampleB2b.dir/src/DetectorMessenger.cc.o -MF CMakeFiles/exampleB2b.dir/src/DetectorMessenger.cc.o.d -o CMakeFiles/exampleB2b.dir/src/DetectorMessenger.cc.o -c /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/DetectorMessenger.cc

CMakeFiles/exampleB2b.dir/src/DetectorMessenger.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB2b.dir/src/DetectorMessenger.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/DetectorMessenger.cc > CMakeFiles/exampleB2b.dir/src/DetectorMessenger.cc.i

CMakeFiles/exampleB2b.dir/src/DetectorMessenger.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB2b.dir/src/DetectorMessenger.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/DetectorMessenger.cc -o CMakeFiles/exampleB2b.dir/src/DetectorMessenger.cc.s

CMakeFiles/exampleB2b.dir/src/EventAction.cc.o: CMakeFiles/exampleB2b.dir/flags.make
CMakeFiles/exampleB2b.dir/src/EventAction.cc.o: ../src/EventAction.cc
CMakeFiles/exampleB2b.dir/src/EventAction.cc.o: CMakeFiles/exampleB2b.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/exampleB2b.dir/src/EventAction.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exampleB2b.dir/src/EventAction.cc.o -MF CMakeFiles/exampleB2b.dir/src/EventAction.cc.o.d -o CMakeFiles/exampleB2b.dir/src/EventAction.cc.o -c /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/EventAction.cc

CMakeFiles/exampleB2b.dir/src/EventAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB2b.dir/src/EventAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/EventAction.cc > CMakeFiles/exampleB2b.dir/src/EventAction.cc.i

CMakeFiles/exampleB2b.dir/src/EventAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB2b.dir/src/EventAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/EventAction.cc -o CMakeFiles/exampleB2b.dir/src/EventAction.cc.s

CMakeFiles/exampleB2b.dir/src/PrimaryGeneratorAction.cc.o: CMakeFiles/exampleB2b.dir/flags.make
CMakeFiles/exampleB2b.dir/src/PrimaryGeneratorAction.cc.o: ../src/PrimaryGeneratorAction.cc
CMakeFiles/exampleB2b.dir/src/PrimaryGeneratorAction.cc.o: CMakeFiles/exampleB2b.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/exampleB2b.dir/src/PrimaryGeneratorAction.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exampleB2b.dir/src/PrimaryGeneratorAction.cc.o -MF CMakeFiles/exampleB2b.dir/src/PrimaryGeneratorAction.cc.o.d -o CMakeFiles/exampleB2b.dir/src/PrimaryGeneratorAction.cc.o -c /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/PrimaryGeneratorAction.cc

CMakeFiles/exampleB2b.dir/src/PrimaryGeneratorAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB2b.dir/src/PrimaryGeneratorAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/PrimaryGeneratorAction.cc > CMakeFiles/exampleB2b.dir/src/PrimaryGeneratorAction.cc.i

CMakeFiles/exampleB2b.dir/src/PrimaryGeneratorAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB2b.dir/src/PrimaryGeneratorAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/PrimaryGeneratorAction.cc -o CMakeFiles/exampleB2b.dir/src/PrimaryGeneratorAction.cc.s

CMakeFiles/exampleB2b.dir/src/RunAction.cc.o: CMakeFiles/exampleB2b.dir/flags.make
CMakeFiles/exampleB2b.dir/src/RunAction.cc.o: ../src/RunAction.cc
CMakeFiles/exampleB2b.dir/src/RunAction.cc.o: CMakeFiles/exampleB2b.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/exampleB2b.dir/src/RunAction.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exampleB2b.dir/src/RunAction.cc.o -MF CMakeFiles/exampleB2b.dir/src/RunAction.cc.o.d -o CMakeFiles/exampleB2b.dir/src/RunAction.cc.o -c /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/RunAction.cc

CMakeFiles/exampleB2b.dir/src/RunAction.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB2b.dir/src/RunAction.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/RunAction.cc > CMakeFiles/exampleB2b.dir/src/RunAction.cc.i

CMakeFiles/exampleB2b.dir/src/RunAction.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB2b.dir/src/RunAction.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/RunAction.cc -o CMakeFiles/exampleB2b.dir/src/RunAction.cc.s

CMakeFiles/exampleB2b.dir/src/TrackerHit.cc.o: CMakeFiles/exampleB2b.dir/flags.make
CMakeFiles/exampleB2b.dir/src/TrackerHit.cc.o: ../src/TrackerHit.cc
CMakeFiles/exampleB2b.dir/src/TrackerHit.cc.o: CMakeFiles/exampleB2b.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/exampleB2b.dir/src/TrackerHit.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exampleB2b.dir/src/TrackerHit.cc.o -MF CMakeFiles/exampleB2b.dir/src/TrackerHit.cc.o.d -o CMakeFiles/exampleB2b.dir/src/TrackerHit.cc.o -c /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/TrackerHit.cc

CMakeFiles/exampleB2b.dir/src/TrackerHit.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB2b.dir/src/TrackerHit.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/TrackerHit.cc > CMakeFiles/exampleB2b.dir/src/TrackerHit.cc.i

CMakeFiles/exampleB2b.dir/src/TrackerHit.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB2b.dir/src/TrackerHit.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/TrackerHit.cc -o CMakeFiles/exampleB2b.dir/src/TrackerHit.cc.s

CMakeFiles/exampleB2b.dir/src/TrackerSD.cc.o: CMakeFiles/exampleB2b.dir/flags.make
CMakeFiles/exampleB2b.dir/src/TrackerSD.cc.o: ../src/TrackerSD.cc
CMakeFiles/exampleB2b.dir/src/TrackerSD.cc.o: CMakeFiles/exampleB2b.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/exampleB2b.dir/src/TrackerSD.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/exampleB2b.dir/src/TrackerSD.cc.o -MF CMakeFiles/exampleB2b.dir/src/TrackerSD.cc.o.d -o CMakeFiles/exampleB2b.dir/src/TrackerSD.cc.o -c /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/TrackerSD.cc

CMakeFiles/exampleB2b.dir/src/TrackerSD.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/exampleB2b.dir/src/TrackerSD.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/TrackerSD.cc > CMakeFiles/exampleB2b.dir/src/TrackerSD.cc.i

CMakeFiles/exampleB2b.dir/src/TrackerSD.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/exampleB2b.dir/src/TrackerSD.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vgate/Geant4_Example/examples/basic/B2/ProCom/src/TrackerSD.cc -o CMakeFiles/exampleB2b.dir/src/TrackerSD.cc.s

# Object files for target exampleB2b
exampleB2b_OBJECTS = \
"CMakeFiles/exampleB2b.dir/exampleB2b.cc.o" \
"CMakeFiles/exampleB2b.dir/src/ActionInitialization.cc.o" \
"CMakeFiles/exampleB2b.dir/src/ChamberParameterisation.cc.o" \
"CMakeFiles/exampleB2b.dir/src/DetectorConstruction.cc.o" \
"CMakeFiles/exampleB2b.dir/src/DetectorMessenger.cc.o" \
"CMakeFiles/exampleB2b.dir/src/EventAction.cc.o" \
"CMakeFiles/exampleB2b.dir/src/PrimaryGeneratorAction.cc.o" \
"CMakeFiles/exampleB2b.dir/src/RunAction.cc.o" \
"CMakeFiles/exampleB2b.dir/src/TrackerHit.cc.o" \
"CMakeFiles/exampleB2b.dir/src/TrackerSD.cc.o"

# External object files for target exampleB2b
exampleB2b_EXTERNAL_OBJECTS =

exampleB2b: CMakeFiles/exampleB2b.dir/exampleB2b.cc.o
exampleB2b: CMakeFiles/exampleB2b.dir/src/ActionInitialization.cc.o
exampleB2b: CMakeFiles/exampleB2b.dir/src/ChamberParameterisation.cc.o
exampleB2b: CMakeFiles/exampleB2b.dir/src/DetectorConstruction.cc.o
exampleB2b: CMakeFiles/exampleB2b.dir/src/DetectorMessenger.cc.o
exampleB2b: CMakeFiles/exampleB2b.dir/src/EventAction.cc.o
exampleB2b: CMakeFiles/exampleB2b.dir/src/PrimaryGeneratorAction.cc.o
exampleB2b: CMakeFiles/exampleB2b.dir/src/RunAction.cc.o
exampleB2b: CMakeFiles/exampleB2b.dir/src/TrackerHit.cc.o
exampleB2b: CMakeFiles/exampleB2b.dir/src/TrackerSD.cc.o
exampleB2b: CMakeFiles/exampleB2b.dir/build.make
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4Tree.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4FR.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4GMocren.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4visHepRep.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4RayTracer.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4VRML.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4ToolsSG.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4OpenGL.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4vis_management.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4modeling.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4interfaces.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4persistency.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4error_propagation.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4readout.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4physicslists.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4run.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4event.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4tracking.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4parmodels.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4processes.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4digits_hits.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4track.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4particles.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4geometry.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4materials.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4graphics_reps.so
exampleB2b: /usr/lib/x86_64-linux-gnu/libGL.so
exampleB2b: /usr/lib/x86_64-linux-gnu/libQt5OpenGL.so.5.15.3
exampleB2b: /usr/lib/x86_64-linux-gnu/libQt5PrintSupport.so.5.15.3
exampleB2b: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.15.3
exampleB2b: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.15.3
exampleB2b: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
exampleB2b: /usr/lib/x86_64-linux-gnu/libXmu.so
exampleB2b: /usr/lib/x86_64-linux-gnu/libXext.so
exampleB2b: /usr/lib/x86_64-linux-gnu/libXt.so
exampleB2b: /usr/lib/x86_64-linux-gnu/libICE.so
exampleB2b: /usr/lib/x86_64-linux-gnu/libSM.so
exampleB2b: /usr/lib/x86_64-linux-gnu/libX11.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4analysis.so
exampleB2b: /usr/lib/x86_64-linux-gnu/libexpat.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4zlib.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4intercoms.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4global.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4clhep.so
exampleB2b: /home/vgate/Software/Geant4/install/lib/libG4ptl.so.2.3.3
exampleB2b: CMakeFiles/exampleB2b.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable exampleB2b"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/exampleB2b.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/exampleB2b.dir/build: exampleB2b
.PHONY : CMakeFiles/exampleB2b.dir/build

CMakeFiles/exampleB2b.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/exampleB2b.dir/cmake_clean.cmake
.PHONY : CMakeFiles/exampleB2b.dir/clean

CMakeFiles/exampleB2b.dir/depend:
	cd /home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vgate/Geant4_Example/examples/basic/B2/ProCom /home/vgate/Geant4_Example/examples/basic/B2/ProCom /home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build /home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build /home/vgate/Geant4_Example/examples/basic/B2/ProCom/procom_build/CMakeFiles/exampleB2b.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/exampleB2b.dir/depend

