#include "textureMaterial.h"

#include <stdio.h>
#include <stdlib.h>

#include <iostream>

#include <imgui.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


TextureMaterial::TextureMaterial(char file[2048]){

    createShader();

    m_imageBuffer = nullptr;

    m_imageWidth = -1;
    initTexture();

    createTexture(file);


}

TextureMaterial::~TextureMaterial(){
    deleteShader();
    stbi_image_free(m_imageBuffer);
    glDeleteTextures(1,&m_textureFBO);
}

void TextureMaterial::initTexture(){
    glGenTextures(1,&m_textureFBO);

    glBindTexture(GL_TEXTURE_2D,m_textureFBO);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void TextureMaterial::createTexture(char file[2048]){

    sprintf(m_filename, "%s", file);
    FILE *f = fopen(m_filename, "r");
    if(f){
        createImageBuffer(f);
        m_errorMessage ="";
        fclose(f);
    } else {
        if(m_imageWidth < 0){ // we fill with a default texture
            f = fopen(m_defaultTexture, "r");
            createImageBuffer(f);
            fclose(f);
        }
        m_errorMessage = "Couldn't find the texture file";
    }

}



void TextureMaterial::deleteShader(){
    delete m_shader;
}


void TextureMaterial::createImageBuffer(FILE *file){

    // stbi_set_flip_vertically_on_load(true);

    m_imageBuffer = stbi_load_from_file(file, &m_imageWidth, &m_imageHeight, &m_channels, STBI_rgb_alpha);

    if(m_imageBuffer == nullptr){
        m_errorMessage = "Couldn't load the texture from the file";
        createTexture((char*)m_defaultTexture);
    }

    glBindTexture(GL_TEXTURE_2D, m_textureFBO);

    // fill texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_imageWidth, m_imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_imageBuffer);

    // generate mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureMaterial::createUI(){
    // to hide label of the input

    if (ImGui::Button("Refresh")){
        reloadShaders();
        createTexture(m_filename);
    }

    ImGui::Text("Texture: "); ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f), m_errorMessage.c_str());
    ImGui::InputText("##fileTexture", m_filename, IM_ARRAYSIZE(m_filename));
}

void TextureMaterial::callUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, Light *light){

    GLuint shaderID = m_shader->id();

    sendUniformMatrices(shaderID, modelMat, viewMat, projMat);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_textureFBO);
    glUniform1i(glGetUniformLocation(shaderID,"tex"),0);


}

GLuint TextureMaterial::getShaderID(){
    return m_shader->id();
}

void TextureMaterial::createShader(){
    m_shader = new Shader();
    m_shader->load(m_textureShaderVert,m_textureShaderFrag);
}
void TextureMaterial::reloadShaders(){
    m_shader->reload(m_textureShaderVert,m_textureShaderFrag);
}
