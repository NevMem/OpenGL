#pragma once
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <tuple>
using namespace std;

class Model {
public:
    vector < glm::vec3 > vertexes;  
    vector < glm::vec3 > normals;
    vector < glm::vec2 > tcoords;
    vector < tuple < tuple < int, int, int >, tuple < int, int, int >, tuple < int, int, int > > > faces;

public:
    void addVertex(glm::vec3 vertex);
    void addNormal(glm::vec3 normal);
    void addTexCoord(glm::vec2 texCoord);
    void addFace(tuple < tuple < int, int, int >, tuple < int, int, int >, tuple < int, int, int > > face);

    vector < pair < int, int > > createMapping();
    pair < pair < float*, int >, pair < unsigned int*, int > > createBuffers();
};