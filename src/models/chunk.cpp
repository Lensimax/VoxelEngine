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

bool Chunk::allNeighborsActivated(size_t x, size_t y, size_t z) const
{
	assert(x > 0 && y > 0 && z > 0 && "les indices doivent êtres plus grand que 0");
	assert(x < this->width() - 1 && y < this->height() - 1 && z < this->depth() - 1 && "les indices doivent êtres plus grand que 0");

	if (!(*this)(x + 1, y    , z    )) return false;
	if (!(*this)(x - 1, y    , z    )) return false;
	if (!(*this)(x    , y + 1, z    )) return false;
	if (!(*this)(x    , y - 1, z    )) return false;
	if (!(*this)(x    , y    , z + 1)) return false;
	if (!(*this)(x    , y    , z - 1)) return false;

	return true;
}


//// Drawing / OpenGL


void Chunk::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light, Mesh *mesh, Material *material) {

	// Dessin de l'interieur du chunk

	for(size_t i = 1 ; i< this->width() - 1 ; i++) {
		for(size_t j = 1 ; j < this->height() - 1 ; j++) {
			for(size_t k = 1 ; k < this->depth() - 1 ; k++) {
				if (!allNeighborsActivated(i, j, k)) {
					glm::mat4 model = glm::translate(modelMat, glm::vec3(i * this->voxelSize(), j * this->voxelSize(), k * this->voxelSize()));
			    	setUniform(model, viewMat, projectionMat, light, material);
			    	mesh->drawVAO();
				}
			}
		}
	}

	// Dessin des faces exterieures du chunk
	
	std::array<size_t, 2> i_borders = {0, (this->width() - 1)};

	for(size_t j = 0 ; j < this->height()  ; j++) {
		for(size_t k = 0 ; k < this->depth()  ; k++) {
			for (auto fixed_i : i_borders)
			{
				if ((*this)(fixed_i, j, k)) {
					glm::mat4 model = glm::translate(modelMat, glm::vec3(fixed_i * this->voxelSize(), j * this->voxelSize(), k * this->voxelSize()));
				   	setUniform(model, viewMat, projectionMat, light, material);
				   	mesh->drawVAO();
				}
			}
		}
	}

	std::array<size_t, 2> j_borders = {0, (this->height() - 1)};

	for(size_t i = 0 ; i < this->width()  ; i++) {
		for(size_t k = 0 ; k < this->depth()  ; k++) {
			for (auto fixed_j : j_borders)
			{
				if ((*this)(i, fixed_j, k)) {
					glm::mat4 model = glm::translate(modelMat, glm::vec3(i * this->voxelSize(), fixed_j * this->voxelSize(), k * this->voxelSize()));
				   	setUniform(model, viewMat, projectionMat, light, material);
				   	mesh->drawVAO();
				}
			}
		}
	}

	std::array<size_t, 2> k_borders = {0, (this->depth() - 1)};

	for(size_t i = 0 ; i < this->width()  ; i++) {
		for(size_t j = 0 ; j < this->height()  ; j++) {
			for (auto fixed_k : k_borders)
			{
				if ((*this)(i, j, fixed_k)) {
					glm::mat4 model = glm::translate(modelMat, glm::vec3(i * this->voxelSize(), j * this->voxelSize(), fixed_k * this->voxelSize()));
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