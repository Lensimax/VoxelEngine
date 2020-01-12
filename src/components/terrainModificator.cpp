#include "terrainModificator.h"

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

TerrainModificator::TerrainModificator(){
    setName("Terrain Modificator");
}

void TerrainModificator::start(){
    // assert(m_terrain != nullptr);
}


void TerrainModificator::destroy(glm::vec3 position, size_t size) {

    glm::vec3 world_coord = m_gameobject->getTransform()->getPosition();
    glm::vec3 min_coord = world_coord - (glm::vec3(size) / glm::vec3(2.0));


    for(size_t i = 0 ; i < size ; i++) {
        for(size_t j = 0 ; j < size ; j++) {
            for(size_t k = 0 ; k < size ; k++) {
                m_terrain->setVoxelAt(min_coord + glm::vec3(i, j, k), Voxel::Empty);
            }
        }
    }
}


void TerrainModificator::inputUpdate(){

    glm::vec3 pos = m_gameobject->getTransform()->getPosition();

    if(ImGui::IsKeyPressed('O')){
        destroy(pos, 10);
        // glm::vec3 deletePos = pos;
        // pos.y -= 1;
        
        // if (m_terrain->getVoxelAt(deletePos) != Voxel::Empty)
        // {
        //     m_terrain->setVoxelAt(deletePos, Voxel::Empty);
        //     m_terrain->updateChunkAt(deletePos);
        // }
    }
}

void TerrainModificator::createUI(){
    // ImGui::Text("Height Offset : ");
    glm::vec3 world_pos =  m_gameobject->getTransform()->getPosition();
    glm::ivec3 chunk_grid_pos = m_terrain->toChunkGridCoord(world_pos);
    glm::ivec3 voxel_coord    = m_terrain->toVoxelCoord(world_pos);
    glm::ivec3 voxel_delete   = m_terrain->toVoxelCoord(glm::vec3(world_pos.x, world_pos.y-1, world_pos.z));

    ImGui::InputInt3("Player Chunk Pos : ", &chunk_grid_pos.x);
    ImGui::InputInt3("Player Voxel Pos : ", &voxel_coord.x);
    ImGui::InputInt3("Delete Voxel Pos : ", &voxel_delete.x);
}