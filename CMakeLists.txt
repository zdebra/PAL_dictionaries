cmake_minimum_required(VERSION 3.6)
project(PAL6)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp FinalState.h LinkedList.cpp LinkedList.h Dictionary.h)
add_executable(PAL6 ${SOURCE_FILES})