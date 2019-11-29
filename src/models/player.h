#ifndef PLAYER_H
#define PLAYER_H

#include "meshObject.h"
#include "mesh/meshCube.h"

class Player : public MeshObject {

public:
    Player(){}
    Player(int id, Transform *t = new Transform(), Mesh *m = new MeshCube(1.0f));

    ~Player();

    void update() override; 

private:


};

#endif