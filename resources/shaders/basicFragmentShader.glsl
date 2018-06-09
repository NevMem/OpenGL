#version 330

in vec3 Normal;
in vec2 tCoord;
out vec4 outColor;
uniform float uTime;

uniform sampler2D tx;

void main(){
	float intensity = dot(Normal, vec3(0, 1, 0));
	//outColor = vec4(.2, .3, sin(uTime) / 20. + .8, 1.) * (.6 + .4 * intensity);
	outColor = vec4(texture(tx, tCoord).rgb, 1.) * (.5 + .5 * intensity);
}