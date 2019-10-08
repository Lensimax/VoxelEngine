
#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H



#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif



#include "material.h"

class Lambertian : public Material {

    public:
        Lambertian(glm::vec4 color = glm::vec4(188./255.,150./255.,185./255.,1.0));
        ~Lambertian();

        virtual void callUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, Light *light);
        virtual void createUI();
        virtual GLuint shaderID();
        virtual void reloadShaders();

    protected:

        void createShader();
        void deleteShader();

        Shader *debugNormalShader;

        bool activeDebugNormal;

        float specularDeg;
        glm::vec4 ambientColor, specularColor, diffuseColor;

};

#endif
