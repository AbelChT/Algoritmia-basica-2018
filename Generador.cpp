//
// Created by Jorge on 02/05/2018.
//

#include "Generador.h"
#include "Nodo.h"
#include <ctime>
#include <set>
#include <algorithm>

const int MAXTIMESTAMP=400;
const int MINNODES = 10;
const int MAXNODES = 100;
const char ficheroGenerado[] = "C:\\Users\\Jorge\\Desktop\\Algoritmia PR1\\ficheroPrueba";

int randNum(int min, int max){
    return (rand()%max)+min; // Randomizing the number between 1-15.
}

bool is_in(set<pair<Nodo*,int>> container, Nodo* element, int timestamp) {
    return container.find(make_pair(element,timestamp)) != container.end();
}

void connect(int node1, int node2, int moment, fstream& where){
    where << node1 << " " << node2 << " " << moment << '\n';
}

bool openIO(std::fstream& file, const char filename[]) {
    file.open(filename); // Try to open for I/O
    if (!file) {
        file.clear();
        file.open(filename, std::ios::out); // Create using out
        if (!file)  return false;
        file.close();
        file.open(filename); // Open for I/O
        if (!file)  return false;
    }
    return true;
}

bool funcionGeneradora(){
    std::fstream file;
    if(openIO(file,ficheroGenerado)){
        int numNodes = randNum(MINNODES,MAXNODES);
        int infectedNode = randNum(1,numNodes);

        std::vector <Nodo*> nodes;
        Nodo *infectedInit = nullptr;

        for (int i=1; i<numNodes ; i++) {
            if (i != infectedNode){
                Nodo *n = new Nodo(i);
                nodes.push_back(n);
            }
            else{
                infectedInit=new Nodo(i);
                nodes.push_back(infectedInit);
            }
        }

        int finalNode = randNum(1,numNodes);
        while(infectedNode==finalNode){
            finalNode=randNum(1,numNodes);
        }
        int initTimestamp = randNum(1,MAXTIMESTAMP/2);
        int finalTimestamp = randNum(initTimestamp+1,MAXTIMESTAMP);
        file << infectedNode << " " << initTimestamp << " " << finalNode << " " << finalTimestamp << '\n';

        std::set <pair<Nodo*,int>> infectedNodes;
        infectedNodes.insert(make_pair(infectedInit,initTimestamp));

        for(int i = 1 ; i<MAXTIMESTAMP; i++){
            bool infected = true;
            while(infected){
                infected = false;
                for(int j = 1; j<numNodes ; j++) {
                    for (int z = j + 1; z < numNodes; z++) {
                        int range = randNum(0, MAXTIMESTAMP * MAXTIMESTAMP);
                        if (range < MAXTIMESTAMP) {
                            connect(j, z, i, file);
                            Nodo *primero = nodes[j - 1];
                            Nodo *segundo = nodes[z - 1];
                            pair<set<std::pair<Nodo*,int>>::iterator,bool> result;
                            if (is_in(infectedNodes, primero, i) && i >= initTimestamp) {
                                result = infectedNodes.insert(make_pair(segundo, i));
                            }
                            if (is_in(infectedNodes, segundo, i) && i >= initTimestamp) {
                                result = infectedNodes.insert(make_pair(primero, i));
                            }
                            infected = result.second;
                        }
                    }
                }
            }
        }
        return is_in(infectedNodes, nodes[finalNode], finalTimestamp);
    }
    return false;
}
