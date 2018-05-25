//
// Created by Abel Chils Trabanco (NIA: 718997) and Jorge Aznar López (NIA: 721556) on 12/03/18.
//

#ifndef ALGORITMIABASICA1_NODO_H
#define ALGORITMIABASICA1_NODO_H

#include <utility>
#include <list>

typedef int timestamp;

using namespace std;

class Nodo {
private:
    int id;
    bool explored = false;
    list<pair<Nodo *, timestamp>> connections;

    // En caso de que el nodo haya sido infectado, contiene el nodo que le infectó
    Nodo * infector_node = nullptr;
    timestamp infection_timestamp = 0;

public:
    Nodo(int id);

    list<pair<Nodo *, timestamp>> getConnections(timestamp start, timestamp end);

    void setExplored();

    int getID();

    bool isExplored();

    void setConnection(pair<Nodo *, timestamp> connections);

    void setInfectorNode(Nodo * n);

    void setInfectionTimestamp(timestamp t);

    Nodo * getInfectorNode();

    timestamp getInfectionTimestamp();

    friend bool operator==(const Nodo &l, const Nodo &r);

};

#endif //ALGORITMIABASICA1_NODO_H
