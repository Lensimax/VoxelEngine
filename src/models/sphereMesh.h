#ifndef SPHERE_MESH_H
#define SPHERE_MESH_H

#include "mesh.h"

#ifndef GLM_H
#define GLM_H
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#endif

class SphereMesh : public Mesh {

public:
    SphereMesh(float radius = 1.0f, unsigned int rings = 12, unsigned int sectors = 24);
    ~SphereMesh();


private:

    virtual void computeCenter();
    virtual void computeRadius();

    void subdivide();

    void createMesh(float radius, unsigned int divs);
    glm::vec3 getVertex(int index);

    void addFace(unsigned int v1, unsigned int v2, unsigned int v3);
    void addVertex(float x, float y, float z);
    void addVertex(int i, glm::vec3 v);

    int numFace, numVertex;


};



#endif
