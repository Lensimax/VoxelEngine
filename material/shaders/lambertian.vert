#version 330

// input attributes
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertNormal;

uniform mat3 normalMatrix;


uniform mat4 modelMat;
uniform mat4 projMat;
uniform mat4 viewMat;

out vec3 normal;
out vec3 normalView;
out vec3 eyeView;

void main() {
	mat4 mv = viewMat * modelMat;

	gl_Position = projMat*mv*vec4(position, 1.0);

	normal = normalize(vertNormal);
	normalView = normalize(normalMatrix*normal);
	eyeView = normalize((mv*vec4(position,1.0)).xyz);
}
