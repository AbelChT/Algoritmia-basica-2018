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

uint64_t CurrentTime::milliseconds()
{
    return (uint64_t) std::chrono::duration_cast<std::chrono::milliseconds>
                (m_clock.now().time_since_epoch()).count();
}

uint64_t CurrentTime::microseconds()
{
    return (uint64_t) std::chrono::duration_cast<std::chrono::microseconds>
                (m_clock.now().time_since_epoch()).count();
}

uint64_t CurrentTime::nanoseconds()
{
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
 * Funcion que ordena el vector del cual se devuelve la mediana
 */
int medianaInsertionSort(vector<int> ordenar) {
    auto izq = 0;
    auto der = ordenar.size() - 1;
    auto i = izq + 1;
    auto x = 0;
    // Proceso de ordenacion mediante el metodo de inserción del primero
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

    // Si es par devolvemos el elemento medio de menor índice por conveniencia
    if (ordenar.size() % 2 == 0) return ordenar[(ordenar.size() / 2) - 1];
    else return ordenar[ordenar.size() / 2];
}

/*
 * Devuelve el elemento que ocuparía la posición 'posicion' si @entrada estuviera ordenado
 */
int select(vector<int> entrada, int posicion) {

    // Tamaño de las subdivisiones del vector a ordenar
    const auto P = 5;
    int mediana;
    auto numeroGrupos = entrada.size() / P;
    auto restantes = entrada.size() % P;

    if (entrada.size() == 1) {
        return entrada[0];
    }

    // Si tras dividir entre 5 el vector, sobran elementos se crea otra subdivision con ellos
    if (restantes > 0) {
        numeroGrupos++;
    }

    vector<int> medianas;

    // Iteramos en las subdiviones del vector: entrada[0-4], entrada[5-9], etc.
    // y las ordenamos mediante el algoritmo 'insertion sort'
    for (int i = 0; i < numeroGrupos; i++) {
        if (i != numeroGrupos - 1 || restantes == 0) {
            vector<int>(entrada.begin() + i * P, entrada.begin() + (i * P) + P);
            medianas.push_back(
                    medianaInsertionSort(vector<int>(entrada.begin() + i * P, entrada.begin() + (i * P) + P)));
        } else {
            // Caso especial para el grupo, si existiese, de menos de 5 elementos
            medianas.push_back(
                    medianaInsertionSort(vector<int>(entrada.begin() + i * P, entrada.begin() + (i * P) + restantes)));
        }
    }

    // En caso de no tener 5 o menos medianas, realizamos llamas recursivas a la propia funcion
    if (medianas.size() <= 5) {
        mediana = medianaInsertionSort(medianas);
    } else {
        mediana = select(medianas, medianas.size() / 2);
    }

    // Una vez obtenido un vector de 5 o menos medianas, lo separamos segun la mediana devuelta por el algoritmo
    // 'insertion sort' en un vector con valores inferiores y otro con valores superiores
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

    // Realizamos llamadas recursivas hasta obtener la mediana del vector original
    if (k == posicion) {
        return mediana;
    } else if (k > posicion) {
        return select(low, posicion);
    } else {
        return select(high, posicion - k - 1);
    }
}

/*
 * Selecciona un elemento como pivote y coloca los elementos menores a este a
 * su izquierda y los mayores a su derecha
 */
int divide(vector<int> &ordenar, int izquierda, int derecha) {
    // Criterio 2: Seleccionamos como pivote la mediana
    int p;
    auto vector_pasar = vector<int>(ordenar.begin() + izquierda, ordenar.begin() + derecha + 1);
    if (vector_pasar.size() % 2 == 0) p = select(vector_pasar, (vector_pasar.size() / 2) - 1);
    else p = select(vector_pasar, vector_pasar.size() / 2);

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

    // Si solo hay 2 elementos se realiza una ordenación por inserción
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
