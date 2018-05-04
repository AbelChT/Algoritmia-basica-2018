//
// Created by abel on 3/05/18.
//
#include <random>
#include <chrono>
#include <algorithm>
#include <climits>
#include <fstream>
#include <iterator>
#include "variables_globales.h"

using namespace std;

int main() {
    auto seed = chrono::system_clock::now().time_since_epoch().count();//seed
    default_random_engine random_engine(seed);//engine
    uniform_int_distribution<int> distribution(INT_MIN, INT_MAX); //distribution

    vector<int> random_vector(VECTOR_SIZE);

    generate(random_vector.begin(), random_vector.end(), [&] { return distribution(random_engine); });

    ofstream myfile(input_path);
    ostream_iterator<int> output_iterator(myfile, " ");
    copy(random_vector.begin(), random_vector.end(), output_iterator);
    return 0;
}

