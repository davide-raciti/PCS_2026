cmake_minimum_required(VERSION 3.20)
project(esercitazione6)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

# eseguibile principale
add_executable(grafi main.cpp)

# eseguibili per i test unitari
add_executable(test_graphs test_graphs.cpp)
add_test(NAME graphs COMMAND test_graphs)
enable_testing()