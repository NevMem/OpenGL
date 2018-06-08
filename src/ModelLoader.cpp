#include "ModelLoader.h"
#include <iostream>
#include <glm/vec3.hpp>
using namespace std;

vector < string > split(string &line){
    vector < string > ret;

    string now = "";

    for(int i = 0;i < line.size();i++){
        if(line[i] != ' '){
            now += line[i];
        } else {
            if(now.size() != 0)
                ret.push_back(now);
            now = "";
        }
    }
    
    if(now.size() != 0)
        ret.push_back(now);

    return ret;
}

pair < vector < float >, vector < unsigned int > > ModelLoader::loadModel(string filename){
    cerr << "Loading model from " << filename << endl;
    ifstream rd(filename);
    
    vector < glm::vec3 > vertexes;
    vector < glm::vec3 > normals;
    pair < vector < float >, vector < unsigned int > > model;

    string s;
    while(rd >> s){
        if(s == "f"){
            int v1, v2, v3;
            int n1, n2, n3;
            char c;
            rd >> v1 >> c >> c >> n1 >> v2 >> c >> c >> n2 >> v3 >> c >> c >> n3;

            --v1;
            --v2;
            --v3;
            --n1;
            --n2;
            --n3;

            int offset = model.first.size() / 6;

            for(int i = 0;i < 3;i++)
                model.first.push_back(vertexes[v1][i]);
            for(int i = 0;i < 3;i++)
                model.first.push_back(normals[n1][i]);

            
            for(int i = 0;i < 3;i++)
                model.first.push_back(vertexes[v2][i]);
            for(int i = 0;i < 3;i++)
                model.first.push_back(normals[n2][i]);

                
            for(int i = 0;i < 3;i++)
                model.first.push_back(vertexes[v3][i]);
            for(int i = 0;i < 3;i++)
                model.first.push_back(normals[n3][i]);

            model.second.push_back(offset);
            model.second.push_back(offset + 1);
            model.second.push_back(offset + 2);
        } else if(s == "vn"){
            float x, y, z;
            rd >> x >> y >> z;
            normals.push_back(glm::vec3(x, y, z));
        } else if(s == "v"){
            float x, y, z;
            rd >> x >> y >> z;
            vertexes.push_back(glm::vec3(x, y, z));
        }
    }
    
    return model;
}