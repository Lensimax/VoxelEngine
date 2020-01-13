#ifndef TERRAIN_MODIFICATOR_H
#define TERRAIN_MODIFICATOR_H

#include "component.h"
#include "../terrain/terrainManager.h"

class TerrainModificator : public Component {
public:

    TerrainModificator();
    
    void createUI() override;

    void destroy(size_t radius);


    void setTerrain(TerrainManager *terrain){m_terrain = terrain;}

private:

    TerrainManager *m_terrain = nullptr;
};


#endif