#version 330

// input attributes
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertNormal;
layout(location = 2) in vec2 textureCoordinate;
layout(location = 3) in vec3 vertColor;


uniform mat4 normalMatrix;


uniform mat4 modelMat;
uniform mat4 projMat;
uniform mat4 viewMat;

uniform vec4 light;

out vec4 normal;
out vec4 normalView;
out vec4 eyeView;
out vec4 vertex;
out vec2 uv;
out vec3 color;

out vec4 lightVec;

void main() {
	vertex = vec4(position, 1.0);

	mat4 mv = viewMat * modelMat;

	gl_Position = projMat*mv*vec4(position, 1.0);

	normal = vec4(vertNormal,1.0);
	normalView = normalize(normalMatrix*normal);
	eyeView = (mv*vec4(position,1.0));

	lightVec = viewMat * vec4(light.xyz, 0.0);

	uv = textureCoordinate;
	color = vertColor;
}
