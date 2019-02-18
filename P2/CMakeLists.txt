cmake_minimum_required(VERSION 3.4.3)
project(Practica2AlgoritmiaBasica)

set(CMAKE_CXX_STANDARD 11)

add_executable(GeneradorVectores generador_vectores.cpp variables_globales.h)

add_executable(Quicksort algoritmo_criterio_1.cpp variables_globales.h)

add_executable(Quicksort_2 algoritmo_criterio_2.cpp variables_globales.h)

add_executable(Quicksort_3 algoritmo_criterio_3.cpp variables_globales.h)

add_executable(TestVectores comprobar_vectores.cpp variables_globales.h)
