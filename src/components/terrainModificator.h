#ifndef TERRAIN_MODIFICATOR_H
#define TERRAIN_MODIFICATOR_H

#include "component.h"
#include "../terrain/terrainManager.h"

class TerrainModificator : public Component {
public:

    TerrainModificator();

    void inputUpdate() override;
    // void update() override;
    void createUI() override;

    void setSphere(glm::vec3 position, size_t size, Voxel v);


    void setTerrain(TerrainManager *terrain){m_terrain = terrain;}

private:

    TerrainManager *m_terrain = nullptr;
};


#endif