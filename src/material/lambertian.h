
#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H



#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif



#include "material.h"

class Lambertian : public Material {

public:
    Lambertian(glm::vec4 ambientColor = glm::vec4(0.1,0.1,0.1,0.0), glm::vec4 specularColor = glm::vec4(64./255.,64./255.,64./255.,1.0), float specularDeg = 10, glm::vec4 diffuseColor = glm::vec4(255./255.,0./255.,0./255.,1.0), bool activeDebugNormal = false);
    ~Lambertian();

    virtual void callUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, Light *light);
    virtual void createUI();
    virtual GLuint getShaderID();
    virtual void reloadShaders();

    void toggleDisplayDiffuse(){m_displayDiffuse = !m_displayDiffuse; }

protected:

    void createShader();
    void deleteShader();

    Shader *m_debugNormalShader;

    bool m_activeDebugNormal;

    float m_specularDeg;
    glm::vec4 m_ambientColor, m_specularColor, m_diffuseColor;

    bool m_displayDiffuse = false;

    const char * m_lambertianShaderVert = "../data/shaders/lambertian.vert";
    const char * m_lambertianShaderFrag = "../data/shaders/lambertian.frag";
    const char * m_debugShaderVert = "../data/shaders/debugNormal.vert";
    const char * m_debugShaderFrag = "../data/shaders/debugNormal.frag";

};

#endif
