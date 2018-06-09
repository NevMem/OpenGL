#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Model.h"
using namespace std;

class ModelLoader {
public:
    static Model loadModel(string filename);
};