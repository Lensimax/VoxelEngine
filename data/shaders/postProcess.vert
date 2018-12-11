#version 330

// input attributes
layout(location = 0) in vec3 position;// position of the vertex in world space

out vec3 pixelPos;

void main() {
    pixelPos = normalize(position);
	gl_Position = vec4(position,1.0);
}
