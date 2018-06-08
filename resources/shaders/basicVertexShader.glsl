#version 330

in vec3 position;
uniform mat4 mtrx;
uniform mat4 worldMatrix;
uniform mat4 eyeMatrix;
uniform float uTime;

void main(){
	gl_Position = mtrx * worldMatrix * eyeMatrix * vec4(position, 1.);	
}