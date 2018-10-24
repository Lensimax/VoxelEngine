#ifndef CUBE_H
#define CUBE_H

#ifndef GLM_H
#define GLM_H
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#endif



#include "drawableObject.h"
#include "../shader.h"

#include <vector>

class Cube : public DrawableObject {
    public:

        Cube(vec3 position = glm::vec3(0.0,0.0,0.0), vec3 scale = glm::vec3(1.0,1.0,1.0), vec3 rotation = glm::vec3(0.0,0.0,0.0));
        ~Cube();


        virtual float *getVertices();
        virtual int *getTriangles();
        virtual int nbVertices();
        virtual int nbTriangles();

        virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat);

        virtual void debugTrianglesAndTriangles();

        void createVAO();
        void deleteVAO();

        glm::vec4 color;

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





};

#endif
