
#ifndef MESH_OBJECT_H
#define MESH_OBJECT_H

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include "../material/lambertian.h"

#include "mesh/mesh.h"
#include "mesh/meshCube.h"
#include "drawableObject.h"

#include <vector>

#include <string>



class MeshObject : public DrawableObject {
    public:
        MeshObject();
        MeshObject(int id, std::string n = "Mesh Object", Transform *t = new Transform(), Mesh *m = new MeshCube(1.0f), Material *mat = new Lambertian());
        ~MeshObject();


        /*virtual float *getVertices();
        virtual unsigned int *getTriangles();*/
        int nbVertices() override;
        int nbTriangles() override;

        void createUI(char *ID);

        void update();

        void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light) override;


    protected:

        void setUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light* light);

        void drawBoxWithMatricess(glm::vec3 min, glm::vec3 max, glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat);


        Material *m_material;

        bool m_showboundingbox = false;

        Mesh *m_mesh;

};


#endif
