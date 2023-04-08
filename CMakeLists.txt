cmake_minimum_required(VERSION 3.20)
project(meta_programming)

set(CMAKE_CXX_STANDARD 23)

add_executable(meta_programming main.cpp my_allocator.cpp my_allocator.h)
