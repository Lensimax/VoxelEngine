#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "mesh.h"

class MeshLoader : public Mesh {

    public:
        MeshLoader(char* filename);
        ~MeshLoader();


        void recreate() override;
        void createUI() override;
    private:

        void createMesh(char *filename);
        void cleanup();

        char currentFilename[1024];
};


#endif
