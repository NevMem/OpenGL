#version 330

in vec3 position;
uniform mat4 mtrx;
uniform mat4 worldMatrix;
uniform float uTime;

void main(){
	gl_Position = mtrx * worldMatrix * vec4(position, 1.);	
}