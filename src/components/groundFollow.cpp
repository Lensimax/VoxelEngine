#include "groundFollow.h"


GroundFollow::GroundFollow() : m_heightOffset(1.5f){
    setName("Ground Follow");
}

void GroundFollow::update(){
    if(m_terrain != nullptr){
        glm::vec3 position = m_gameobject->getTransform()->getPosition();
        
        float height = m_terrain->getHeightAt(position.x, position.z);
        
        if (position.y > height + m_heightOffset)
            position.y -= 1.0f;
        else
            position.y = height + m_heightOffset;
        

        m_gameobject->getTransform()->setPosition(position);
    }
}

void GroundFollow::createUI(){
    ImGui::Text("Height Offset : ");
    ImGui::DragFloat("##heightOffset", &m_heightOffset, 0.00f,0.01f, 1000.f); 
    ImGui::Text("height: %f", m_terrain->getHeightAt(m_gameobject->getTransform()->getPosition().x, m_gameobject->getTransform()->getPosition().z));
}