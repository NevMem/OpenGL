#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "utils.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

using namespace std;

float vr[] = {
	-.5, .5, -1.0, 
	-.5, -.5, -1.0, 
	.5, -.5, -1.0, 
	.5, .5, -1.0, 	
};

unsigned int idx[] = {
	0, 1, 2, 
	2, 0, 3
};

int main(void) {
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
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

    VertexArrayObject vao;
    vao.init();
    vao.bind();

    VertexBuffer vb = VertexBuffer();
    vb.init();
    vb.bufferData(vr, 12);

    IndexBuffer ib = IndexBuffer();
    ib.init();
    ib.bufferData(idx, 6);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    vao.unbind();

    vb.unbind();
    ib.unbind();

    glm::mat4 projectionMatrix = glm::frustum(-1., 1., -1., 1., -1., 1000.);
    mainShader.start();
	mainShader.uniformMatrix4f(matrixLocation, &projectionMatrix[0][0]);	
    mainShader.stop();

    while (!glfwWindowShouldClose(window)){
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