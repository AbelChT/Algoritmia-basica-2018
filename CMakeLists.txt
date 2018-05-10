cmake_minimum_required(VERSION 3.6)
project(Algoritmia_Basica)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Algoritmo.cpp
        Algoritmo.h
        Frontera.cpp
        Frontera.h
        main.cpp
        Nodo.cpp
        Nodo.h Generador.cpp Generador.h)

add_executable(Algoritmia_Basica ${SOURCE_FILES})