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

tuple < int, int, unsigned char* > loadTextureBMP(string filename){
	unsigned char *res;
	int height, width;
	height = width = 0;

	FILE *f = fopen(filename.c_str(), "rb");
	if(!f){
		cerr << "File not opened" << endl;
		return { height, width, res };
	}
	cout << "start reading file" << endl;

	unsigned char header[54];

	if(fread(header, 1, 54, f) != 54){
		cout << "File is not valid" << endl;
		return { height, width, res };
	}

	cout << "header is ready" << endl;

	int fileSize = 0, imageOffset = 0, imageSize = 0, compressionMethod = 0, numberOfBitPerPixel = 0;

	for(int i = 3;i >= 0;i--)
		fileSize <<= 8, fileSize += header[2 + i];
	for(int i = 3;i >= 0;i--)
		imageOffset <<= 8, imageOffset += header[10 + i];
	for(int i = 3;i >= 0;i--)
		width <<= 8, width += header[18 + i];
	for(int i = 3;i >= 0;i--)
		height <<= 8, height += header[22 + i];
	for(int i = 3;i >= 0;i--)
		imageSize <<= 8, imageSize += header[34 + i];
	for(int i = 3;i >= 0;i--)
		compressionMethod <<= 8, compressionMethod += header[30 + i];
	for(int i = 1;i >= 0;i--)
		numberOfBitPerPixel <<= 8, numberOfBitPerPixel += header[28 + i];

	cout << "fileSize: " << fileSize << " bytes" << endl;
	cout << "Image offset: " << imageOffset << endl;
	cout << "width: " << width << endl;
	cout << "height: " << height << endl;
	cout << "image size: " << imageSize << endl;
	cout << "compression method: " << compressionMethod << endl;
	cout << "number of bit per pixel: " << numberOfBitPerPixel << endl;

	unsigned char *buffer = new unsigned char[imageSize];
	if(fread(buffer, imageSize, 1, f) != imageSize){
		cerr << "Error while reading data" << endl;
	}

	fclose(f);
	
	res = new unsigned char[width * height * 3];

	int rowSize = (numberOfBitPerPixel * width + 31) / 32 * 4;
	cout << "row size: " << rowSize << endl;

	for(int i = 0;i < height;i++){
		for(int j = 0;j < width;j++){
			res[(i * width + j) * 3] = buffer[i * rowSize + j * 3];
			res[(i * width + j) * 3 + 1] = buffer[i * rowSize + j * 3 + 1];
			res[(i * width + j) * 3 + 2] = buffer[i * rowSize + j * 3 + 2];
		}
	}
	
	cout << "Ready" << endl;

	return { height, width, res };
}

int main(int argc, char **argv) {
	auto model = ModelLoader::loadModel("resources/models/texcube.obj");

	auto mapping = model.createMapping();

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
	auto txLocation = mainShader.getUniformLocation("tx");

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

	auto textureData = loadTextureBMP("resources/textures/texture.bmp");
	unsigned int texture = 0;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, get < 1 > (textureData), get < 0 > (textureData), 0, GL_RGB, GL_UNSIGNED_BYTE, get < 2 > (textureData));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glActiveTexture(GL_TEXTURE0);

    vao.unbind();

    vb.unbind();
    ib.unbind();

    double aspectRatio = (double) DEFAULT_SCREEN_WIDTH / DEFAULT_SCREEN_HEIGHT;

    projectionMatrix = glm::perspective(45.0f, (float)aspectRatio, .1f, 1000.f);
    worldMatrix = glm::translate(glm::mat4(1.0), glm::vec3(.5, 0, -1.));

    mainShader.start();
	mainShader.uniformMatrix4f(matrixLocation, &projectionMatrix[0][0]);	
	mainShader.uniformMatrix4f(worldMatrixLocation, &worldMatrix[0][0]);
	mainShader.uniform1ui(txLocation, 0);
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