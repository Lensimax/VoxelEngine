#ifndef MATERIAL_H
#define MATERIAL_H

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include "shader.h"
#include "../tools/lights/light.h"

class Material {

    public:
        virtual ~Material() = default;

        virtual void callUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, Light *light) = 0;
        virtual void createUI() = 0;
        virtual GLuint getShaderID() = 0;
        virtual void reloadShaders() = 0;
    protected:
        Shader *shader;

        void sendUniformMatrices(GLuint shaderID, glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat);

};

#endif
