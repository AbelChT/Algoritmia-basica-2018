cmake_minimum_required(VERSION 3.4.3)
project(AlgoritmiaBasica1)

set(CMAKE_CXX_STANDARD 11)

add_executable(GeneradorPruebas generador_pruebas.cpp nodo_pruebas.h nodo_pruebas.cpp variables_globales.h)
add_executable(Algoritmo main.cpp algoritmo.cpp algoritmo.h Nodo.cpp Nodo.h frontera.cpp frontera.h variables_globales.h)
add_executable(ComprobadorSolucion comprobar_solucion.cpp variables_globales.h)
