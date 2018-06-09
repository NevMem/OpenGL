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

int toInt(string s){
    int ans = 0;
    for(auto el: s)
        ans *= 10, ans += el - '0';
    return ans;
}

tuple < int, int, int > parseVertexInfo(string s){
    string now = "";
    vector < int > r;
    for(int i = 0;i < s.size();i++)
        if(s[i] == '/')
            r.push_back(toInt(now)), now = "";
        else
            now += s[i];
    r.push_back(toInt(now));

    tuple < int, int, int > vertexInfo;
    get < 0 > (vertexInfo) = r[0] - 1;
    get < 1 > (vertexInfo) = r[1] - 1;
    get < 2 > (vertexInfo) = r[2] - 1;
    return vertexInfo;
}

Model ModelLoader::loadModel(string filename){
    cout << "Loading model from file " << filename << endl;
    Model model;

    ifstream rd(filename);

    string s;
    while(rd >> s){
        if(s == "f"){
            string a, b, c;
            rd >> a >> b >> c;
            model.addFace({ parseVertexInfo(a), parseVertexInfo(b), parseVertexInfo(c) });
        } else if(s == "v"){
            double x, y, z;
            rd >> x >> y >> z;
            model.addVertex(glm::vec3(x, y, z));
        } else if(s == "vn"){
            double x, y, z;
            rd >> x >> y >> z;
            model.addNormal(glm::vec3(x, y, z));
        } else if(s == "vt"){
            double x, y;
            rd >> x >> y;
            model.addTexCoord(glm::vec2(x, y));
        }
    }

    cout << "vertices: " << model.vertexes.size() << endl;
    cout << "normals: " << model.normals.size() << endl;
    cout << "texture coordinates: " << model.tcoords.size() << endl;
    cout << "faces: " << model.faces.size() << endl;

    return model;
}