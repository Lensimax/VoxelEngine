#version 330

uniform sampler2D sceneRendered;

in vec2 texcoord;

out vec4 bufferColor;

void main(){

    bufferColor = texture(sceneRendered, texcoord);

    // bufferColor = vec4(texcoord.x,texcoord.y,0.0,1.0);

}
