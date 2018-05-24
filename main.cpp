#include <iostream>
#include <map>
#include <fstream>
#include "Nodo.h"
#include "algoritmo.h"
#include "variables_globales.h"

using namespace std;

int nodo_inicial, nodo_final, timestamp_inicial, timestamp_final;
map<int, Nodo *> sistema;

void cargarDatos(const string &path) {
    // Formato de entrada :
    // En la primera linea va la query. Formato query = ( nodo inicial, timestamp inicial, nodo final, timestamp final)
    // A partir de ahi:
    // Linea por traza ordenada ordenadas por timestamp. Formato traza = (primer nodo, segundo nodo, timestamp)
    //
    // Ejemplo:
    // 1 5 2 7 // Nodo inicial = 1, Timestamp inicial = 5, Nodo final = 2, Timestamp final = 7
    // 1 3 4 // El nodo 1 se comunica con el nodo 3 en el instante 4
    // 1 5 2 // El nodo 1 se comunica con el nodo 5 en el instante 2
    // 5 2 8 // El nodo 5 se comunica con el nodo 2 en el instante 8

    ifstream myfile;
    myfile.open(path);

    // Carga del fichero en a estructura de datos interna
    if (myfile.is_open()) {
        myfile >> nodo_inicial >> timestamp_inicial >> nodo_final >> timestamp_final;

        while (!myfile.eof()) {
            int nodo_1, nodo_2, timestamp_comunicacion;
            myfile >> nodo_1 >> nodo_2 >> timestamp_comunicacion;
            // Coste log n en el número de nodos
            if (sistema.find(nodo_1) == sistema.end())
                sistema.insert(pair<int, Nodo *>(nodo_1, new Nodo(nodo_1)));

            if (sistema.find(nodo_2) == sistema.end())
                sistema.insert(pair<int, Nodo *>(nodo_2, new Nodo(nodo_2)));

            auto nodo_1n = sistema.find(nodo_1)->second;
            auto nodo_2n = sistema.find(nodo_2)->second;

            nodo_1n->setConnection(pair<Nodo *, timestamp>(nodo_2n, timestamp_comunicacion));
            nodo_2n->setConnection(pair<Nodo *, timestamp>(nodo_1n, timestamp_comunicacion));
        }
    }
    myfile.close();
}

void guardarSolucion(const string &path, bool solucion) {
    ofstream myfile;
    myfile.open(path);
    if (myfile.is_open()) {
        myfile << solucion;
    }
    myfile.close();
}

void dibujaTraza(list<pair<int,timestamp >> &traza){
    cout.width(10);
    cout << "Nodo" << flush;
    cout.width(10);
    cout << "Timestamp" << endl;

    for (auto i :traza) {
        cout.width(10);
        cout << i.first;
        cout.width(10);
        cout << i.second;
        cout << endl;
    }
    cout.width(10);
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        cout << "Calgando datos" << endl;
        // Carga de datos estructura interna 
        // Coste: Aristas * log(número de nodos)
        cargarDatos(argv[1]);
        Frontera frontera;

        cout << "Ejecutando algoritmo" << endl;
        clock_t tStart = clock();

        // Ejecución algoritmo
        // Coste: Lineal en el número de aristas
        bool resultado = resolveQuery(sistema.find(nodo_inicial)->second, sistema.find(nodo_final)->second, frontera,
                                      timestamp_inicial, timestamp_final);
        clock_t tFinal = clock();

        printf("Tiempo de ejecución algoritmo: %.2fs\n", (double) (tFinal - tStart) / CLOCKS_PER_SEC);

        cout << "Guardando resultado" << endl;
        guardarSolucion(argv[2], resultado);

        if (resultado) {
            cout << "Si se ha infectado el nodo" << endl;
            cout << "Traza de infección: " << endl;
            auto actualex = sistema.find(nodo_final)->second;
            auto nodo_inicial_traza = sistema.find(nodo_inicial)->second;
            list<pair<int,timestamp >> traza;
            while (actualex!= nodo_inicial_traza){
                traza.push_front(make_pair(actualex->getID(),actualex->getInfectionTimestamp()));
                actualex = actualex->getInfectorNode();
            }
            traza.push_front(make_pair(nodo_inicial, timestamp_inicial));
            dibujaTraza(traza);

        } else {
            cout << "No se ha infectado el nodo" << endl;
        }
        return 0;
    } else {
        cout
                << "Error: Ha de especificar  el nombre del fichero con el sistema de nodos como primer parámetro y el nombre que tomará el fichero de resultados generado como segundo parámetro"
                << endl;
        return 1;
    }
}
