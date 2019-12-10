#ifndef VOXELRENDERER_H
#define VOXELRENDERER_H

#include "meshRenderer.h"

#include "../models/chunk.h"

#include "../material/material.h"
#include "../models/mesh/meshCube.h"

class ChunkRenderer : public MeshRenderer {
public:

    ChunkRenderer();
    ~ChunkRenderer(){delete m_material;}

    void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light) override;

private:

    Chunk *m_chunk = NULL;
    
    MeshCube *m_mesh = NULL;

};


#endif