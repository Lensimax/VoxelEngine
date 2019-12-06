
#ifndef VOXELGRID_H
#define VOXELGRID_H

#include "chunk.h"
#include "meshObject.h"
// #include <glm_display.h>

class VoxelGrid : public MeshObject {

public:
	VoxelGrid(){}
	VoxelGrid(int id, std::string n = "Voxel Grid", Transform *t = new Transform(), float size = 0.2f);
	~VoxelGrid();

	void setTransform(Transform * t);
	Transform* getTransform();

	// void update();

	void draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light) override;

	void createUI(char *ID) override;

	glm::ivec3 toChunkWorldPosition(const glm::vec3& worldPosition);

private:

	std::vector<Chunk> m_chunks;
	Chunk *m_chunk;
	
	float m_sizeCube;
	Transform * m_transform;

};


#endif