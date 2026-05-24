cmake_minimum_required(VERSION 3.20)
project(esercitazione8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

# trova la libreria Eigen3 nel sistema
find_package(Eigen3 REQUIRED)

enable_testing()

# definisce l'eseguibile principale "gcd"
add_executable(gcd main.cpp)

# collega Eigen a gcd
target_link_libraries(gcd PRIVATE Eigen3::Eigen)

# registra il test lanciando direttamente l'eseguibile gcd
add_test(NAME gctest COMMAND gcd)