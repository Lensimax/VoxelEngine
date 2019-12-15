#include "chunk.h"
#include "simplexNoise.h"

#include <iostream>
#include <cmath>
// #include <glm_display.h>


//(0 -> 255)
float normalize(float value, float old_max, float new_max)
{
	return (value * new_max) / old_max;
}

// float reduced_values(float value, size_t desired_nb_values, size_t current_nb_values = 256)
// float cut_in(float value, size_t nb_cuts, size_t nb_values = 256)
// {
// 	float offset = float(nb_values) / float(nb_cuts);

// 	return std::round(value / nb_cuts) * offset;
// }


///////////////////////// Voxel

//// Constructors

Voxel::Voxel() : type(Voxel::Type::Empty) {}

Voxel::Voxel(Voxel::Type type) : type(type) {}

//// Cast operators

Voxel::operator bool() const {
	return this->type != Voxel::Type::Empty;
}

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
constexpr size_t  CubicGrid<T, N>::borderSize() const {
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
		v = Voxel::Type::Empty;
}

Chunk::Chunk(float voxelSize, float x, float y, float z) : m_voxelSize(voxelSize) {
	generateTerrain(x, y, z);
}

void Chunk::generateTerrain(float x, float y, float z)
{
	float scale = 100.f;
	size_t octaves = 8;

	SimplexNoise snoise(1.0f / scale);

	for(size_t i = 0 ; i < this->width() ; ++i) {
		for(size_t k = 0 ; k < this->depth() ; ++k) {
			
			float v = (snoise.fractal(octaves, float(i) + float(x) * float(this->width()), float(k) + float(z) * float(this->depth())) + 1.0) * (255.0 / 2.0);
			
			float max_y = std::round(normalize(v, 255, this->borderSize() -1));

			// (*this)(i, max_y, k) = Voxel::Type::Full;
			
			for (size_t j = 0 ; j != max_y + 1 ; ++j) // => active les voxel de 0 à Y 
			{
				(*this)(i, j, k) = Voxel::Type::Full;
				// std::cerr << "Voxel : " << glm::vec3(i, j, k) << '\n';
			}
		}
	}
}


//// Accessors


float Chunk::voxelSize() const {
	return m_voxelSize;
}



glm::uvec3 Chunk::dimensions() const {
	return glm::uvec3(
        this->width()  * this->voxelSize(),
        this->height() * this->voxelSize(),
        this->depth()  * this->voxelSize()
    );
}

bool Chunk::surrounded(size_t x, size_t y, size_t z) const
{
	// assert(x > 0 && y > 0 && z > 0 && "les indices doivent êtres plus grand que 0");
	// assert(x < this->width() - 1 && y < this->height() - 1 && z < this->depth() - 1 && "les indices doivent êtres inferieurs à 15");

	return !( (x == 0 || y == 0 || z == 0) ||
              (x == this->width() - 1 || y == this->height() - 1 || z == this->depth() - 1) ||
              (!(*this)(x + 1, y    , z    )) ||
              (!(*this)(x - 1, y    , z    )) ||
              (!(*this)(x    , y + 1, z    )) ||
              (!(*this)(x    , y - 1, z    )) ||
              (!(*this)(x    , y    , z + 1)) ||
              (!(*this)(x    , y    , z - 1)) );
}

std::array<bool, 6> Chunk::surrounding(size_t x, size_t y, size_t z) const {

	std::array<bool, 6> activated_neighbors = {}; // Tout est faux

	if ( !(x == (this->width() - 1))  && (*this)(x + 1, y    , z    ) ) activated_neighbors[0] = true;
    if ( !(x == 0)                    && (*this)(x - 1, y    , z    ) ) activated_neighbors[1] = true;
    if ( !(y == (this->height() - 1)) && (*this)(x    , y + 1, z    ) ) activated_neighbors[2] = true;
    if ( !(y == 0)                    && (*this)(x    , y - 1, z    ) ) activated_neighbors[3] = true;
    if ( !(z == (this->depth() - 1))  && (*this)(x    , y    , z + 1) ) activated_neighbors[4] = true;
    if ( !(z == 0)                    && (*this)(x    , y    , z - 1) ) activated_neighbors[5] = true;

	return activated_neighbors;
}


