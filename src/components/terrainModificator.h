#ifndef TERRAIN_MODIFICATOR_H
#define TERRAIN_MODIFICATOR_H

#include "component.h"
#include "../terrain/terrainManager.h"

class TerrainModificator : public Component {
public:

    TerrainModificator();
    
    void inputUpdate() override;
    void createUI() override;

    void destroy(size_t radius);
    void setSphere(glm::vec3 position, size_t radius, Voxel v);

    void setTerrain(TerrainManager *terrain){m_terrain = terrain;}

private:

    TerrainManager *m_terrain = nullptr;
};


#endif