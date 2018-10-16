#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "drawableObject.h"
#include "shader.h"

#include <vector>

class Cube : public DrawableObject {
    public:

        Cube();
        ~Cube();

        virtual inline float *getVertices();
        virtual inline int *getTriangles();

        virtual glm::mat4 getTransform();

        virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat);

    protected:
        virtual void createVAO();
        virtual void deleteVAO();
        void setUniform(glm::mat4 viewMat, glm::mat4 projectionMat);

        int nbVertices();
        int nbFaces();

        std::vector<float> createVertices();
        std::vector<int> createTriangles();

        std::vector<float> vertices;
        std::vector<int> faces;

        GLuint vertexArrayID;
        GLuint cubeVA[2];

        Shader *shader;

        void createShader();
        void deleteShader();


};

#endif
