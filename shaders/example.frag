#version 330

out vec4 bufferColor;

uniform vec4 color;


void main(){
	//bufferColor = vec4(1.0,1.0,0.0,1.0);
	bufferColor = color;
}
