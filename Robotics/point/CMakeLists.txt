cmake_minimum_required(VERSION 3.0)
project(point)

include_directories(include)

add_executable(
    point_exe #binario
    src/main.cpp
    src/point.cpp
)