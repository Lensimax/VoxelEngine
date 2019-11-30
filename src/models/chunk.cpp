#include "chunk.h"
#include <iostream>


///////////////////////// CubicGrid


//// Accessors

template<class T, size_t N>
constexpr size_t CubicGrid<T, N>::width()  const {
	return N;
}

template<class T, size_t N>
constexpr size_t CubicGrid<T, N>::height() const {
	return N;
}

template<class T, size_t N>
constexpr size_t CubicGrid<T, N>::depth()  const {
	return N;
}


template<class T, size_t N>
T&       CubicGrid<T, N>::operator()(size_t x, size_t y, size_t z) {
	return (*this)[x + y * this->width() + z * this->width() * this->height()];
}

template<class T, size_t N>
const T& CubicGrid<T, N>::operator()(size_t x, size_t y, size_t z) const {
	return (*this)[x + y * this->width() + z * this->width() * this->height()];
}


//// Booleans


template<class T, size_t N>
bool CubicGrid<T, N>::on_bounds(size_t x, size_t y, size_t z) const {
	return x < this->width() && y < this->height() && z << this->depth();
}


///////////////////////// Chunk


//// Constructors


Chunk::Chunk(float voxelSize) : m_voxelSize(voxelSize) {
	for (auto& v : (*this))
		v = true;
}


//// Accessors


float Chunk::voxelSize() const {
	return m_voxelSize;
}


//// Drawing / OpenGL


void Chunk::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light, Mesh *mesh, Material *material) {

	for(unsigned int i = 0 ; i< this->width() ; i++) {
		for(unsigned int j = 0 ; j < this->height() ; j++) {
			for(unsigned int k = 0 ; k < this->depth() ; k++) {
				if ((*this)(i, j, k))
				{
					glm::mat4 model = glm::translate(modelMat, glm::vec3(i * this->voxelSize(), j * this->voxelSize(), k * this->voxelSize()));
			    	setUniform(model, viewMat, projectionMat, light, material);
			    	mesh->drawVAO();
				}
			}
		}
	}
}

void Chunk::setUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light* light, Material *material) {

    // glm::mat4 model = transform->getMat4(modelMat);
    // send the transformation matrix
    material->callUniform(modelMat, viewMat, projectionMat, light);
}