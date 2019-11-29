#include "chunk.h"



Chunk::Chunk(float size){
    sizeOfOneCube = size;
    createChunk();
}



Chunk::~Chunk(){

}


void Chunk::createChunk(){
	for(unsigned int i=0; i<grid.size(); i++){
		for(unsigned int j=0; j<grid[i].size(); j++){
			for(unsigned int k=0; k<grid[i][j].size(); k++){
				grid[i][j][k] = true;
			}
		}
	}
}


void Chunk::setUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light* light, Material *material){

    // glm::mat4 model = transform->getMat4(modelMat);



    // send the transformation matrix
    material->callUniform(modelMat, viewMat, projectionMat, light);

}




void Chunk::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light, Mesh *mesh, Material *material){


     for(unsigned int i=0; i<grid.size(); i++){
		for(unsigned int j=0; j<grid[i].size(); j++){
			for(unsigned int k=0; k<grid[i][j].size(); k++){

				glm::mat4 model = glm::translate(modelMat, glm::vec3(i*sizeOfOneCube, j*sizeOfOneCube, k*sizeOfOneCube));

			    setUniform(model, viewMat, projectionMat, light, material);

			    mesh->drawVAO();

			}
		}

	}


}

bool Chunk::getCell(unsigned int i, unsigned int j, unsigned int k){
    return grid[i][j][k];
}