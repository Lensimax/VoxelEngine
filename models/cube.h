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

        virtual float *getVertices();
        virtual int *getTriangles();
        virtual int nbVertices();
        virtual int nbTriangles();

        virtual glm::mat4 getTransform();

        virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat);

        virtual void debugTrianglesAndTriangles();

        void createVAO();
        void deleteVAO();
    protected:
        void setUniform(glm::mat4 viewMat, glm::mat4 projectionMat);



        std::vector<float> createVertices();
        std::vector<int> createTriangles();

        std::vector<float> vertices;
        std::vector<int> triangles;

        GLuint vertexArrayID;
        GLuint *buffers;

        Shader *shader;

        void createShader();
        void deleteShader();



};

#endif
