cmake_minimum_required(VERSION 3.10)
project(Assignment1)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_CFLAGS "-static")

add_executable(EDIT src/main.cpp src/LinkedList.cpp src/LinkedList.h src/LineEditor.cpp src/LineEditor.h)
