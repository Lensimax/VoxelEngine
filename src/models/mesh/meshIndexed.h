#ifndef MESHINDEXED_H
#define MESHINDEXED_H

#include <vector>

#include "mesh.h"

class MeshIndexed : public Mesh {
public:
    MeshIndexed(std::string filename = "../data/models/cube.obj");
    ~MeshIndexed();

    void createVAO() override;

    void drawVAO() override;

    void deleteVAO() override;

    void createUI() override;
    void recreate() override;



    void clear();

    unsigned int getNBFaces() override;

private:
    void createMeshFromFile(std::string filename);

    std::vector<unsigned int> m_indices;
    std::string m_filename;
};

#endif