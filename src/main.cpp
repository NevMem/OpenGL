#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

#include "includes.h"
#include "variables.h"

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

Camera mainCamera;
bool isDragging = false;
double dragX, dragY;

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods){
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		isDragging = true;
		dragX = xpos;
		dragY = ypos;
	}

	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE){
		isDragging = false;
	}
}	

void mouseCallback(GLFWwindow *window, double xpos, double ypos){
	if(isDragging){
		double deltaX = xpos - dragX;
		double deltaY = ypos - dragY;
		dragX = xpos;
		dragY = ypos;
		mainCamera.rotateHorizontal(deltaX / DEFAULT_SCREEN_WIDTH);
		mainCamera.rotateVertical(deltaY / DEFAULT_SCREEN_HEIGHT);
	}
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
	if(key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)){
		mainCamera.moveForward();	
	}
	if(key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)){
		mainCamera.moveBackward();
	}
	if(key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)){
		mainCamera.rotateHorizontal(-acos(-1) / 36);
	}
	if(key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)){
		mainCamera.rotateHorizontal(acos(-1) / 36);
	}
	if(key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)){
		mainCamera.rotateVertical(acos(-1) / 36);
	}
	if(key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)){
		mainCamera.rotateVertical(-acos(-1) / 36);
	}
}

glm::mat4 projectionMatrix, worldMatrix, eyeMatrix;

int main(int argc, char **argv) {
	auto model = ModelLoader::loadModel("resources/models/texcube.obj");

	auto mapping = model.createMapping();
	for(auto el: mapping)
		cout << el.first << ' ' << el.second << endl;

	auto buffers = model.createBuffers();

	vr = buffers.first.first;
	vrSize = buffers.first.second;

	idx = buffers.second.first;
	idxSize = buffers.second.second;

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
    auto eyeMatrixLocation = mainShader.getUniformLocation("eyeMatrix");

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    vao.unbind();

    vb.unbind();
    ib.unbind();

    double aspectRatio = (double) DEFAULT_SCREEN_WIDTH / DEFAULT_SCREEN_HEIGHT;

    projectionMatrix = glm::perspective(45.0f, (float)aspectRatio, .1f, 1000.f);
    worldMatrix = glm::translate(glm::mat4(1.0), glm::vec3(.5, 0, -1.));

    mainShader.start();
	mainShader.uniformMatrix4f(matrixLocation, &projectionMatrix[0][0]);	
	mainShader.uniformMatrix4f(worldMatrixLocation, &worldMatrix[0][0]);
    mainShader.stop();

    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetKeyCallback(window, keyCallback);

	glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)){
    	if (WIRED_MODE)
    		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    	mainShader.start();
    	mainShader.uniformMatrix4f(eyeMatrixLocation, mainCamera.getEyeMatrix());
    	mainShader.uniform1f(loc, glfwGetTime());

    	glClearColor(.2, .2, .2, 1.);
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    	vao.bind();
    	glDrawElements(GL_TRIANGLES, idxSize, GL_UNSIGNED_INT, 0);

    	mainShader.stop();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}