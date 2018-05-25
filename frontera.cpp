//
// Created by abel on 1/04/18.
//

#include <tuple>
#include "frontera.h"

using namespace std;

// Se necesita que tenga más prioridad el elemento con menos time stamp
bool operator<(const elemento_frontera &l, const elemento_frontera &r) {
    return get<2>(l) > get<2>(r);
}

void Frontera::add(list<pair<Nodo *, timestamp >> &connections, Nodo *productor) {
    for (auto i : connections) {
        frontera.push(make_tuple(productor, i.first, i.second));
    }
}

elemento_frontera Frontera::getLowest() const {
    return frontera.top();
}

void Frontera::deleteLowest() {
    frontera.pop();
}

bool Frontera::isEmpty() {
    return frontera.empty();
}

