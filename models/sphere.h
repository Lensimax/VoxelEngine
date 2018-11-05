#ifndef SPHERE_H
#define SPHERE_H

#include "drawableObject.h"

#include "../material/material.h"

#include <vector>

class Sphere : public DrawableObject {
    public:
        Sphere(std::string n = "Sphere", float radius = 1.0f, unsigned int rings = 12, unsigned int sectors = 24,
            vec3 position = glm::vec3(0.0,0.0,0.0), vec3 scale = glm::vec3(1.0,1.0,1.0), vec3 rotation = glm::vec3(0.0,0.0,0.0));

        ~Sphere();


        virtual float *getVertices();
        virtual int *getTriangles();
        virtual int nbVertices();
        virtual int nbTriangles();

        virtual void createUI(char *ID);

        virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat, glm::vec3 light = glm::vec3(0.0,0.0,0.0));

    // https://stackoverflow.com/questions/5988686/creating-a-3d-sphere-in-opengl-using-visual-c/5989676#5989676
    private:

        std::vector<float> vertices;
        std::vector<int> triangles;
        std::vector<float> normals;
        std::vector<float> texCoords;

        GLuint vertexArrayID;
        GLuint *buffers;

        Material *material;

        void createVAO();
        void deleteVAO();

        void createMesh(float radius, unsigned int rings, unsigned int sectors);
        void setUniform(glm::mat4 viewMat, glm::mat4 projectionMat, glm::vec3 light);
};


#endif
