#include "player.h"

#include <imgui.h>

#include <iostream>

Player::Player(int id, std::string name, Transform *t, Mesh *m, Material *mat){

    setName(name);
    setID(id);
    mesh = m;
    material = mat;
    transform = t;

    glm::vec3 center = mesh->getCenter();
    t->setCenter(center);

    createVAO();

}


Player::~Player(){
    
}

void Player::update(){

    glm::vec3 pos = transform->getPosition();
    if(ImGui::IsKeyPressed('W')){
        pos.z -= speed;
    }
    if(ImGui::IsKeyPressed('S')){
        pos.z += speed;
    }
    if(ImGui::IsKeyPressed('A')){
        pos.x -= speed;
    }
    if(ImGui::IsKeyPressed('D')){
        pos.x += speed;
    }


    transform->setPosition(pos);   
}

void Player::createUI(char *ID){
    ImGui::BeginChild(ID);
    ImGui::Text(name.c_str()); ImGui::SameLine();
    ImGui::Text("id : %d", getID());
    ImGui::Separator();
    transform->createUI();


    ImGui::Separator();
    ImGui::Text("Player Speed: ");
    ImGui::DragFloat("##speed", &speed, 0.01f);  

    ImGui::Separator();
    bool node_material = ImGui::TreeNodeEx("Material", 0);
    if(node_material){
        material->createUI();
        ImGui::TreePop();
    }

    ImGui::EndChild();

}