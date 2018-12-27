#ifndef SPHERE_H
#define SPHERE_H

#include "drawableObject.h"

#include "../material/material.h"
#include "../models/mesh.h"

#include <vector>

class Sphere : public DrawableObject {
    public:
        Sphere(std::string n = "Sphere", float radius = 1.0f, unsigned int rings = 12, unsigned int sectors = 24,
            Transform *t = new Transform());

        ~Sphere();


        virtual float *getVertices();
        virtual unsigned int *getTriangles();
        virtual int nbVertices();
        virtual int nbTriangles();

        virtual void createUI(char *ID);

        virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat, Light * light);

    // https://stackoverflow.com/questions/5988686/creating-a-3d-sphere-in-opengl-using-visual-c/5989676#5989676
    private:

        GLuint vertexArrayID;
        GLuint *buffers;

        Mesh *mesh;

        Material *material;

        void createVAO();
        void deleteVAO();

        void createMesh(float radius, unsigned int rings, unsigned int sectors);
        void setUniform(glm::mat4 viewMat, glm::mat4 projectionMat, Light* light);
};


#endif
