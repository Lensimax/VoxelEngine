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

        void cleanup();
        void readOFFfile(char *filename);

        char currentFilename[1024];
        char backupFilename[1024];
};


#endif
