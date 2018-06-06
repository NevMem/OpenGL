#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include "includes.h"
#include "constants.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

using namespace std;

float *vr;
int vrSize = 0;
unsigned int *idx;
int idxSize = 0;

void value3f(float *location, float a, float b, float c){
	*location = a;
	*(location + 1) = b;
	*(location + 2) = c;
}

void value1ui(unsigned int *location, unsigned int value){
	*location = value;
}

void initializeCube(){
	vrSize = 3 * 8;
	vr = new float[vrSize];

	value3f(vr, 0, 0, -1);
	value3f(vr + 3, 1, 0, -1);
	value3f(vr + 6, 1, 1, -1);
	value3f(vr + 9, 0, 1, -1);

	value3f(vr + 12, 0, 0, -2);
	value3f(vr + 15, 1, 0, -2);
	value3f(vr + 18, 1, 1, -2);
	value3f(vr + 21, 0, 1, -2);

	idxSize = 6;
	idx = new unsigned int[idxSize];

	value1ui(idx, 0); value1ui(idx + 1, 1); value1ui(idx + 2, 2);
	value1ui(idx + 3, 0); value1ui(idx + 4, 2); value1ui(idx + 5, 3);

	//value1ui(idx + 6, 0); value1ui(idx + 7, 3); value1ui(idx + 8, 7);
	//value1ui(idx + 9, 7); value1ui(idx + 10, 0); value1ui(idx + 11, 4);

	//value1ui(idx + 12, 7); value1ui(idx + 13, 4); value1ui(idx + 14, 5);
	//value1ui(idx + 15, 7); value1ui(idx + 16, 5); value1ui(idx + 17, 6);
}

int main(void) {
	initializeCube();

    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "Hello World", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (!window){
        glfwTerminate();
        return -1;
    }
    
    if(glewInit() != GLEW_OK){
    	cout << "glew error" << endl;
    	return -1;
    }

    cout << glGetString(GL_VERSION) << endl;

    ShaderProgram mainShader;
    mainShader.initByFiles("resources/shaders/basicVertexShader.glsl", "resources/shaders/basicFragmentShader.glsl");

    auto loc = mainShader.getUniformLocation("uTime");
    auto matrixLocation = mainShader.getUniformLocation("mtrx");
    auto worldMatrixLocation = mainShader.getUniformLocation("worldMatrix");

    VertexArrayObject vao;
    vao.init();
    vao.bind();

    VertexBuffer vb = VertexBuffer();
    vb.init();
    vb.bufferData(vr, vrSize);

    IndexBuffer ib = IndexBuffer();
    ib.init();
    ib.bufferData(idx, idxSize);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    vao.unbind();

    vb.unbind();
    ib.unbind();

    double aspectRatio = 1024. / 768.;

    glm::mat4 projectionMatrix = glm::frustum(-1., 1., -1. / aspectRatio, 1. / aspectRatio, 1., 1000.);
    glm::mat4 worldMatrix = glm::translate(glm::mat4(1.0), glm::vec3(.5, 0, -1.));
    mainShader.start();
	mainShader.uniformMatrix4f(matrixLocation, &projectionMatrix[0][0]);	
	mainShader.uniformMatrix4f(worldMatrixLocation, &worldMatrix[0][0]);
    mainShader.stop();

    while (!glfwWindowShouldClose(window)){
    	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    	mainShader.start();
    	mainShader.uniform1f(loc, glfwGetTime());

    	glClearColor(.2, .4, .8, 1.);
    	glClear(GL_COLOR_BUFFER_BIT);

    	vao.bind();
    	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    	mainShader.stop();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}