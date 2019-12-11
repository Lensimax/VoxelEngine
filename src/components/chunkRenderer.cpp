#include "chunkRenderer.h"

#include "../material/lambertian.h"

#include <iostream>

ChunkRenderer::ChunkRenderer(){
    setName("Chunk Renderer");

    m_mesh = m_gameobject->getComponent<MeshCube*>();

    if(m_mesh != NULL){
        m_chunks = std::vector<Chunk>();
        Chunk c = Chunk(m_mesh->getVoxelSize());
        m_chunks.push_back(c);
    }

}

ChunkRenderer::~ChunkRenderer(){
    //delete m_chunk;
}


void ChunkRenderer::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){
    
    /// RECUPERATION DES COMPOSANTS
    if(m_material == NULL){
        m_material = m_gameobject->getComponent<Material*>();
        if(m_material == NULL){return;}
    }

    assert(m_material != NULL);

    if(m_mesh == NULL){
        m_mesh = m_gameobject->getComponent<MeshCube*>();
        if(m_mesh == NULL) {return;}

        m_chunks = std::vector<Chunk>();
        Chunk c = Chunk(m_mesh->getVoxelSize());
        m_chunks.push_back(c);
    }

    assert(m_mesh != NULL);


    // DESSIN DU CHUNK
    glUseProgram(m_material->getShaderID());

    glm::vec3 worldPosition = m_gameobject->getTransform()->getPosition();
    glm::vec3 chunkWorldPosition = toChunkWorldPosition(worldPosition);

    glm::vec3 chunkGridMinPosition = (chunkWorldPosition + glm::vec3(-1, 0, -1));



    /*size_t i = 0;
    for (size_t x = 0; x < m_chunks.size() / 3; x++)
    {
        for (size_t z = 0; z < m_chunks.size() / 3; z++)
        {
            // chunkWorldPositionOffset + glm::vec3(x, y, z);
            // std::cerr << chunkGridMinPosition + glm::vec3(x, 0, z) << ' ';
            std::cout << "Passe\n";
            glm::mat4 model = glm::translate(modelMat, (chunkGridMinPosition + glm::vec3(x, 0, z)) * glm::vec3(m_chunk->dimensions()));
            m_chunks[i].draw(model, viewMat, projectionMat, light, m_mesh, m_material);
            i++;
            // m_chunk->draw(model, viewMat, projectionMat, light, m_mesh, m_material);
        }
    }*/

    glUseProgram(0);
}


glm::ivec3 ChunkRenderer::toChunkWorldPosition(const glm::vec3& worldPosition) {

    glm::vec3 positionOffset(
        worldPosition.x < 0 ? worldPosition.x - 3 : worldPosition.x,
        worldPosition.y < 0 ? worldPosition.y - 3 : worldPosition.y,
        worldPosition.z < 0 ? worldPosition.z - 3 : worldPosition.z
    );

    return  glm::vec3(positionOffset) / glm::vec3(m_chunk->dimensions());
}
