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
    ImGuiIO& io = ImGui::GetIO();

    std::cout << "Update Player\n";
    glm::vec3 pos = transform->getPosition();
    if(ImGui::IsKeyPressed('H')){
        pos.z -= speed;
    }


    transform->setPosition(pos);   
}

void Player::createUI(char *ID){
    MeshObject::createUI(ID);

    ImGui::Separator();
    ImGui::Text("Player Speed: ");
    ImGui::DragFloat("near", &speed, 0.01f);  
}