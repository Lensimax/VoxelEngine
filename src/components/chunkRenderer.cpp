#include "chunkRenderer.h"

#include "../material/lambertian.h"

#include <iostream>

ChunkRenderer::ChunkRenderer(){
    m_material = new Lambertian();

    m_mesh = m_gameobject->getComponent<MeshCube*>();

    if(m_mesh != NULL){
        m_chunk = new Chunk(m_mesh->getVoxelSize());
    }

}


void ChunkRenderer::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){

    
    if(m_mesh == NULL){
        m_mesh = m_gameobject->getComponent<MeshCube*>();
        if(m_mesh == NULL) {return;}
        m_chunk = new Chunk(m_mesh->getVoxelSize());
    }

    glUseProgram(m_material->getShaderID());

	m_chunk->draw(modelMat, viewMat, projectionMat, light, m_mesh, m_material);

    glUseProgram(0);


}