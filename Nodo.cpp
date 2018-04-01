//
// Created by abel on 12/03/18.
//

#include "Nodo.h"

Nodo::Nodo(int id) : id(id){}

list<pair<Nodo *, timestamp>> Nodo::getConnections(timestamp start, timestamp end) {
    list<pair<Nodo *, timestamp>> connections;
    for (auto i : this->connections)
        if (i.second >= start && i.second <= end) connections.emplace_back(i);

    return connections;
}

void Nodo::setExplored() {
    explored = true;
}

bool Nodo::isExplored() {
    return explored;
}

void Nodo::setConnection(pair<Nodo *, timestamp> connection){
    connections.emplace_back(connection);
}

bool operator==(const Nodo &l, const Nodo &r) {
    return l.id == r.id;
}
