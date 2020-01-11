#ifndef COLLIDER_H
#define COLLIDER_H
#include "../rigidbody.h"

#include "../component.h"
#include "../../terrain/terrainManager.h"

#include "../../terrain/terrainChunk.h"


class Collider : public Renderer {
public:
    Collider(glm::vec3 box = glm::vec3(0.6f));
    ~Collider();

    void start() override;
    void physicsUpdate() override;
    void createUI() override;

    void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light) override;

    inline bool isGrounded(){return m_isGrounded;}
    inline void setTerrain(TerrainManager *terrain){m_terrain = terrain;}
private:
    void displayImGuiVoxel(Voxel voxel, const char message[]);
    bool intersect(glm::vec3 boxMin, glm::vec3 boxMax);
    bool intersect(glm::vec3 box1Min, glm::vec3 box1Max, glm::vec3 box2Min, glm::vec3 box2Max);
    bool intersectAccordingToMove(glm::vec3 boxMin, glm::vec3 boxMax);
    void updateCollidingBox();
    void computeCollisionWithGround();
    glm::vec3 computeCollision();
    void raycast();

    void drawAABB(glm::vec3 min, glm::vec3 max, Shader shader, glm::vec4 color = glm::vec4(1,0,0,1));

    TerrainManager *m_terrain = nullptr;

    glm::vec3 m_collidingBox;
    bool m_showCollidingBox, m_showCheckCollision;

    glm::vec3 m_boxMin, m_boxMax;

    Rigidbody *m_rb;

    glm::vec3 m_targetHitPoint;

    bool m_isGrounded;  
};

#endif