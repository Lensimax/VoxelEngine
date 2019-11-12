#include "textureMaterial.h"

#include <stdio.h>
#include <stdlib.h>

#include <imgui.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../images_loader/stb_image.h"


TextureMaterial::TextureMaterial(char file[2048]){

    createShader();

    createTexture(file);

}

void TextureMaterial::createTexture(char file[2048]){

    sprintf(filename, "%s", file);
    FILE *f = fopen(filename, "r");
    if(f){
        createImageBuffer(f);
        errorMessage ="";
    } else {
        f = fopen(defaultTexture, "r");
        createImageBuffer(f);
        errorMessage = "Couldn't find the texture file";
    }
    fclose(f);
}


TextureMaterial::~TextureMaterial(){
    deleteShader();
    stbi_image_free(imageBuffer);
}

void TextureMaterial::deleteShader(){
    delete shader;
}


void TextureMaterial::createImageBuffer(FILE *file){

    stbi_set_flip_vertically_on_load(true);

    imageBuffer = stbi_load_from_file(file, &imageWidth, &imageWidth, &channels, STBI_rgb);


}

void TextureMaterial::createUI(){
    // to hide label of the input

    if (ImGui::Button("Refresh")){
        reloadShaders();
        createTexture(filename);
    }

    ImGui::Text("Texture: "); ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), errorMessage.c_str());
    ImGui::InputText("##fileTexture", filename, IM_ARRAYSIZE(filename));
}

void TextureMaterial::callUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, Light *light){

    GLuint shaderID = shader->id();

    sendUniformMatrices(shaderID, modelMat, viewMat, projMat);

    glUniform1i(glGetUniformLocation(shaderID,"tex"),1);


}

GLuint TextureMaterial::getShaderID(){
    return shader->id();
}

void TextureMaterial::createShader(){
    shader = new Shader();
    shader->load(textureShaderVert,textureShaderFrag);
}
void TextureMaterial::reloadShaders(){
    shader->reload(textureShaderVert,textureShaderFrag);
}
