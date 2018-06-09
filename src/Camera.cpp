#include "Camera.h"
#include <iostream>
using namespace std;

Camera::Camera(){
	eye = glm::vec4(0, 0, 0, 0);
	look = glm::vec4(0, 0, -1, 0);
	up = glm::vec4(0, 1, 0, 0);
}

void Camera::move(glm::vec3 m){
	eye += glm::vec4(m, 0);
}

float *Camera::getEyeMatrix(){
	lookAtMatrix = glm::lookAt(glm::vec3(eye), glm::vec3(eye + look), glm::vec3(up));
	return &lookAtMatrix[0][0];
}

void Camera::rotateHorizontal(float angle){
	glm::mat4 transform = rotate(glm::mat4(1.), angle, glm::vec3(0, 1, 0));
	up = transform * up;
	look = transform * look;
}

void Camera::rotateVertical(float angle){
	glm::mat4 transform = rotate(glm::mat4(1.), angle, cross(glm::vec3(look), glm::vec3(up)));
	up = transform * up;
	look = transform * look;
}

void Camera::moveForward(){
	eye += look;
}

void Camera::moveBackward(){
	eye -= look;
}