//
// Created by Abel Chils Trabanco (NIA: 718997) and Jorge Aznar López (NIA: 721556)
//

#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <ctime>
#include <chrono>
#include "variables_globales.h"
#include <cstdint>

using namespace std;
using namespace std::chrono;


class CurrentTime {
    std::chrono::high_resolution_clock m_clock;

public:
    uint64_t milliseconds();

    uint64_t microseconds();

    uint64_t nanoseconds();
};

uint64_t CurrentTime::milliseconds() {
    return (uint64_t) std::chrono::duration_cast<std::chrono::milliseconds>
                (m_clock.now().time_since_epoch()).count();
}

uint64_t CurrentTime::microseconds() {
    return (uint64_t) std::chrono::duration_cast<std::chrono::microseconds>
                (m_clock.now().time_since_epoch()).count();
}

uint64_t CurrentTime::nanoseconds() {
    return (uint64_t) std::chrono::duration_cast<std::chrono::nanoseconds>
                (m_clock.now().time_since_epoch()).count();
}

/*
 * Funcion que intercambia los valores de dos elementos
 */
void my_swap(int &x, int &y) {
    auto aux = x;
    x = y;
    y = aux;
}

/*
 * Funcion que devuelve un entero aleatorio acotado
 */
int obtainRandom(int min, int max) {
    return min + (rand() % (max - min + 1));
}

/*
 * Selecciona un elemento como pivote y coloca los elementos menores a este a
 * su izquierda y los mayores a su derecha
 */
int divide(vector<int> &ordenar, int izquierda, int derecha) {
    // Criterio 3: Se seleciona como pivote un elemento aleatorio del vector
    auto p = ordenar[obtainRandom(izquierda, derecha)];
    auto k = izquierda;
    auto me = derecha;

    // Buscamos tanto el primer elemento mayor o igual que el pivote desde la izquierda
    // como el que es menor o igual desde la derecha
    while (ordenar[k] < p) { ++k; } ;
    while (ordenar[me] > p) { --me; } ;

    // Los intercambiamos y realizamos el mismo proceso hasta tener a la izquierda
    // los elementos menores que el pivote y a su derecha los que son mayores
    while (k < me) {
        my_swap(ordenar[k], ordenar[me]);
        while (ordenar[k] < p) { ++k; } ;
        while (ordenar[me] > p) { --me; } ;
    }
    return me;
}

/*
 * Ordena mediante el método quicksort el vector @ordenar entre los índices
 * @izquierda y @derecha
 */
void quicksort(vector<int> &ordenar, int izquierda, int derecha) {
    auto diferencia = derecha - izquierda;

    // Si solo hay 2 elementos, comprobamos sus valores y los ordenamos
    if (diferencia == 1) {
        if (ordenar[izquierda] > ordenar[derecha]) {
            my_swap(ordenar[izquierda], ordenar[derecha]);
        }
    }else if (diferencia > 1) {
      // En otro caso se selecciona un elemento como pivote y se coloca los elementos
      // menores a este a su izquierda y los mayores a su derecha. Una vez hecho esto
      // se ordenan primero los elementos que hay a su izquierda y luego los elementos
      // que hay a su derecha
        auto med = divide(ordenar, izquierda, derecha);
        quicksort(ordenar, izquierda, med - 1);
        quicksort(ordenar, med + 1, derecha);
    }
}

int main() {
    // Se lee el vector del fichero de entrada
    ifstream myfile_input(input_path);
    istream_iterator<int> start(myfile_input), end;
    vector<int> random_vector(start, end);

    CurrentTime current_time;

    // Instante de inicio
    uint64_t t1 = current_time.nanoseconds();

    quicksort(random_vector, 0, random_vector.size() - 1);

    // Instante de finalizacion
    uint64_t t2 = current_time.nanoseconds();


    cout << "Coste tiempo en nanosegundos = " << (t2 - t1) << endl;

    // Se guarda el vector ordenado en un fichero
    ofstream myfile_output(output_path);
    ostream_iterator<int> output_iterator(myfile_output, " ");
    copy(random_vector.begin(), random_vector.end(), output_iterator);
    return 0;
}
