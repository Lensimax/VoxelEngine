#ifndef PLAYER_H
#define PLAYER_H

#include "meshObject.h"
#include "mesh/meshCube.h"

class Player : public MeshObject {

public:
    Player(){}
    Player(int id, Transform *t = new Transform(), Mesh *m = new MeshCube(1.0f), float speed = 0.2f);

    ~Player();

    void createUI(char *ID) override;

    void update() override;

private:

    float m_speed = 0.2f;


    
};

#endif