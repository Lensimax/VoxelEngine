#include "player.h"

#include <imgui.h>

#include "../material/material.h"

Player::Player(int id, Transform *t, Mesh *m, float sp) : m_speed(sp){

    setID(id);
    setName("Player");

    m_transform = t;
    m_mesh = m;
    m_material = new Lambertian();
}



Player::~Player(){
}



void Player::update(){
    EngineObject::update();
    m_mesh->update();

    glm::vec3 pos = m_transform->getPosition();
    if(ImGui::IsKeyPressed('W')){
        pos.z -= m_speed;
    }
    if(ImGui::IsKeyPressed('S')){
        pos.z += m_speed;
    }
    if(ImGui::IsKeyPressed('A')){
        pos.x -= m_speed;
    }
    if(ImGui::IsKeyPressed('D')){
        pos.x += m_speed;
    }

    m_transform->setPosition(pos); 


}


void Player::createUI(char *ID){
    const int node_flags = 0;

    ImGui::BeginChild(ID);
    ImGui::Text(m_name.c_str());

    ImGui::Separator();
    m_transform->createUI();


    ImGui::Separator();

    ImGui::Text("Speed : ");
    ImGui::DragFloat("##speed", &m_speed, 0.01f, 0.001f, 10000.0f, "%.3f");


    ImGui::Separator();
    bool node_mesh = ImGui::TreeNodeEx("Mesh", node_flags);
    if(node_mesh){
        m_mesh->createUI();
        if (ImGui::Button("Recreate")){
            m_mesh->recreate();
            
        }
        ImGui::Text("Show bounding box "); ImGui::SameLine();
        ImGui::Checkbox("##showboundingbox"+getID(),&m_showboundingbox);

        ImGui::TreePop();
    }

    ImGui::Separator();
    bool node_material = ImGui::TreeNodeEx("Material", node_flags);
    if(node_material){
        m_material->createUI();
        ImGui::TreePop();
    }
    ImGui::Separator();

	ImGui::EndChild();



}