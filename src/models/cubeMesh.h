#ifndef CUBE_MESH_H
#define CUBE_MESH_H

#include "mesh.h"

#ifndef GLM_H
#define GLM_H
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#endif

class CubeMesh : public Mesh {

public:
    CubeMesh();
    ~CubeMesh();

private:
    void addVertex(int i, glm::vec3 v);
    void createVertices();
    void createFaces();

};



#endif
