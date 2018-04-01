//
// Created by abel on 1/04/18.
//

#include "Frontera.h"

using namespace std;

bool operator<(const pair<Nodo *, timestamp> &l, const pair<Nodo *, timestamp> &r) {
    return l.second < r.second;
}

void Frontera::add(list<pair<Nodo *, timestamp>> &connections) {
    for (auto i : connections) {
        frontera.push(i);
    }
}

pair<Nodo *, timestamp> Frontera::getLowest() const {
    return frontera.top();
}

void Frontera::deleteLowest() {
    frontera.pop();
}

bool Frontera::isEmpty() {
    return frontera.empty();
}

