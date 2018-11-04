#version 330

out vec4 bufferColor;

uniform vec4 color;

uniform vec3 light;


void main(){
	//bufferColor = vec4(1.0,1.0,0.0,1.0);
	if(light != vec3(0.0,0.0,0.0)){
		bufferColor = vec4(0.0,1.0,0,1.0);
	} else {
		bufferColor = color;
	}
}
