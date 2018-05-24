//
// Created by abel on 12/03/18.
//

#include <tuple>
#include "algoritmo.h"

using namespace std;

/* Algoritmo */
bool resolveQuery(Nodo *nodo_inicio, Nodo *nodo_fin, Frontera &frontera, timestamp timestamp_inicio,
                  timestamp timestamp_fin) {
    // El nodo inicial (desde el que se empieza la búsqueda) se marca como explorado
    nodo_inicio->setExplored();

    // Si el nodo inicial es igual al final la búsqueda ha terminado
    if (nodo_inicio == nodo_fin) {
        return true;
    } else {
        // Obtengo los nodos a los que me conecto entre los intervalos de tiempo timestamp_inicio
        // y timestamp_fin
        // coste = caso peor lineal número de nodos
        auto conexiones = nodo_inicio->getConnections(timestamp_inicio, timestamp_fin);
        frontera.add(conexiones, nodo_inicio);

        // Obtiene el nodo más pequeño de la frontera y comprueba si ha sido explorado,
        // si ya lo ha sido lo elimina de la frontera ya que en un momento anterior
        // se analizó a todos los nodos a los que este puede infectar
        // coste = caso peor logaritmico número de nodos
        while (!frontera.isEmpty() && get<1>(frontera.getLowest())->isExplored()) {
            frontera.deleteLowest();
        }

        // Si no hay elementos en la frontera implica que se han explorado todas las conexiones
        // con nodos y no se ha encontrado infección
        if (frontera.isEmpty()) return false;
        else {
            // Obtiene el nodo más pequeño de la frontera, búsqueda voraz
            // coste = caso peor logaritmico número de nodos
            auto lowest = frontera.getLowest();
            frontera.deleteLowest();

            // Añade al nodo seleccionado su padre y el timestamp
            get<1>(lowest)->setInfectionTimestamp(get<2>(lowest));
            get<1>(lowest)->setInfectorNode(get<0>(lowest));

            // Resuelve la query para el nodo seleccionado
            // Esta función se ejecuta un máximo de n veces siendo n el número de nodos,
            // ya que el nodo tiene que ser no explorado, y al entrar en la función ese mismo
            // nodo pasa a ser explorado
            return resolveQuery(get<1>(lowest), nodo_fin, frontera, get<2>(lowest), timestamp_fin);
        }
    }
};