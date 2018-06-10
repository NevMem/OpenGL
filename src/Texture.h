#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <tuple>
#include <iostream>
using namespace std;

class Texture{
private:
    unsigned int id;

public:
    Texture(){};
    ~Texture(){};

    void loadFromBMP(string filename);
    void activeTexture0();
    void activeTexture1();
    void activeTexture2();
    void activeTexture3();
};