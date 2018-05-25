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

void mostrarUnaPosibleTrazaInfeccion(vector<nodo_pruebas> &nodes);


bool funcionGeneradora() {
    default_random_engine generator(time(0));
    uniform_int_distribution<unsigned int> distribution_numNodes(MIN_NUM_OF_NODES, MAX_NUM_OF_NODES);
    numNodes = distribution_numNodes(generator);

    uniform_int_distribution<unsigned int> distribution_infectedNode(0, numNodes - 1);
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

    for (unsigned int i = 0; i < numNodes; i++) {
        nodes.emplace_back(nodo_pruebas(i));
    }

    nodes[infectedNode].setInfected();
    nodes[infectedNode].setTimestampOfInfection(initTimestamp);

    // Conexiones antes infección inicial
    for (unsigned int i = 1; i < initTimestamp; i++) {
        cout << "Calculando timestamp " << i << " de " << MAX_TIMESTAMP << endl;
        for (unsigned int j = 0; j < numNodes; j++) {
            for (unsigned int z = j + 1; z < numNodes; z++) {
                // Iteramos en todas las uniones entre dos nodos sin repetición
                auto actual_pair = make_pair(j, z);
                if (distribution(generator) && connection_pairs.find(actual_pair) == connection_pairs.end()) {
                    connections.emplace_back(make_tuple(j, z, i));
                    connection_pairs.insert(actual_pair);
                }
            }
        }
    }

    // Conexiones tras infección
    for (unsigned int i = initTimestamp; i <= finalTimestamp; i++) {
        cout << "Calculando timestamp " << i << " de " << MAX_TIMESTAMP << endl;
        bool has_been_new_infection = false;

        set<pair<unsigned int, unsigned int>> connection_pairs_actual_time_stamp;

        // Generar conexiones en este timestamp
        for (unsigned int j = 0; j < numNodes; j++) {
            for (unsigned int z = j + 1; z < numNodes; z++) {
                auto actual_pair = make_pair(j, z);
                if (distribution(generator) && connection_pairs.find(actual_pair) == connection_pairs.end()) {
                    connections.emplace_back(make_tuple(j, z, i));
                    connection_pairs.insert(actual_pair);
                    connection_pairs_actual_time_stamp.insert(actual_pair);

                    if (nodes[j].isInfected() && !nodes[z].isInfected()) {
                        // Momento en el que se infecta el nodo z
                        nodes[z].setInfected();
                        nodes[z].setTimestampOfInfection(i);
                        nodes[z].setInfectorId(j);
                        has_been_new_infection = true;
                    } else if (nodes[z].isInfected() && !nodes[j].isInfected()) {
                        // Momento en el que se infecta el nodo j
                        nodes[j].setInfected();
                        nodes[j].setTimestampOfInfection(i);
                        nodes[j].setInfectorId(z);
                        has_been_new_infection = true;
                    }


                }
            }
        }

        // Comprobar si algún nodo infectado en este timestamp puede propagar la infección
        while (has_been_new_infection) {
            has_been_new_infection = false;
            for (auto actual_connection_node : connection_pairs_actual_time_stamp) {
                if (nodes[actual_connection_node.first].isInfected() &&
                    !nodes[actual_connection_node.second].isInfected() &&
                    nodes[actual_connection_node.first].getTimestampOfInfection() == i) {
                    nodes[actual_connection_node.second].setInfected();
                    nodes[actual_connection_node.second].setTimestampOfInfection(i);
                    nodes[actual_connection_node.second].setInfectorId(actual_connection_node.first);
                    has_been_new_infection = true;
                } else if (nodes[actual_connection_node.second].isInfected() &&
                           !nodes[actual_connection_node.first].isInfected() &&
                           nodes[actual_connection_node.second].getTimestampOfInfection() == i) {
                    nodes[actual_connection_node.first].setInfected();
                    nodes[actual_connection_node.first].setTimestampOfInfection(i);
                    nodes[actual_connection_node.first].setInfectorId(actual_connection_node.second);
                    has_been_new_infection = true;
                }
            }
        }
    }

    // Conexiones despues de final timestamp
    for (unsigned int i = finalTimestamp; i <= MAX_TIMESTAMP; i++) {
        cout << "Calculando timestamp " << i << " de " << MAX_TIMESTAMP << endl;
        for (unsigned int j = 0; j < numNodes; j++) {
            for (unsigned int z = j + 1; z < numNodes; z++) {
                auto actual_pair = make_pair(j, z);
                if (distribution(generator) && connection_pairs.find(actual_pair) == connection_pairs.end()) {
                    connections.emplace_back(make_tuple(j, z, i));
                    connection_pairs.insert(actual_pair);
                }
            }
        }
    }

    mostrarUnaPosibleTrazaInfeccion(nodes);

    return nodes[finalNode].isInfected();
}

void guardarConexiones(const string &path) {
    ofstream salida;
    salida.open(path);
    if (salida.is_open()) {
        salida << infectedNode + 1 << " " << initTimestamp << " " << finalNode + 1 << " " << finalTimestamp << '\n';
        for (auto i : connections) {
            salida << get<0>(i) + 1 << " " << get<1>(i) + 1 << " " << get<2>(i) << '\n';
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

void mostrarUnaPosibleTrazaInfeccion(vector<nodo_pruebas> &nodes) {
    if (nodes[finalNode].isInfected()) {
        list<unsigned int> traza;

        unsigned int actual_infected = finalNode;
        traza.push_front(actual_infected);
        while (actual_infected != infectedNode) {
            actual_infected = nodes[actual_infected].getInfectorId();
            traza.push_front(actual_infected);
        }

        cout << "Posible traza de infección:" << endl;

        for (auto i :traza) {
            cout << i << " " << flush;
        }
        cout << endl;
    }
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

