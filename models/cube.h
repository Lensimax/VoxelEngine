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
        virtual int nbFaces();

        virtual glm::mat4 getTransform();

        virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat);

        virtual GLuint shaderID();

    protected:
        void setUniform(glm::mat4 viewMat, glm::mat4 projectionMat);



        std::vector<float> createVertices();
        std::vector<int> createTriangles();

        std::vector<float> vertices;
        std::vector<int> faces;

        GLuint vertexArrayID;
        GLuint cubeVA[2];

        Shader *shader;

        void createShader();
        void deleteShader();

        void debugFaces();
        void debugVertices();


};

#endif
