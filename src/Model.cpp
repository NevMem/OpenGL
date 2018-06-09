#include "Model.h"
#include <iostream>
using namespace std;

vector < pair < int, int > > Model::createMapping(){
    vector < pair < int, int > > mapping;

    if(vertexes.size() != 0)
        mapping.push_back({ 0, 3 });
    if(normals.size() != 0)
        mapping.push_back({ 1, 3 });
    if(tcoords.size() != 0)
        mapping.push_back({ 2, 2 });

    return mapping;
}

void Model::addVertex(glm::vec3 vertex){
    vertexes.push_back(vertex);
}

void Model::addNormal(glm::vec3 normal){
    normals.push_back(normal);
}

void Model::addTexCoord(glm::vec2 texCoord){
    tcoords.push_back(texCoord);
}

void Model::addFace(tuple < tuple < int, int, int >, tuple < int, int, int >, tuple < int, int, int > > face){
    faces.push_back(face);
}

void fill(float *offset, tuple < int, int, int > vertexInfo, Model &model){
    *(offset + 0) = model.vertexes[get < 0 > (vertexInfo)][0];
    *(offset + 1) = model.vertexes[get < 0 > (vertexInfo)][1];
    *(offset + 2) = model.vertexes[get < 0 > (vertexInfo)][2];

    *(offset + 6) = model.tcoords[get < 1 > (vertexInfo)][0];
    *(offset + 7) = model.tcoords[get < 1 > (vertexInfo)][1];

    *(offset + 3) = model.normals[get < 2 > (vertexInfo)][0];
    *(offset + 4) = model.normals[get < 2 > (vertexInfo)][1];
    *(offset + 5) = model.normals[get < 2 > (vertexInfo)][2];
}

pair < pair < float*, int >, pair < unsigned int*, int > > Model::createBuffers(){
    int oneVertexSize = (vertexes.size() != 0) * 3 + 
        (normals.size() != 0) * 3 + 
        (tcoords.size() != 0) * 2;

    cout << oneVertexSize << endl;

    int idxSize = faces.size() * 3;
    unsigned int *idx = new unsigned int[idxSize];
    int vrSize = oneVertexSize * idxSize;
    float *vrs = new float[vrSize];

    for(int i = 0;i < faces.size();i++){
        auto first = get < 0 > (faces[i]);
        auto second = get < 1 > (faces[i]);
        auto third = get < 2 > (faces[i]);

        fill(vrs + i * oneVertexSize * 3, first, *this);
        fill(vrs + i * oneVertexSize * 3 + oneVertexSize, second, *this);
        fill(vrs + i * oneVertexSize * 3 + 2 * oneVertexSize, third, *this);

        *(idx + i * 3 + 0) = i * 3;
        *(idx + i * 3 + 1) = i * 3 + 1;
        *(idx + i * 3 + 2) = i * 3 + 2;
    }

    return { { vrs, vrSize }, { idx, idxSize } };
}