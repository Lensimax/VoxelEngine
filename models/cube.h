#ifndef CUBE_H
#define CUBE_H

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "drawableObject.h"
#include "shader.h"
#include "transform.h"

#include <vector>

class Cube : public DrawableObject {
    public:

        Cube();
        Cube(vec3 position);
        Cube(vec3 position, vec3 scale);
        ~Cube();


        virtual float *getVertices();
        virtual int *getTriangles();
        virtual int nbVertices();
        virtual int nbTriangles();

        virtual Transform* getTransform();

        virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat);

        virtual void debugTrianglesAndTriangles();

        void createVAO();
        void deleteVAO();
    protected:

        void setUniform(glm::mat4 viewMat, glm::mat4 projectionMat);

        void createShader();
        void deleteShader();


        std::vector<float> createVertices();
        std::vector<int> createTriangles();

        std::vector<float> vertices;
        std::vector<int> triangles;

        GLuint vertexArrayID;
        GLuint *buffers;

        Shader *shader;

        Transform *transform;



};

#endif