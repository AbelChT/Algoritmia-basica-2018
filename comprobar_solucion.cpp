//
// Created by abel on 11/05/18.
//
#include <fstream>
#include <iostream>
#include "variables_globales.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc == 3) {
        bool resultado_algotirmo, resultado_correcto;
        ifstream salida_algoritmo;
        salida_algoritmo.open(argv[2]);
        if (salida_algoritmo.is_open()) {
            salida_algoritmo >> resultado_algotirmo;
        } else {
            return -1;
        }
        salida_algoritmo.close();

        ifstream salida_pruebas;
        salida_pruebas.open(argv[1]);
        if (salida_pruebas.is_open()) {
            salida_pruebas >> resultado_correcto;
        } else {
            return -1;
        }

        if (resultado_correcto == resultado_algotirmo) {
            cout << "Prueba pasada" << endl;
        } else {
            cout << "Prueba fallida" << endl;
            if (resultado_correcto) {
                cout << "Resultado correcto: si" << endl;
                cout << "Resultado algoritmo: no" << endl;
            } else {
                cout << "Resultado correcto: no" << endl;
                cout << "Resultado algoritmo: si" << endl;
            }
        }
        return 0;
    } else {
        cout
                << "Error: Ha de especificar  el nombre del fichero con la solución correcta como primer parámetro y el nombre del fichero con la solución que ha devuelto el algoritmo como segundo parámetro"
                << endl;
        return 1;
    }
}
