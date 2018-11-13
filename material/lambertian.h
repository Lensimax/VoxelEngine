
#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H



#ifndef GLM_H
#define GLM_H
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#endif



#include "material.h"

class Lambertian : public Material {

    public:
        Lambertian(glm::vec4 color = glm::vec4(1.0,0.0,0.0,1.0));
        ~Lambertian();

        virtual void callUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, glm::vec3 light = glm::vec3(0.0,0.0,0.0));
        virtual void createUI();
        virtual GLuint shaderID();

    protected:
        glm::vec4 color;

        void createShader();
        void deleteShader();

        Shader *debugNormalShader;

        bool activeDebugNormal;

        float specularDeg;
        glm::vec3 ambientColor, specularColor;


};

#endif
