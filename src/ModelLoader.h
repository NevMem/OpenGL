#pragma once
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class ModelLoader {
public:
    static pair < vector < float >, vector < unsigned int > > loadModel(string filename);
};