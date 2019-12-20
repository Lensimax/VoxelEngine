#include "chunkRenderer.h"

#include "../material/lambertian.h"

#include <iostream>

ChunkRenderer::ChunkRenderer(){
    setName("Chunk Renderer");

    m_mesh = new MeshCube();
    m_mesh->clear();
    //m_gameobject->Component<MeshCube*>();

    if(m_mesh){
        m_chunks = std::vector<Chunk>();
        Chunk c(1.0f, 0, 0, 0);
        m_chunks.emplace_back(c);

        c.calculateMesh(m_mesh);
        m_mesh->createVAO();
        // m_chunk = new Chunk(1.0f, 0, 0, 0);
    }
}

ChunkRenderer::~ChunkRenderer(){
    //delete m_chunk;
}


void ChunkRenderer::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){
    if(!m_active){
        return;
    }
// std::cerr << "dessin construction\n";
    /// RECUPERATION DES COMPOSANTS
    if(!m_material){
        m_material = m_gameobject->getComponent<Material*>();
        if(!m_material){return;}
    }

    assert(m_material);

    if(!m_mesh){
        m_mesh = m_gameobject->getComponent<MeshCube*>();
        if(!m_mesh) {return;}

        m_chunks = std::vector<Chunk>();
        Chunk c = Chunk(m_mesh->getVoxelSize());
        m_chunks.push_back(c);
    }

    assert(m_mesh);

    // DESSIN DU CHUNK
    glUseProgram(m_material->getShaderID());

    // glm::vec3 worldPosition = m_gameobject->getTransform()->getPosition();
    // glm::vec3 chunkWorldPosition = toChunkWorldPosition(worldPosition);

    // glm::vec3 chunkGridMinPosition = (chunkWorldPosition + glm::vec3(-1, 0, -1));


    m_chunks.front().draw(modelMat, viewMat, projectionMat, light, m_mesh, m_material);


    glUseProgram(0);
}


glm::ivec3 ChunkRenderer::toChunkWorldPosition(const glm::vec3& worldPosition) {

    glm::vec3 positionOffset(
        worldPosition.x < 0 ? worldPosition.x - 3 : worldPosition.x,
        worldPosition.y < 0 ? worldPosition.y - 3 : worldPosition.y,
        worldPosition.z < 0 ? worldPosition.z - 3 : worldPosition.z
    );

    return  glm::vec3(positionOffset) / glm::vec3(m_chunks.front().dimensions());
}
