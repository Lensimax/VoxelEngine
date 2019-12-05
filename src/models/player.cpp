#include "player.h"

#include <imgui.h>

#include "../material/material.h"

Player::Player(int id, Transform *t, Mesh *m, float sp) : m_speed(sp){

    setID(id);
    setName("Player");

    transform = t;
    mesh = m;
    material = new Lambertian();
}



Player::~Player(){
}



void Player::update(){
    EngineObject::update();
    mesh->update();

    glm::vec3 pos = transform->getPosition();
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

    transform->setPosition(pos); 


}


void Player::createUI(char *ID){
    const int node_flags = 0;

    ImGui::BeginChild(ID);
    ImGui::Text(name.c_str());

    ImGui::Separator();
    transform->createUI();


    ImGui::Separator();

    ImGui::Text("Speed : ");
    ImGui::DragFloat("##speed", &m_speed, 0.01f, 0.001f, 10000.0f, "%.3f");


    ImGui::Separator();
    bool node_mesh = ImGui::TreeNodeEx("Mesh", node_flags);
    if(node_mesh){
        mesh->createUI();
        if (ImGui::Button("Recreate")){
            mesh->recreate();
            
        }
        ImGui::Text("Show bounding box "); ImGui::SameLine();
        ImGui::Checkbox("##showboundingbox"+getID(),&showboundingbox);

        ImGui::TreePop();
    }

    ImGui::Separator();
    bool node_material = ImGui::TreeNodeEx("Material", node_flags);
    if(node_material){
        material->createUI();
        ImGui::TreePop();
    }
    ImGui::Separator();

	ImGui::EndChild();



}