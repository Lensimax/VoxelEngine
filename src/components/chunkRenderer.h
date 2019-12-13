#ifndef VOXELRENDERER_H
#define VOXELRENDERER_H

#include "meshRenderer.h"

#include "../models/chunk.h"

#include "../material/material.h"
#include "../models/mesh/meshCube.h"

class ChunkRenderer : public MeshRenderer {
public:

    ChunkRenderer();
    ~ChunkRenderer();

    void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light) override;

    glm::ivec3 toChunkWorldPosition(const glm::vec3& worldPosition);

    void setPlayerTransform(Transform *player){m_playerTransform = player;}
    Transform * getPlayerTransform(){return m_playerTransform;}

private:
    std::vector<Chunk> m_chunks;
    // Chunk *m_chunk = NULL;
    
    MeshCube *m_mesh = nullptr;

    Transform *m_playerTransform;

};


#endif