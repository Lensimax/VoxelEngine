#version 330

out vec4 bufferColor;


uniform vec4 color;


void main(){

	bufferColor = color;
	// bufferColor = vec4(1,0,0,1);
}
