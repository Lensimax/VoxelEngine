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
    void createVertices();
    void createFaces();

    void createMesh(float radius, unsigned int rings, unsigned int sectors);



};



#endif
