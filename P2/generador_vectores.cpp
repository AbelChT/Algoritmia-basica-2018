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

int main(int argc, char *argv[]) {
  if(argc == 2){
    //Seed generada
    auto seed = chrono::system_clock::now().time_since_epoch().count();

    //Engina generada a partir de la seed
    default_random_engine random_engine(seed);

    //Distribución entre los valores máximo y mínimo fijados por defecto
    uniform_int_distribution<int> distribution(INT_MIN, INT_MAX);

    // Declaración del vector que ordenaremos
    vector<int> random_vector(atoi(argv[1]));

    // Generación del vector que ordenaremos a partir de la distribución
    generate(random_vector.begin(), random_vector.end(), [&] { return distribution(random_engine); });

    // Guardamos el vector para poder visualizarlo en un fichero de nuestro sistema
    ofstream myfile(input_path);
    ostream_iterator<int> output_iterator(myfile, " ");
    copy(random_vector.begin(), random_vector.end(), output_iterator);
    return 0;
  } else{
    cout
            << "Error: Ha de especificar el tamaño del vector a generar"
            << endl;
    return 1;
  }
}
