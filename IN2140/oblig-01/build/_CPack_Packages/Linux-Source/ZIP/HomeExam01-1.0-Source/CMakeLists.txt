cmake_minimum_required(VERSION 3.14)

#
# This tells CMake that your project's name is homeexam-01, and that the programs
# here are written in C.
#
project(HomeExam01
	VERSION 1.0
	DESCRIPTION "CMake configuration file for the first home exam IN2140 v26"
        LANGUAGES C)

#
# This tells CMake that the compilation should use the version of the C standard
# from 2011.
# This has no effect on Windows.
#
set(CMAKE_C_STANDARD 11)

#
# This tells CMake to create compilation rules that add debug information. When
# your program is built successfully, you will be able to search for bugs with
# gdb and valgrind. The build type Release would make a program that cannot be
# debugged with these tools.
#
set(CMAKE_BUILD_TYPE Debug)

#
# This tells CMake to create rules for making an executable program named homeexam-01
# from the source files tests.c the_apple.c and the_apple.h
#
add_executable(vowelshift
               vowelshift-main.c
	       vowelshift-todo.c vowelshift-todo.h)

add_executable(stringops
               stringops-main.c
	       stringops-todo.c stringops-todo.h)

add_executable(apple
               apple-main.c
	       apple-todo.c apple-todo.h
	       the_apple.c the_apple.h)

#
# This creates a make rule that helps you create your delivery.
# You call it with "make package_source"
# This will generate the archive file HomeExam01-1.0-Source.zip,
# which you deliver.
#
set(CPACK_SOURCE_GENERATOR "ZIP")
set(CPACK_SOURCE_IGNORE_FILES
	/\.git/
	/build/
	".*Makefile"
	/CMakeFiles/
	".*CMakeCache.txt"
	".*CPack.*"
	".*cmake"
	".*.zip"
	".*~$" )
include(CPack)
