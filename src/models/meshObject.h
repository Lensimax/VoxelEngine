
#ifndef MESH_OBJECT_H
#define MESH_OBJECT_H

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

// #include "../material/material.h"
#include "../material/lambertian.h"

#include "mesh.h"
#include "drawableObject.h"

#include <vector>

#include <string>

// #include "cubeMesh.h"



class MeshObject : public DrawableObject {
    public:

        virtual ~MeshObject() = default;;


        /*virtual float *getVertices();
        virtual unsigned int *getTriangles();*/
        int nbVertices() override;
        int nbTriangles() override;

        void createUI(char *ID);

        void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light) override;


    protected:
        void createVAO();
        void deleteVAO();

        void setUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light* light);


        GLuint vertexArrayID;
        GLuint *buffers;

        Material *material;

        Mesh *mesh;

};


#endif
