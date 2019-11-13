#include "textureMaterial.h"

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <imgui.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../images_loader/stb_image.h"


TextureMaterial::TextureMaterial(char file[2048]){

    createShader();

    imageBuffer = nullptr;

    imageWidth = -1;
    initTexture();

    createTexture(file);


}

TextureMaterial::~TextureMaterial(){
    deleteShader();
    stbi_image_free(imageBuffer);
    glDeleteTextures(1,&_textureFBO);
}

void TextureMaterial::initTexture(){
    glGenTextures(1,&_textureFBO);

    glBindTexture(GL_TEXTURE_2D,_textureFBO);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void TextureMaterial::createTexture(char file[2048]){

    sprintf(filename, "%s", file);
    FILE *f = fopen(filename, "r");
    if(f){
        createImageBuffer(f);
        errorMessage ="";
        fclose(f);
    } else {
        if(imageWidth < 0){ // we fill with a default texture
            f = fopen(defaultTexture, "r");
            createImageBuffer(f);
            fclose(f);
        }
        errorMessage = "Couldn't find the texture file";
    }

}



void TextureMaterial::deleteShader(){
    delete shader;
}


void TextureMaterial::createImageBuffer(FILE *file){

    // stbi_set_flip_vertically_on_load(true);

    imageBuffer = stbi_load_from_file(file, &imageWidth, &imageHeight, &channels, STBI_rgb_alpha);

    if(imageBuffer == nullptr){
        errorMessage = "Couldn't load the texture from the file";
        createTexture((char*)defaultTexture);
    }

    glBindTexture(GL_TEXTURE_2D, _textureFBO);

    // fill texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBuffer);

    // generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
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


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureFBO);
    glUniform1i(glGetUniformLocation(shaderID,"tex"),0);


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
