#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "geometry.h"
#include "utils.h"
using namespace std;

float vr[] = {
	-.5, .5, .0, 
	-.5, -.5, .0, 
	.5, -.5, .0, 
	.5, .5, .0, 	
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

    unsigned int shader = CreateShader("resources/shaders/basicVertexShader.glsl", "resources/shaders/basicFragmentShader.glsl");

    VertexArrayObject vao;
    vao.init();
    vao.bind();

    glUseProgram(shader);

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

    while (!glfwWindowShouldClose(window)){
    	glClearColor(.2, .4, .8, 1.);
    	glClear(GL_COLOR_BUFFER_BIT);

    	vao.bind();
    	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}