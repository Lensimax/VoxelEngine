#ifndef FIREPROJECTILES_H
#define FIREPROJECTILES_H

#include "component.h"
#include "../engineClass/scene.h"
#include "../terrain/terrainManager.h"

class FireProjectiles : public Component {

public:
    FireProjectiles();
    ~FireProjectiles();

    void inputUpdate() override;
    void createUI() override;

    void setScene(Scene *scene){m_scene = scene;}
    void setTerrain(TerrainManager *terrain){m_terrain = terrain;}
private:
    glm::vec3 computeForward();
    void createProjectile();

    Scene *m_scene;
    float m_projectileSpeed;
    TerrainManager *m_terrain;

};


#endif