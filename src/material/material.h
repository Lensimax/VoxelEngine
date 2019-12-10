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

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif


#include "shader.h"
#include "../tools/lights/light.h"

#include "../components/component.h"

class Material : public Component {

    public:
        virtual ~Material() = default;

        virtual void callUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat, Light *light) = 0;
        virtual void createUI() = 0;
        virtual GLuint getShaderID() = 0;
        virtual void reloadShaders() = 0;
    protected:
        Shader *m_shader;

        void sendUniformMatrices(GLuint shaderID, glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat);

};

#endif
