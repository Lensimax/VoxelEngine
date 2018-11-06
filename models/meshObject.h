
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

class MeshObject : public DrawableObject {
    public:

        MeshObject(std::string n = "MeshObject", const char *filename = "exampleModels/head.off",vec3 position = glm::vec3(0.0,0.0,0.0), vec3 scale = glm::vec3(1.0,1.0,1.0), vec3 rotation = glm::vec3(0.0,0.0,0.0));
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

        void computeNormals();
        void computeCenter();

        glm::vec3 getVertex(int i);


        std::vector<float> vertices;
        std::vector<int> triangles;
        std::vector<float> normals;

        GLuint vertexArrayID;
        GLuint *buffers;

        Material *material;

        glm::vec3 center;

};


#endif
