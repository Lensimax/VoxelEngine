
#ifndef MESH_OBJECT_H
#define MESH_OBJECT_H

#ifndef GLM_H
#define GLM_H
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#endif

#include "../material/material.h"

#include "drawableObject.h"

#include <vector>

#include <string>

#include "cubeMesh.h"

class MeshObject : public DrawableObject {
    public:

        MeshObject(std::string n = "MeshObject", char *filename = "exampleModels/head.off",vec3 position = glm::vec3(0.0,0.0,0.0), vec3 scale = glm::vec3(1.0,1.0,1.0), vec3 rotation = glm::vec3(0.0,0.0,0.0));
        ~MeshObject();


        virtual float *getVertices();
        virtual int *getTriangles();
        virtual int nbVertices();
        virtual int nbTriangles();

        virtual void createUI(char *ID);

        virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat, glm::vec3 light = glm::vec3(0.0,0.0,0.0));


    private:
        void createVAO();
        void deleteVAO();

        void setUniform(glm::mat4 viewMat, glm::mat4 projectionMat, glm::vec3 light);

        void createMesh(const char *filename);


        std::vector<float> vertices;
        std::vector<int> triangles;

        GLuint vertexArrayID;
        GLuint *buffers;

        Material *material;

        Mesh *mesh;

};


#endif
