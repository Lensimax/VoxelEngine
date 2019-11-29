#include "player.h"

#include "../material/material.h"

Player::Player(int id, Transform *t, Mesh *m){

    setID(id);
    setName("Player");

    transform = t;
    mesh = m;
    material = new Lambertian();
}



Player::~Player(){

}


void Player::update(){

}