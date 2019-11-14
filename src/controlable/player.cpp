#include "player.h"

#include <imgui.h>

Player::Player(std::string name, Mesh *m, Material *mat){

    setName(name);
    mesh = m;
    material = mat;

}


Player::~Player(){
    
}

void Player::update(){

}

void Player::createUI(char *ID){
    MeshObject::createUI(ID);
}