#include "VertexBuffer.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

VertexBuffer::VertexBuffer() {
	cout << "constructing vertex buffer" << endl;
	glGenBuffers(1, &id);
	cout << "completed" << endl;
}

VertexBuffer::~VertexBuffer(){
	cout << "deconstructing vertex buffer" << endl;
	glDeleteBuffers(1, &id);
	cout << "completed" << endl;
}

void VertexBuffer::bufferData(float *data, int length){
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * length, data, GL_STATIC_DRAW);
}

void VertexBuffer::bind(){
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind(){
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}