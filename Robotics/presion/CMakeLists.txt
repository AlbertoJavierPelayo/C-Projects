cmake_minimum_required(VERSION 3.0)
project(presion)

include_directories(include)

add_executable(
    presion_exe #binario
    src/main.cpp
    src/presion.cpp
)