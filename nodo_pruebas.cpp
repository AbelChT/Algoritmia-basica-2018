//
// Created by abel on 11/05/18.
//

#include "nodo_pruebas.h"

nodo_pruebas::nodo_pruebas(unsigned int id) : id(id){}

void nodo_pruebas::setInfected() {
    is_infected = true;
}

bool nodo_pruebas::isInfected() {
    return is_infected;
}

int nodo_pruebas::getTimestampOfInfection(){
    return timestamp_of_infection;
}

void nodo_pruebas::setTimestampOfInfection(int x){
    timestamp_of_infection = x;
}

bool operator==(const nodo_pruebas &l, const nodo_pruebas &r) {
    return l.id == r.id;
}
