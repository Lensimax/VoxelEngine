#version 330

// input attributes
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertNormal;

uniform mat4 normalMatrix;


uniform mat4 modelMat;
uniform mat4 projMat;
uniform mat4 viewMat;

uniform mat4 lightMat4;
uniform vec4 light;

out vec4 normal;
out vec4 normalView;
out vec4 eyeView;

out vec4 lightVec;

void main() {
	mat4 mv = viewMat * modelMat;

	gl_Position = projMat*mv*vec4(position, 1.0);

	normal = normalize(vec4(vertNormal,0.0));
	normalView = normalize(normalMatrix*normal);
	eyeView = normalize((-1)*mv*vec4(position,1.0));

	lightVec = viewMat * lightMat4 * light;
}
