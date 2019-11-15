
#ifndef MESH_OBJECT_H
#define MESH_OBJECT_H

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include "../material/lambertian.h"

#include "mesh.h"
#include "meshLoader.h"
#include "drawableObject.h"

#include <vector>

#include <string>



class MeshObject : public DrawableObject {
    public:
        MeshObject();
        MeshObject(int id, std::string n = "Mesh Object", Mesh *m = new MeshLoader("../data/models/monkey.off"),  Transform *t = new Transform(), Material *mat = new Lambertian());
        ~MeshObject();


        /*virtual float *getVertices();
        virtual unsigned int *getTriangles();*/
        int nbVertices() override;
        int nbTriangles() override;

        void createUI(char *ID);

        void update();

        void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light) override;


    protected:
        void createVAO();
        void deleteVAO();

        void setUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light* light);

        void drawBoxWithMatricess(glm::vec3 min, glm::vec3 max, glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat);
        GLuint vertexArrayID;
        GLuint *buffers;

        Material *material;

        bool showboundingbox = false;

        Mesh *mesh;

};


#endif
