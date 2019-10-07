#ifndef CUBE_MESH_H
#define CUBE_MESH_H

#include "mesh.h"


#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>


class CubeMesh : public Mesh {

public:
    CubeMesh();
    ~CubeMesh();

private:
    void addVertex(int i, glm::vec3 v);
    void createVertices();
    void createFaces();

protected:
    virtual void computeNormals();
    // virtual void computeTangents();
    virtual void computeCenter();
    virtual void computeRadius();
    // virtual void computeUVCoord();

};



#endif
