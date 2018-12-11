#version 330


in vec3 pixelPos;

out vec4 bufferColor;

void main(){

    vec2 uvCoord = 0.5 + pixelPos.xy * 0.5;

    bufferColor = vec4(uvCoord.x,uvCoord.y,0.0,1.0);
}
