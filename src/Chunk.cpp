#include "Chunk.h"
using namespace std;

int CHUNK_WIDTH = 16;
int CHUNK_HEIGHT = 32;

void cube(int x, int z, int y, float *vr, unsigned int *idx, int offset, pair < pair < float*, int >, pair < unsigned int*, int > > buffers){
    for(int i = 0;i < buffers.first.second / 8;i++){
        *(vr + i * 8 + 0) = (buffers.first.first[i * 8 + 0] + 1.) / 2. + x;
        *(vr + i * 8 + 1) = (buffers.first.first[i * 8 + 1] + 1.) / 2. + y;
        *(vr + i * 8 + 2) = (buffers.first.first[i * 8 + 2] + 1.) / 2. + z;

        *(vr + i * 8 + 3) = buffers.first.first[i * 8 + 3];
        *(vr + i * 8 + 4) = buffers.first.first[i * 8 + 4];
        *(vr + i * 8 + 5) = buffers.first.first[i * 8 + 5];

        *(vr + i * 8 + 6) = buffers.first.first[i * 8 + 6];
        *(vr + i * 8 + 7) = buffers.first.first[i * 8 + 7];
    }

    for(int i = 0;i < buffers.second.second;i++){
        *(idx + i + offset * 36) = buffers.second.first[i] + offset * 36;
    }
}

inline int index(int a, int b, int c){
    return c * CHUNK_WIDTH * CHUNK_WIDTH + b * CHUNK_WIDTH + a;
}

Chunk::Chunk(){
    cout << "Chunk constructor started" << endl;
    blocks = new unsigned short[CHUNK_HEIGHT * CHUNK_WIDTH * CHUNK_WIDTH];
    cout << "memory for block info allocated(" << CHUNK_HEIGHT * CHUNK_WIDTH * CHUNK_WIDTH * sizeof(unsigned short) << " bytes)" << endl;

    generateChunk();

    auto cubeModel = ModelLoader::loadModel("resources/models/texcube.obj");
    auto buffers = cubeModel.createBuffers();

    int vertexBufferLength = 288 * CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;
    int indexBufferLength = 36 * CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;

    cout << "chunk vertex buffer length: " << vertexBufferLength << endl;
    cout << "chunk index buffer length: " << indexBufferLength << endl;

    float *vr = new float[vertexBufferLength];
    unsigned int *idx = new unsigned int[indexBufferLength];

    for(int i = 0;i < CHUNK_WIDTH;i++){
        for(int j = 0;j < CHUNK_WIDTH;j++){
            for(int k = 0;k < CHUNK_HEIGHT;k++){
                cube(i, j, k, vr + index(i, j, k) * 288, idx, index(i, j, k), buffers);
            }
        }
    }

    vbo.bufferData(vr, vertexBufferLength);
    ibo.bufferData(idx, indexBufferLength);

    vao.bind();

    vbo.bind();
    ibo.bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    vao.unbind();
    vbo.unbind();
    ibo.unbind();
}

void Chunk::render(){
    vao.bind();
    glDrawElements(GL_TRIANGLES, 36 * CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT, GL_UNSIGNED_INT, 0);
    vao.unbind();
}

Chunk::~Chunk(){
    cout << "Chunk deconstructor started" << endl;
    delete []blocks;
}

void Chunk::generateChunk(){
    cout << "Starting chunk generator" << endl;

    for(int i = 0;i < CHUNK_WIDTH;i++){
        for(int j = 0;j < CHUNK_WIDTH;j++){
            for(int k = 0;k < CHUNK_HEIGHT;k++){
                blocks[index(i, j, k)] = 0;

                if(k < i + j + 10)
                    blocks[index(i, j, k)] = 1;
            } 
        }
    }

    cout << "Chunk was successfully generated" << endl;
}