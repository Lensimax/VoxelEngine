#ifndef COLLIDER_H
#define COLLIDER_H

#include "../component.h"
#include "../../terrain/terrainManager.h"

#include "../../terrain/terrainChunk.h"


class Collider : public Component {
public:
    Collider(glm::vec3 box = glm::vec3(0.6f));
    ~Collider();

    void update() override;
    void createUI() override;

    inline bool isGrounded(){return m_bottom != Voxel::Empty;}
    inline void setTerrain(TerrainManager *terrain){m_terrain = terrain;}
private:
    void displayImGuiVoxel(Voxel voxel, const char message[]);

    TerrainManager *m_terrain = nullptr;

    glm::vec3 m_collidingBox;
    bool m_showCollidingBox;

    Voxel m_bottom, m_top, m_left, m_right, m_front, m_back;
    
};

#endif