#version 330

in vec3 Normal;

out vec4 outColor;

uniform float uTime;

void main(){
	float intensity = dot(Normal, vec3(0, 1, 0));
	outColor = vec4(.2, .3, sin(uTime) / 20. + .8, 1.) * (.6 + .4 * intensity);
}