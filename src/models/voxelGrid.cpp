#include "voxelGrid.h"


VoxelGrid::VoxelGrid(int id, std::string n, Transform *t, unsigned int size, float sizeCube){
	assert(sizeCube > 0.0f);
	setID(id);
	setName(n);

	sizeOfOneCube = sizeCube;
	sizeChunk = size;

	transform = t;
	mesh = new MeshCube(sizeOfOneCube);
	material = new Lambertian();


	createChunk();
}



VoxelGrid::~VoxelGrid(){

}


void VoxelGrid::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){


    glUseProgram(material->getShaderID());

    for(unsigned int i=0; i<chunk.size(); i++){
		/*for(unsigned int j=0; j<chunk[i].size(); j++){
			for(unsigned int k=0; k<chunk[i][j].size(); k++){

				glm::mat4 model = glm::translate(modelMat, glm::vec3(i*sizeOfOneCube, j*sizeOfOneCube, k*sizeOfOneCube));

			    setUniform(model, viewMat, projectionMat, light);

			    mesh->drawVAO();

			}
		}*/
		glm::mat4 model = glm::translate(modelMat, glm::vec3(i*sizeOfOneCube, 0, 0));

	    setUniform(model, viewMat, projectionMat, light);

	    mesh->drawVAO();
	}


    glUseProgram(0);


}


void VoxelGrid::createChunk(){
	chunk.resize(sizeChunk);
	for(unsigned int i=0; i<chunk.size(); i++){
		chunk[i].resize(sizeChunk);
		for(unsigned int j=0; j<chunk[i].size(); j++){
			chunk[i][j].resize(sizeChunk);
			for(unsigned int k=0; k<chunk[i][j].size(); k++){
				chunk[i][j][k] = true;
			}
		}
	}
}