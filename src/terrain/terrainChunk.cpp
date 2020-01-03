#include <cmath>

#include "terrainChunk.h"
#include "simplexNoise.h"

///////////////////////// Chunk

//// Constructors

TerrainChunk::TerrainChunk(size_t cubic_size, const glm::vec3& pos) : CubicArray<Voxel>(cubic_size), position(pos) {
	generate();
}

TerrainChunk::TerrainChunk(size_t cubic_size, float x, float y, float z) : TerrainChunk(cubic_size, glm::vec3(x, y, z)) {}

void TerrainChunk::generate()
{
	float scale = 100.f;
	size_t octaves = 8;

	SimplexNoise snoise(1.0f / scale);

	for(size_t i = 0 ; i < this->width() ; ++i) {
		for(size_t k = 0 ; k < this->depth() ; ++k) {
			
			// perlin_value in [0, 1]
			float perlin_value = (snoise.fractal(octaves,
				                  this->position.x * this->width() + i, 
				                  this->position.z * this->depth() + k) + 1.0) / 2.0;
			
			size_t max_y = std::round(perlin_value * this->cubic_size());

			// (*this)(i, max_y, k) = Voxel::Full;
			
			for (size_t j = 0 ; j < max_y ; ++j) // => active les voxel de 0 à Y 
			{
				(*this)(i, j, k) = Voxel::Full;
			}
		}
	}
}


std::array<bool, 6> TerrainChunk::surrounding(size_t x, size_t y, size_t z) const {

	std::array<bool, 6> activated_neighbors = {}; // Tout est faux

	if ( !(x == (this->width() - 1))  && (*this)(x + 1, y    , z    ) != Voxel::Empty) activated_neighbors[0] = true;
    if ( !(x == 0)                    && (*this)(x - 1, y    , z    ) != Voxel::Empty) activated_neighbors[1] = true;
    if ( !(y == (this->height() - 1)) && (*this)(x    , y + 1, z    ) != Voxel::Empty) activated_neighbors[2] = true;
    if ( !(y == 0)                    && (*this)(x    , y - 1, z    ) != Voxel::Empty) activated_neighbors[3] = true;
    if ( !(z == (this->depth() - 1))  && (*this)(x    , y    , z + 1) != Voxel::Empty) activated_neighbors[4] = true;
    if ( !(z == 0)                    && (*this)(x    , y    , z - 1) != Voxel::Empty) activated_neighbors[5] = true;

	return activated_neighbors;
}


void TerrainChunk::addCubeFaces(Mesh* mesh, const std::array<bool, 6>& surrounding, size_t x, size_t y, size_t z) const
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

Mesh* TerrainChunk::calculateMesh() const
{
	Mesh* mesh = new Mesh();

	for(size_t i = 0 ; i< this->width() ; i++) {
		for(size_t j = 0 ; j < this->height() ; j++) {
			for(size_t k = 0 ; k < this->depth() ; k++) {
				if ((*this)(i, j, k) != Voxel::Empty) // si le voxel est activé
				{
					this->addCubeFaces(mesh, this->surrounding(i, j, k), i, j, k);
				}
			}
		}
	}

	return mesh;
}

