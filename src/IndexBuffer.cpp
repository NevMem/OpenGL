#include "IndexBuffer.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

void IndexBuffer::init(){
	glGenBuffers(1, &id);
}

void IndexBuffer::bufferData(unsigned int *data, int length){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * length, data, GL_STATIC_DRAW);
}

void IndexBuffer::bind(){
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}