#ifndef GROUNDFOLLOW_H
#define GROUNDFOLLOW_H

#include "component.h"
#include "chunkRenderer.h"

class GroundFollow : public Component {
public:

    GroundFollow();
    ~GroundFollow();

    void update() override;
    void createUI() override;

    void setTerrain(ChunkRenderer *terrain){m_terrain = terrain;}

private:

    ChunkRenderer *m_terrain;
    float m_heightOffset;

};


#endif