#ifndef COLLIDER_H
#define COLLIDER_H

#include "../component.h"
#include "../../terrain/terrainManager.h"

#include "../../terrain/terrainChunk.h"


class Collider : public Renderer {
public:
    Collider(glm::vec3 box = glm::vec3(0.6f));
    ~Collider();

    void physicsUpdate() override;
    void createUI() override;

    void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light) override;

    inline bool isGrounded(){return m_bottom != Voxel::Empty;}
    inline void setTerrain(TerrainManager *terrain){m_terrain = terrain;}
private:
    void displayImGuiVoxel(Voxel voxel, const char message[]);
    bool intersect(glm::vec3 boxMin, glm::vec3 boxMax);

    TerrainManager *m_terrain = nullptr;

    glm::vec3 m_collidingBox;
    bool m_showCollidingBox;

    Voxel m_bottom, m_top, m_left, m_right, m_front, m_back;

    glm::vec3 m_boxMin, m_boxMax;
    
};

#endif