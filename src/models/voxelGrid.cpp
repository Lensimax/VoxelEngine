#include "voxelGrid.h"


VoxelGrid::VoxelGrid(int id, std::string n, Transform *t, float sizeCube){
	assert(sizeCube > 0.0f);
	setID(id);
	setName(n);

	this->sizeCube = sizeCube;

	transform = t;
	mesh = new MeshCube(sizeCube);
	material = new Lambertian();

	chunk = new Chunk(sizeCube);
}



VoxelGrid::~VoxelGrid(){
	delete chunk;
}


void VoxelGrid::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){


    glUseProgram(material->getShaderID());

	chunk->draw(modelMat, viewMat, projectionMat, light, mesh, material);

    glUseProgram(0);


}

