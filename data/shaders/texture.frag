#version 330

out vec4 bufferColor;

uniform sampler2D tex;

in vec2 uv;



void main(){

	bufferColor = vec4(uv.xy,0,1);
}
