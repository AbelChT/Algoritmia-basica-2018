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

class Frontera {
    priority_queue<pair<Nodo *, timestamp>> frontera;
public:
    void add(list<pair<Nodo *, timestamp>> &connections);

    pair<Nodo *, timestamp> getLowest() const;

    void deleteLowest();

    bool isEmpty();
};

#endif //ALGORITMIABASICA1_FRONTERA_H
