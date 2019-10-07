
#ifndef MESH_OBJECT_H
#define MESH_OBJECT_H


#include <glm/mat4.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "../material/material.h"
#include "../material/lambertian.h"

#include "drawableObject.h"

#include <vector>

#include <string>

#include "cubeMesh.h"

#define POSITION_ATTRIB 0
#define VERTEX_NORMAL_ATTRIB 1

const std::string defaultFilename = "exampleModels/monkey.off";

class MeshObject : public DrawableObject {
    public:

        MeshObject(std::string n = "MeshObject", char *filename = (char*)defaultFilename.c_str(),Transform *t = new Transform(), Material *m = new Lambertian());
        ~MeshObject();


        virtual float *getVertices();
        virtual unsigned int *getTriangles();
        virtual int nbVertices();
        virtual int nbTriangles();

        virtual void createUI(char *ID);

        virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat, Light *light);


    protected:
        void createVAO();
        void deleteVAO();

        void setUniform(glm::mat4 viewMat, glm::mat4 projectionMat, Light* light);



        std::vector<float> vertices;
        std::vector<int> triangles;
        std::vector<float> normals;

        GLuint vertexArrayID;
        GLuint *buffers;

        Material *material;

        Mesh *mesh;

};


#endif
