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
    void addVertex(int i, glm::vec3 v);
    // virtual void computeNormals();
    virtual void computeCenter();
    virtual void computeRadius();

    void createMesh(float radius, unsigned int divs);

    void addFace(unsigned int v1, unsigned int v2, unsigned int v3);
    void addVertex(float x, float y, float z);

    int numFace, numVertex;


};



#endif
