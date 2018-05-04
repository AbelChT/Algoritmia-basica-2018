cmake_minimum_required(VERSION 3.10)
project(Practica2AlgoritmiaBasica)

set(CMAKE_CXX_STANDARD 11)

add_executable(GeneredorVectores generador_vectores.cpp variables_globales.h)

add_executable(Quicksort algoritmo_criterio_1.cpp variables_globales.h)

add_executable(TestVectores comprobar_vectores.cpp variables_globales.h)