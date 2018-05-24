//
// Created by abel on 1/04/18.
//

#ifndef ALGORITMIABASICA1_FRONTERA_H
#define ALGORITMIABASICA1_FRONTERA_H

#include "Nodo.h"
#include <utility>
#include <queue>
#include <list>

using namespace std;

// El primer elemento identifica el nodo que realiza la infección, el segundo el infectado, y el tercero el timestamp
typedef tuple<Nodo*, Nodo*, timestamp> elemento_frontera;

class Frontera {
    priority_queue<elemento_frontera> frontera;
public:

    void add(list<pair<Nodo*, timestamp >> &connections, Nodo* productor);

    elemento_frontera getLowest() const;

    void deleteLowest();

    bool isEmpty();
};

#endif //ALGORITMIABASICA1_FRONTERA_H
