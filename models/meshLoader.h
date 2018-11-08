#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "mesh.h"

class MeshLoader : public Mesh {

    public:
        MeshLoader(const char*  filename);
        ~MeshLoader();


};


#endif
