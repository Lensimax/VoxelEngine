#version 330

out vec4 bufferColor;

in vec3 normal;



void main(){

	bufferColor = vec4(normal, 1.0);
}
