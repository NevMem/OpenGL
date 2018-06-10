#pragma once
#include <string>
using namespace std;

class ShaderProgram {
private: 
	unsigned int id;

public:
	ShaderProgram(){}
	~ShaderProgram(){}

	void init(string vertexShaderText, string fragmentShaderText);
	void initByFiles(string vertexShaderFile, string fragmentShaderFile);

	void start();
	void stop();

	unsigned int getUniformLocation(string name);
	void uniform1f(unsigned int location, float a);
	void uniform2f(unsigned int location, float a, float b);
	void uniform3f(unsigned int location, float a, float b, float c);
	void uniform4f(unsigned int location, float a, float b, float c, float d);
	void uniform1i(unsigned int location, int value);

	void uniformMatrix4f(unsigned int location, float *pointer);
};