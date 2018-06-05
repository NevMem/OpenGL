#version 330

in vec3 position;
uniform mat4 mtrx;

void main(){
	gl_Position = mtrx * vec4(position, 1.);	
}