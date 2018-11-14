#ifndef MATERIAL_H
#define MATERIAL_H

#ifndef GL_H
#define GL_H
#include <GL/gl.h>
#endif

#include "../shader.h"

class Material {

    public:
        virtual ~Material() = default;

        virtual void callUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, glm::vec3 light = glm::vec3(0.0,0.0,0.0)) = 0;
        virtual void createUI() = 0;
        virtual GLuint shaderID() = 0;
    protected:
        Shader *shader;

};

#endif
