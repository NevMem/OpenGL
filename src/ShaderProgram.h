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
};