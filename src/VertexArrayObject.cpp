#include "VertexArrayObject.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

void VertexArrayObject::init(){
	glGenVertexArrays(1, &id);
}

void VertexArrayObject::bind(){
	glBindVertexArray(id);
}

void VertexArrayObject::unbind(){
	glBindVertexArray(0);
}