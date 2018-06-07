#include "Camera.h"
#include <iostream>
using namespace std;

Camera::Camera(){
	eye = glm::vec3(0, 0, 0);
	look = glm::vec3(0, 0, -1);
	up = glm::vec3(0, 1, 0);
}

void Camera::move(glm::vec3 m){
	eye += m;
}

float *Camera::getEyePointer(){
	return &eye[0];
}

float *Camera::getEyeMatrix(){
	lookAtMatrix = glm::lookAt(eye, look, up);
	return &lookAtMatrix[0][0];
}