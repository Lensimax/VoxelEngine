#ifndef VOXELRENDERER_H
#define VOXELRENDERER_H

#include "meshRenderer.h"

class VoxelRenderer : public MeshRenderer {
public:

    VoxelRenderer(){m_material = new Lambertian();}
    ~VoxelRenderer(){delete m_material;}

private:

};


#endif