#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tcoord;

uniform mat4 mtrx;
uniform mat4 worldMatrix;
uniform mat4 eyeMatrix;
uniform float uTime;

out vec3 Normal;
out vec2 tCoord;

void main(){
	tCoord = tcoord;
	Normal = vec3(mtrx * eyeMatrix * worldMatrix * vec4(normal, .0));
	gl_Position = mtrx * eyeMatrix * worldMatrix * vec4(position, 1.);	
}