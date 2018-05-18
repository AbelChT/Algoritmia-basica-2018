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

int medianaInsertionSort(vector<int> ordenar) {
    auto izq = 0;
    auto der = ordenar.size() - 1;
    auto i = izq + 1;
    auto x = 0;
    while (i <= der) {
        x = ordenar[i];
        auto j = i - 1;
        while (j >= izq && ordenar[j] > x) {
            ordenar[j + 1] = ordenar[j];
            j--;
        }
        ordenar[j + 1] = x;
        i++;
    }

    if (ordenar.size() % 2 == 0) return ordenar[(ordenar.size() / 2) - 1];
    else return ordenar[ordenar.size() / 2];
}

/*
 * Devuelve el elemento que ocuparía la posición posición si ordenar estuviera ordenado
 */
int select(vector<int> entrada, int posicion) {

    const auto P = 5;
    int mediana;
    auto numeroGrupos = entrada.size() / P;
    auto restantes = entrada.size() % P;

    if (entrada.size() == 1) {
        return entrada[0];
    }

    if (restantes > 0) {
        numeroGrupos++;
    }

    vector<int> medianas;

    for (int i = 0; i < numeroGrupos; i++) {
        if (i != numeroGrupos - 1 || restantes == 0) {
            vector<int>(entrada.begin() + i * P, entrada.begin() + (i * P) + P);
            medianas.push_back(
                    medianaInsertionSort(vector<int>(entrada.begin() + i * P, entrada.begin() + (i * P) + P)));
        } else {
            medianas.push_back(
                    medianaInsertionSort(vector<int>(entrada.begin() + i * P, entrada.begin() + (i * P) + restantes)));
        }
    }

    if (medianas.size() <= 5) {
        mediana = medianaInsertionSort(medianas);
    } else {
        mediana = select(medianas, medianas.size() / 2);
    }

    vector<int> low;
    vector<int> high;

    for (auto j: entrada) {
        if (j < mediana) {
            low.push_back(j);
        } else if (j > mediana) {
            high.push_back(j);
        }
    }

    int k = low.size();

    if (k == posicion) {
        return mediana;
    } else if (k > posicion) {
        return select(low, posicion);
    } else {
        return select(high, posicion - k - 1);
    }
}


int divide(vector<int> &ordenar, int izquierda, int derecha) {
    int p;
    auto vector_pasar = vector<int>(ordenar.begin() + izquierda, ordenar.begin() + derecha + 1);
    if (vector_pasar.size() % 2 == 0) p = select(vector_pasar, (vector_pasar.size() / 2) - 1);
    else p = select(vector_pasar, vector_pasar.size() / 2);

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