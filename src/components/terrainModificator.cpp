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

void TerrainModificator::destroy(size_t radius)
{
    setSphere(m_gameobject->getTransform()->getPosition(), radius, Voxel::Empty);
}

void TerrainModificator::setSphere(glm::vec3 world_coord, size_t radius, Voxel v) {
    glm::vec3 min_coord = world_coord - glm::vec3(radius);

    for(size_t i = 0 ; i < m_terrain->getChunkSize() ; i++) {
        for(size_t j = 0 ; j < m_terrain->getChunkSize() ; j++) {
            for(size_t k = 0 ; k < m_terrain->getChunkSize() ; k++) {

                glm::vec3 current_coord = min_coord + glm::vec3(i, j, k);

                if (glm::distance(world_coord, current_coord) <= radius)
                    m_terrain->setVoxelAt(min_coord + glm::vec3(i, j, k), v);
            }
        }
    }
}

void TerrainModificator::inputUpdate(){

    glm::vec3 pos = m_gameobject->getTransform()->getPosition();

    if(ImGui::IsKeyPressed('O'))
        setSphere(pos, 10, Voxel::Empty);
    else if (ImGui::IsKeyPressed('U'))
        setSphere(pos, 10, Voxel::Full);
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