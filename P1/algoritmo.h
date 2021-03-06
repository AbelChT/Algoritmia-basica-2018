//
// Created by Abel Chils Trabanco (NIA: 718997) and Jorge Aznar López (NIA: 721556) on 12/03/18.
//

#ifndef ALGORITMIABASICA1_ALGORITMO_H
#define ALGORITMIABASICA1_ALGORITMO_H

#include "Nodo.h"
#include "frontera.h"
#include <list>

using namespace std;

bool
resolveQuery(Nodo *nodo_inicio, Nodo *nodo_fin, Frontera &frontera, timestamp timestamp_inicio,
             timestamp timestamp_fin);

#endif //ALGORITMIABASICA1_ALGORITMO_H
