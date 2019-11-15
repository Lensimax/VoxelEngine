#version 330

// input attributes
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertNormal;
layout(location = 2) in vec2 texCoord;


uniform mat4 modelMat;
uniform mat4 projMat;
uniform mat4 viewMat;

out vec2 uv;

void main() {
	uv = texCoord;
	gl_Position = projMat*viewMat*modelMat*vec4(position, 1.0);
}
