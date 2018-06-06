#version 330

out vec4 outColor;

uniform float uTime;

void main(){
	outColor = vec4(.2, .3, sin(uTime) / 20. + .8, 1.);
}