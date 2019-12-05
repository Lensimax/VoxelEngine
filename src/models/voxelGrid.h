
#ifndef VOXELGRID_H
#define VOXELGRID_H

#include "chunk.h"

#include "meshObject.h"

class VoxelGrid : public MeshObject {

public:
	VoxelGrid(){}
	VoxelGrid(int id, std::string n = "Voxel Grid", Transform *t = new Transform(), float size = 0.2f);
	~VoxelGrid();

	void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light) override;

	void createUI(char *ID) override;

private:


	Chunk *m_chunk;
	
	float m_sizeCube;

};


#endif