void Chunk::addCubeFaces(Mesh* mesh, const std::array<bool, 6>& surrounding, size_t x, size_t y, size_t z) const
{
	// std::cerr << "addCube" << glm::vec3(x, y, z) << '\n';

	glm::vec3 color(0.0, 1.0, 0.0);
	// glm::vec3 normal(0, 0, 0);

	// XPlus
	if (!surrounding[0])
	{
		glm::vec3 v1(x + 1, y    , z);
		glm::vec3 v2(x + 1, y + 1, z);
		glm::vec3 v3(x + 1, y    , z + 1);
		glm::vec3 v4(x + 1, y + 1, z + 1);

		// glm::vec3 normal = glm::cross((v2 - v1), (v3 - v1));
		
		mesh->addQuad(v1, v2, v3, v4, glm::vec3(1, 0, 0), color); // multiply by voxel_size if != 1.0f
	}

	// XMinus
	if (!surrounding[1])
	{
		glm::vec3 v1(x, y    , z);
		glm::vec3 v2(x, y + 1, z);
		glm::vec3 v3(x, y    , z + 1);
		glm::vec3 v4(x, y + 1, z + 1);

		// glm::vec3 normal = glm::cross((v3 - v1), (v2 - v1));
		
		mesh->addQuad(v1, v3, v2, v4, glm::vec3(-1, 0, 0), color); // multiply by voxel_size if != 1.0f
	}

	// YPlus
	if (!surrounding[2])
	{
		glm::vec3 v1(x    , y + 1, z);
		glm::vec3 v2(x + 1, y + 1, z);
		glm::vec3 v3(x    , y + 1, z + 1);
		glm::vec3 v4(x + 1, y + 1, z + 1);

		// glm::vec3 normal = glm::cross((v2 - v1), (v3 - v1));
		
		mesh->addQuad(v1, v3, v2, v4, glm::vec3(0, 1, 0), color); // multiply by voxel_size if != 1.0f
	}

	// YMinus
	if (!surrounding[3])
	{
		glm::vec3 v1(x    , y, z);
		glm::vec3 v2(x + 1, y, z);
		glm::vec3 v3(x    , y, z + 1);
		glm::vec3 v4(x + 1, y, z + 1);

		// glm::vec3 normal = glm::cross((v3 - v1), (v2 - v1));
		
		mesh->addQuad(v1, v2, v3, v4, glm::vec3(0, -1, 0), color); // multiply by voxel_size if != 1.0f
	}

	// ZPlus
	if (!surrounding[4])
	{
		glm::vec3 v1(x    , y    , z + 1);
		glm::vec3 v2(x + 1, y    , z + 1);
		glm::vec3 v3(x    , y + 1, z + 1);
		glm::vec3 v4(x + 1, y + 1, z + 1);

		// glm::vec3 normal = -glm::cross((v2 - v1), (v3 - v1));
		
		mesh->addQuad(v1, v2, v3, v4, glm::vec3(0, 0, 1), color); // multiply by voxel_size if != 1.0f
	}

	// ZMinus
	if (!surrounding[5])
	{
		glm::vec3 v1(x    , y    , z);
		glm::vec3 v2(x + 1, y    , z);
		glm::vec3 v3(x    , y + 1, z);
		glm::vec3 v4(x + 1, y + 1, z);

		// glm::vec3 normal = glm::cross((v3 - v1), (v2 - v1));
		
		mesh->addQuad(v1, v3, v2, v4, glm::vec3(0, 0, -1), color); // multiply by voxel_size if != 1.0f
	}
}

void Chunk::calculateMesh(Mesh* mesh) const
{
	for(size_t i = 0 ; i< this->width() ; i++) {
		for(size_t j = 0 ; j < this->height() ; j++) {
			for(size_t k = 0 ; k < this->depth() ; k++) {
				if ((*this)(i, j, k)) // si le voxel est activé
				{
					// std::array<bool, 6> surrounding{};
				// std::fill(surrounding.begin(), surrounding.end(), false);
					this->addCubeFaces(mesh, this->surrounding(i, j, k), i, j, k);
					 // 
				}
			}
		}
	}
}

//// Drawing / OpenGL

void Chunk::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light, Mesh *mesh, Material *material) {

	// Dessin de l'interieur du chunk (Affiche seulement si tout les voisins ne sont pas activées)

	// for(size_t i = 0 ; i< this->width() ; i++) {
	// 	for(size_t j = 0 ; j < this->height() ; j++) {
	// 		for(size_t k = 0 ; k < this->depth() ; k++) {
	// 			if ((*this)(i, j, k) && !this->sourounded(i, j, k))
	// 			{
					// glm::mat4 model = glm::translate(modelMat, glm::vec3(i * this->voxelSize(), j * this->voxelSize(), k * this->voxelSize()));
		    		setUniform(modelMat, viewMat, projectionMat, light, material);
		    		mesh->drawVAO();
		// 		}
		// 	}
		// }
	// }

	// A garder pour du debugage plus tard

	// Dessin des faces exterieures du chunk (Affiche seulement le si voxel est activé)
	/*
	std::array<size_t, 2> i_borders = {0, (this->width() - 1)};

	for(size_t j = 0 ; j < this->height()  ; j++) {
		for(size_t k = 0 ; k < this->depth()  ; k++) {
			for (auto fixed_i : i_borders)
			{
				if ((*this)(fixed_i, j, k)) {
					glm::mat4 model = glm::translate(modelMat, glm::vec3(fixed_i * this->voxelSize(), j * this->voxelSize(), k * this->voxelSize()));
				   	setUniform(model, viewMat, projectionMat, light, material);
				   	m_mesh->drawVAO();
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
				   	m_mesh->drawVAO();
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
				   	m_mesh->drawVAO();
				}
			}
		}
	}
	*/
}

void Chunk::setUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light* light, Material *material) {

    // glm::mat4 model = transform->getMat4(modelMat);
    // send the transformation matrix
    material->callUniform(modelMat, viewMat, projectionMat, light);
}