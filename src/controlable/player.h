#ifndef PLAYER_H
#define PLAYER_H

#include "../models/meshObject.h"
#include "../models/meshLoader.h"

class Player : public MeshObject {

public:
    Player(std::string name = "Player", Mesh *m = new MeshLoader("../data/models/sphere.off"), Material *mat = new Lambertian());
    ~Player();

    void update();

    void createUI(char *ID);

private:

    float distanceFromTerrain = 0.1f;
    Mesh *mesh;
    Material *material;

};



#endif