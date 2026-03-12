cmake_minimum_required(VERSION 3.20)
project(es_1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(ese1 printargs.cpp)
add_executable(ese2 medie.cpp)