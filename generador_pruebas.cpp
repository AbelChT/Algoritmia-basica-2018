//
// Created by Jorge on 02/05/2018.
//

#include "nodo_pruebas.h"
#include "variables_globales.h"
#include <ctime>
#include <set>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <random>

// Constantes
const unsigned int MAX_TIMESTAMP = 1000; // Número máximo de timestamps que pasarán, mientras más alto sea más costarán
// ejecutarse las pruebas
const unsigned int MIN_NUM_OF_NODES = 500; // Número mínimo de nodos del sistema
const unsigned int MAX_NUM_OF_NODES = 3000; // Máximo numero de nodos del sistema, mientras más alto sea más costarán
// ejecutarse las pruebas
const double PROBABILITY_OF_CONNECTION = 0.04; // Mientras más alta mas posibilidades de que dos nodos se conecten, por
// lo que más probabilidad de infección existe

// Solucion
unsigned int numNodes, infectedNode, initTimestamp, finalTimestamp, finalNode;
list<tuple<unsigned int, unsigned int, unsigned int>> connections;


bool funcionGeneradora() {
    default_random_engine generator(time(0));
    uniform_int_distribution<unsigned int> distribution_numNodes(MIN_NUM_OF_NODES, MAX_NUM_OF_NODES);
    numNodes = distribution_numNodes(generator);

    uniform_int_distribution<unsigned int> distribution_infectedNode(1, numNodes);
    uniform_int_distribution<unsigned int> distribution_initTimestamp(1, MAX_TIMESTAMP / 4);
    uniform_int_distribution<unsigned int> distribution_finalTimestamp((3 * MAX_TIMESTAMP) / 4, MAX_TIMESTAMP);
    bernoulli_distribution distribution(PROBABILITY_OF_CONNECTION);

    set<pair<unsigned int, unsigned int>> connection_pairs;

    infectedNode = distribution_infectedNode(generator);
    initTimestamp = distribution_initTimestamp(generator);
    finalTimestamp = distribution_finalTimestamp(generator);

    unsigned int auxFinalNode = distribution_infectedNode(generator);

    while (infectedNode == auxFinalNode) {
        auxFinalNode = distribution_infectedNode(generator);
    }

    finalNode = auxFinalNode;

    vector<nodo_pruebas> nodes;

    for (int i = 1; i <= numNodes; i++) {
        if (i != infectedNode) {
            nodes.emplace_back(nodo_pruebas(i));
        } else {
            auto insertar = nodo_pruebas(i);
            insertar.setInfected();
            insertar.setTimestampOfInfection(initTimestamp);
            nodes.emplace_back(insertar);
        }
    }

    for (int i = 1; i < MAX_TIMESTAMP; i++) {
        cout << "Calculando timestamp " << i << " de " << MAX_TIMESTAMP << endl;
        if (i < initTimestamp || i > finalTimestamp) {
            for (int j = 1; j <= numNodes; j++) {
                for (int z = j + 1; z <= numNodes; z++) {
                    auto actual_pair = make_pair<unsigned int, unsigned int>(j, z);
                    if (distribution(generator) && connection_pairs.find(actual_pair) == connection_pairs.end()) {
                        connections.emplace_back(make_tuple(j, z, i));
                        connection_pairs.insert(actual_pair);
                    }
                }
            }
        } else {
            bool has_been_new_infection = true;
            while (has_been_new_infection) {
                has_been_new_infection = false;
                for (int j = 1; j <= numNodes; j++) {
                    for (int z = j + 1; z <= numNodes; z++) {
                        auto actual_pair = make_pair<unsigned int, unsigned int>(j, z);
                        if (distribution(generator) && connection_pairs.find(actual_pair) == connection_pairs.end()) {
                            connections.emplace_back(make_tuple(j, z, i));
                            connection_pairs.insert(actual_pair);
                            if (nodes[j - 1].isInfected() && !nodes[z - 1].isInfected() &&
                                nodes[j - 1].getTimestampOfInfection() <= i) {
                                nodes[z - 1].setInfected();
                                nodes[z - 1].setTimestampOfInfection(i);
                                has_been_new_infection = true;
                            }

                            if (nodes[z - 1].isInfected() && !nodes[j - 1].isInfected() &&
                                nodes[z - 1].getTimestampOfInfection() <= i) {
                                nodes[j - 1].setInfected();
                                nodes[j - 1].setTimestampOfInfection(i);
                                has_been_new_infection = true;
                            }
                        }
                    }
                }
            }
        }
    }
    return nodes[finalNode - 1].isInfected();
}

void guardarConexiones(const string &path) {
    ofstream salida;
    salida.open(path);
    if (salida.is_open()) {
        salida << infectedNode << " " << initTimestamp << " " << finalNode << " " << finalTimestamp << '\n';
        for (auto i : connections) {
            salida << get<0>(i) << " " << get<1>(i) << " " << get<2>(i) << '\n';
        }
    }
    salida.close();
}

void guardarSolucion(const string &path, bool solucion) {
    ofstream myfile;
    myfile.open(path);
    if (myfile.is_open()) {
        myfile << solucion;
    }
    myfile.close();
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        auto resultado = funcionGeneradora();
        if (resultado) {
            cout << "Solución: El nodo ha resultado infectado" << endl;
        } else {
            cout << "Solución: El nodo no ha resultado infectado" << endl;
        }
        guardarConexiones(argv[1]);
        guardarSolucion(argv[2], resultado);
        return 0;
    } else {
        cout
                << "Error: Ha de especificar el nombre que tomará el fichero de pruebas generado como primer parámetro y el nombre del fichero con la solución correcta como segundo parámetro"
                << endl;
        return 1;
    }
}

