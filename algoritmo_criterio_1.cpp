#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <ctime>
#include "variables_globales.h"

using namespace std;

void my_swap(int &x, int &y) {
    auto aux = x;
    x = y;
    y = aux;
}

// Funciona mal
int divide(vector<int> &ordenar, int izquierda, int derecha) {
    auto p = ordenar[izquierda];
    auto k = izquierda;
    auto me = derecha + 1;
    do { ++k; } while (ordenar[k] <= p && k < derecha);
    do { --me; } while (ordenar[me] > p);
    while (k < me) {
        my_swap(ordenar[k], ordenar[me]);
        do { ++k; } while (ordenar[k] <= p);
        do { --me; } while (ordenar[me] > p);
    }
    my_swap(ordenar[izquierda], ordenar[me]);
    return me;
}

void quicksort(vector<int> &ordenar, int izquierda, int derecha) {
    auto diferencia = derecha - izquierda;
    if (diferencia == 1) {
        if (ordenar[izquierda] > ordenar[derecha]) {
            my_swap(ordenar[izquierda], ordenar[derecha]);
        }
    } else if (diferencia > 1) {
        auto med = divide(ordenar, izquierda, derecha);
        quicksort(ordenar, izquierda, med - 1);
        quicksort(ordenar, med + 1, derecha);
    }
}

int main() {
    ifstream myfile_input(input_path);
    istream_iterator<int> start(myfile_input), end;
    vector<int> random_vector(start, end);

    clock_t antes, despues;

    antes = clock();

    quicksort(random_vector, 0, VECTOR_SIZE - 1);

    despues = clock();

    cout << "Coste tiempo = " << despues - antes << endl;

    ofstream myfile_output(output_path);
    ostream_iterator<int> output_iterator(myfile_output, " ");
    copy(random_vector.begin(), random_vector.end(), output_iterator);
    return 0;
}