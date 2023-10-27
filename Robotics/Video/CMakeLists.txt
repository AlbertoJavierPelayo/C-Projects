cmake_minimum_required(VERSION 3.0)  #proteccion
project(Video)    #mismo nombre de la carpeta


#Incluir los directorios del proyecto
find_package(OpenCV REQUIRED)                     #Busca paquete

include_directories(${OpenCV_INCLUDE_DIRS})       #Inlcuye directorio

add_executable(filters src/main.cpp)             #Buscamos el codigo fuente

target_link_libraries(filters ${OpenCV_LIBS})    #Busca la libreria
