## Practica Nº2 Algoritmia Básica

### Fuentes
En los fuentes de la práctica se incluyen 3 tipos de archivos según su función.
Por un lado se encuentras los fuentes del algoritmo, los cuales son los fuentes
que generan el algoritmo. Por otro lado se encuentran los fuentes de las pruebas,
los cuales son los fuentes que generan los programas que realizan la generación
de pruebas y la corrección de la salida del algoritmo. Por último se encuentran
los scripts.

A continuación se detalla a que conjunto pertenece cada uno de los ficheros:
Fuentes algoritmo:
- algoritmo_criterio_1.cpp
- algoritmo_criterio_2.cpp
- algoritmo_criterio_3.cpp
- variables_globales.h

Fuentes pruebas:
- generador_vectores.cpp
- comprobar_vectores.cpp

Scripts:
- CMakeLists.txt
- lanza_algoritmos.sh
- compila.sh


### Compilación
Para compilar el fichero se ha de ejecutar el script compila.sh que se
incluye con los fuentes del proyecto en una terminal bash.
Para ejecutarlo en esta terminal se puede usar el comando source compila.sh.
La compilación se ha realizado en hendrix con versión de gcc 5.2.0.


### Pruebas
Para generar las pruebas hemos utilizado un programa creado por nosotros. Dicho
programa se puede ejecutar una vez compilados los fuentes mediante las instrucciones
de compilación. Para hacerlo se ha de ejecutar el script lanza_algoritmos.sh desde
una terminal bash. Este script posee dentro de él declarada una variable llamada
NUMERO_DE_PRUEBAS, que indica el número de pruebas a generar. Cada una de estas
pruebas genera un vector aleatorio de tamaño VECTOR_SIZE (variable también definida
dentro del script) sobre el que se ejecutan los algoritmos de los
3 criterios y se comprueba si se ejecutan correctamente.
En caso de que la ejecución de todos los algoritmos se haya realizado de forma
correcta, mostrará el coste medio de cada uno en nanosegundos, en caso contrario
mostrará un mensaje de error.