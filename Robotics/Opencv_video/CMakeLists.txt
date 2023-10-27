# minima versio de cmake
cmake_minimum_required(VERSION 3.0)
# nombre de mi proyecto
project(Opencv_video)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})    # Variables de entorno

# para generar el binario
# add_executable(<nombre de mi ejecutable>
#                < codigo fuente ...>()
add_executable(filters src/main.cpp)

# Indicar donde encontrar todo el codigo fuente de la libreria
target_link_libraries(filters ${OpenCV_LIBS})