#version 330

in vec3 position;
in vec3 normal;

uniform mat4 mtrx;
uniform mat4 worldMatrix;
uniform mat4 eyeMatrix;
uniform float uTime;

out vec3 Normal;

void main(){
	Normal = vec3(mtrx * worldMatrix * eyeMatrix * vec4(normal, .0));
	gl_Position = mtrx * worldMatrix * eyeMatrix * vec4(position, 1.);	
}