#ifndef GROUNDFOLLOW_H
#define GROUNDFOLLOW_H

#include "component.h"
#include "../terrain/terrainManager.h"

class GroundFollow : public Component {
public:

    GroundFollow();

    void update() override;
    void createUI() override;

    void setTerrain(TerrainManager *terrain){m_terrain = terrain;}

private:

    TerrainManager *m_terrain = nullptr;
    float m_heightOffset;

};


#endif