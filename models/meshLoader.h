#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "mesh.h"

class MeshLoader : public Mesh {

    public:
        MeshLoader(char* filename);
        ~MeshLoader();

        void createUI() override;
    private:

        void createMesh(char *filename);

        char *currentFilename;
};


#endif
