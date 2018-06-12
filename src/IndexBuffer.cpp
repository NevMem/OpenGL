#include "IndexBuffer.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

IndexBuffer::IndexBuffer(){
	cout << "constructing index buffer" << endl;
	glGenBuffers(1, &id);
	cout << "completed" << endl;
}

IndexBuffer::~IndexBuffer(){
	cout << "deconstructing index buffer" << endl;
	glDeleteBuffers(1, &id);
	cout << "completed" << endl;
}

void IndexBuffer::bufferData(unsigned int *data, int length){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * length, data, GL_STATIC_DRAW);
}

void IndexBuffer::bind(){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind(){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}