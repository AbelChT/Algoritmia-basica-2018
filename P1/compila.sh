#!/bin/bash
# Autores: Abel Chils Trabanco (NIA:718997) y Jorge Aznar López (NIA:721556)
# Descripción: Compila los ficheros necesarios
cmake . -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release
make
