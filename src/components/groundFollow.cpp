#include "groundFollow.h"

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

GroundFollow::GroundFollow() : m_heightOffset(0.25f){
    setName("Ground Follow");
}

void GroundFollow::update(){
    if(m_terrain != nullptr){
        glm::vec3 position = m_gameobject->getTransform()->getPosition();
        position.y -= m_heightOffset;
        
        glm::vec3 bottomVoxelOffset(0, 1, 0);
        
        Voxel v = m_terrain->getVoxelAt(round(position));
        
        if (v == Voxel::Empty) {
            v = m_terrain->getVoxelAt(round(position - bottomVoxelOffset));

            if (v == Voxel::Empty){
                position.y = round(position.y - 1); 
            }
        }
        else{
            position.y = round(position.y + 1);
        }

        m_gameobject->getTransform()->setPosition(position + bottomVoxelOffset * m_heightOffset);
    }
}

void GroundFollow::createUI(){
    ImGui::Text("Height Offset : ");
    ImGui::DragFloat("##heightOffset", &m_heightOffset, 0.00f,0.01f, 1000.f); 
    ImGui::Text("height: %f", m_terrain->getHeightAt(m_gameobject->getTransform()->getPosition().x, m_gameobject->getTransform()->getPosition().z));
}