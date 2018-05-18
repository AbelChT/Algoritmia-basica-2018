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

int obtainRandom(int min, int max) {
    return min + (rand() % (max - min + 1));
}

int divide(vector<int> &ordenar, int izquierda, int derecha) {
    auto p = ordenar[obtainRandom(izquierda, derecha)];
    auto k = izquierda;
    auto me = derecha;
    while (ordenar[k] < p) { ++k; };
    while (ordenar[me] > p) { --me; };
    while (k < me) {
        my_swap(ordenar[k], ordenar[me]);
        while (ordenar[k] < p) { ++k; };
        while (ordenar[me] > p) { --me; };
    }
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
    srand(time(NULL));

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