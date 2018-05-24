//
// Created by abel on 12/03/18.
//

#include "Nodo.h"

Nodo::Nodo(int id) : id(id) {}

// Devuelve los nodos conectados al nodo actual entre start y end
// Coste: Lineal en número de nodos conectados al nodo actual
list<pair<Nodo *, timestamp>> Nodo::getConnections(timestamp start, timestamp end) {
    list<pair<Nodo *, timestamp>> connections;
    for (auto i : this->connections)
        if (i.second >= start && i.second <= end) connections.emplace_back(i);

    return connections;
}

int Nodo::getID() {
    return id;
}

void Nodo::setExplored() {
    explored = true;
}

void Nodo::setInfectorNode(Nodo * n) {
    infector_node = n;
}

void Nodo::setInfectionTimestamp(timestamp t) {
    infection_timestamp = t;
}

bool Nodo::isExplored() {
    return explored;
}

void Nodo::setConnection(pair<Nodo *, timestamp> connection) {
    connections.emplace_back(connection);
}

bool operator==(const Nodo &l, const Nodo &r) {
    return l.id == r.id;
}

Nodo * Nodo::getInfectorNode(){
    return infector_node;
}

timestamp Nodo::getInfectionTimestamp(){
    return infection_timestamp;
}
