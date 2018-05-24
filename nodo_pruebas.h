//
// Created by abel on 11/05/18.
//

#ifndef ALGORITMIABASICA1_NODO_PRUEBAS_H
#define ALGORITMIABASICA1_NODO_PRUEBAS_H

#include <utility>
#include <list>

typedef int timestamp;

using namespace std;

class nodo_pruebas {
private:
    unsigned int id;
    bool is_infected = false;
    int timestamp_of_infection = -1;

public:
    nodo_pruebas(unsigned int id);

    void setInfected();

    bool isInfected();

    int getTimestampOfInfection();

    void setTimestampOfInfection(int);

    friend bool operator==(const nodo_pruebas &l, const nodo_pruebas &r);

};

#endif //ALGORITMIABASICA1_NODO_PRUEBAS_H
