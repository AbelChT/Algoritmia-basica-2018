//
// Created by Abel Chils Trabanco (NIA: 718997) and Jorge Aznar López (NIA: 721556)
//

#include <random>
#include <chrono>
#include <algorithm>
#include <climits>
#include <fstream>
#include <iterator>
#include <iostream>
#include "variables_globales.h"

using namespace std;

int main() {
    // Comprobamos si el vector de salida esta ordenado correctamente
    ifstream myfile(output_path);
    istream_iterator<int> start(myfile), end;
    vector<int> random_vector(start, end);

    // Función de la clase vector que comprueba dados dos índices del vector
    // si está ordenado en ese intervalo
    if (is_sorted(random_vector.begin(), random_vector.end())) {
        cout << "Correcto" << std::endl;
        return 0;
    } else {
        cout << "Fallo" << std::endl;
        return 1;
    }
}
