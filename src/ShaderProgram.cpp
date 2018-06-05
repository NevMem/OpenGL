#include "ShaderProgram.h"
#include <string>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
using namespace std;

unsigned int CompileShader(unsigned int shaderType, string shaderText){
	unsigned int shader = glCreateShader(shaderType);
	const char *src = shaderText.c_str();

	glShaderSource(shader, 1, &src, NULL);

	glCompileShader(shader);
	int result;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE){
		cout << "error in compiling shader" << endl;

		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char *message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);
		cout << message << endl;
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

unsigned int CreateShader(string vShaderText, string fShaderText){
	unsigned int vShader = CompileShader(GL_VERTEX_SHADER, vShaderText);
	unsigned int fShader = CompileShader(GL_FRAGMENT_SHADER, fShaderText);

	unsigned int program = glCreateProgram();

	glAttachShader(program, vShader);
	glAttachShader(program, fShader);

	glLinkProgram(program);
	glValidateProgram(program);

	GLint res;
	glGetProgramiv(program, GL_VALIDATE_STATUS, &res);
	if(res != GL_TRUE){
		cout << "Program not validated" << endl;
	}

	glDeleteShader(vShader);
	glDeleteShader(fShader);

	return program;
}

unsigned int CreateShaderFromFiles(string vShaderFile, string fShaderFile){
	string s;
	ifstream ln(vShaderFile);

	string vShaderText = "", fShaderText = "";

	while(getline(ln, s, '\n')){
		vShaderText += s + '\n';
	}

	ln = ifstream(fShaderFile);
	while(getline(ln, s, '\n')){
		fShaderText += s + '\n';
	}

	return CreateShader(vShaderText, fShaderText);
}

void ShaderProgram::init(string vertexShaderText, string fragmentShaderText){
	id = CreateShader(vertexShaderText, fragmentShaderText);
	cout << id << endl;
}


void ShaderProgram::initByFiles(string vertexShaderFile, string fragmentShaderFile){
	id = CreateShaderFromFiles(vertexShaderFile, fragmentShaderFile);
	cout << id << endl;
}

void ShaderProgram::start(){
	glUseProgram(id);
}

void ShaderProgram::stop(){
	glUseProgram(0);
}