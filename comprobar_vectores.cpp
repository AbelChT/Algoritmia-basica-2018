//
// Created by abel on 3/05/18.
//
#include <random>
#include <chrono>
#include <algorithm>
#include <climits>
#include <fstream>
#include <iterator>
#include <iostream>
#include "variables_globales.h"

using namespace std;

int main() {
    ifstream myfile(output_path);

    istream_iterator<int> start(myfile), end;
    vector<int> random_vector(start, end);

    if (is_sorted(random_vector.begin(), random_vector.end())) {
        cout << "Correcto" << std::endl;
    } else {
        cout << "Fallo" << std::endl;
    }

    return 0;
}