#include "VertexArrayObject.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

VertexArrayObject::VertexArrayObject(){
	cout << "constructing VAO" << endl;
	glGenVertexArrays(1, &id);
	cout << "completed" << endl;
}

VertexArrayObject::~VertexArrayObject(){
	cout << "deconstruction VAO" << endl;
	glDeleteVertexArrays(1, &id);
	cout << "completed" << endl;
}

void VertexArrayObject::bind(){
	glBindVertexArray(id);
}

void VertexArrayObject::unbind(){
	glBindVertexArray(0);
}