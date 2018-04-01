//
// Created by abel on 12/03/18.
//

#include "Algoritmo.h"

using namespace std;

bool resolveQuery(Nodo *nodo_inicio, Nodo *nodo_fin, Frontera &frontera, timestamp timestamp_inicio,
                  timestamp timestamp_fin) {
    nodo_inicio->setExplored();
    if (nodo_inicio == nodo_fin)
        return true;
    else {
        auto conexiones = nodo_inicio->getConnections(timestamp_inicio, timestamp_fin);
        frontera.add(conexiones);
        while (!frontera.isEmpty() && frontera.getLowest().first->isExplored()) {
            frontera.deleteLowest();
        }
        if (frontera.isEmpty()) return false;
        else {
            auto lowest = frontera.getLowest();
            frontera.deleteLowest();
            return resolveQuery(lowest.first, nodo_fin, frontera, lowest.second, timestamp_fin);
        }
    }
};