#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <glm/vec3.hpp>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "ModelLoader.h"
using namespace std;

class Chunk {
private:
    unsigned short *blocks;
    VertexBuffer vbo;
    IndexBuffer ibo;
    VertexArrayObject vao;

public:
    void loadChunk(string filename);
    void generateChunk();

    void render();

    Chunk();
    ~Chunk();
};