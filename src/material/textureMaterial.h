#ifndef TEXTUREMATERIAL_H
#define TEXTUREMATERIAL_H

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include <stdlib.h>


#include "material.h"

class TextureMaterial : public Material {

public:
    TextureMaterial(char file[2048]);
    ~TextureMaterial();

    virtual void callUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, Light *light);
    virtual void createUI();
    virtual GLuint getShaderID();
    virtual void reloadShaders();

private:
    char m_filename[2048];

    unsigned char *m_imageBuffer;

    void createShader();
    void deleteShader();
    void createTexture(char file[2048]);

    void createImageBuffer(FILE *file);
    void initTexture();

    const char m_defaultTexture[2048] = "../data/textures/pattern.jpg";

    const char * m_textureShaderVert = "../data/shaders/texture.vert";
    const char * m_textureShaderFrag = "../data/shaders/texture.frag";

    int m_imageWidth,m_imageHeight, m_channels;

    std::string m_errorMessage;



    GLuint m_textureFBO;

};


#endif
