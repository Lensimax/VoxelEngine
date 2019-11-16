
#ifndef SIMPLEMAT_H
#define SIMPLEMAT_H



#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif



#include "material.h"

class SimpleMat : public Material {

    public:
        SimpleMat(glm::vec4 color = glm::vec4(255./255.,255./255.,0./255.,1.0));
        ~SimpleMat();

        virtual void callUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, Light *light);
        virtual void createUI();
        virtual GLuint getShaderID();
        virtual void reloadShaders();

    protected:

        void createShader();
        void deleteShader();


        glm::vec4 color;

        const char * simpleShaderVert = "../data/shaders/simple.vert";
        const char * simpleShaderFrag = "../data/shaders/simple.frag";

};

#endif
