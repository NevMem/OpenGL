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
}


void ShaderProgram::initByFiles(string vertexShaderFile, string fragmentShaderFile){
	id = CreateShaderFromFiles(vertexShaderFile, fragmentShaderFile);
}

void ShaderProgram::start(){
	glUseProgram(id);
}

void ShaderProgram::stop(){
	glUseProgram(0);
}

unsigned int ShaderProgram::getUniformLocation(string name){
	unsigned int res = glGetUniformLocation(id, name.c_str());
	return res;
}

void ShaderProgram::uniform1f(unsigned int location, float a){
	glUniform1f(location, a);
}

void ShaderProgram::uniform2f(unsigned int location, float a, float b){
	glUniform2f(location, a, b);
}

void ShaderProgram::uniform3f(unsigned int location, float a, float b, float c){
	glUniform3f(location, a, b, c);
}

void ShaderProgram::uniform4f(unsigned int location, float a, float b, float c, float d){
	glUniform4f(location, a, b, c, d);
}

void ShaderProgram::uniformMatrix4f(unsigned int location, float *pointer){
	glUniformMatrix4fv(location, 1, false, pointer);
}

void ShaderProgram::uniform1ui(unsigned int location, unsigned int value){
	glUniform1ui(location, value);
}