//
// Created by abel on 12/03/18.
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

public:
    Nodo(int id);

    list<pair<Nodo *, timestamp>> getConnections(timestamp start, timestamp end);

    void setExplored();

    bool isExplored();

    void setConnection(pair<Nodo *, timestamp> connections);

    friend bool operator==(const Nodo &l, const Nodo &r);

};

#endif //ALGORITMIABASICA1_NODO_H
