#version 330

in vec3 position;
uniform mat4 mtrx;
uniform float uTime;

void main(){
	gl_Position = mtrx * vec4(position.x, position.y, position.z + sin(uTime) / 2., 1.);	
}