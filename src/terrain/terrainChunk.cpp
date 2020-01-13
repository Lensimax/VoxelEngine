#include <cmath>

#include "terrainChunk.h"
#include "simplexNoise.h"
#include "terrainManager.h"

///////////////////////// Chunk

//// Constructors

// float TerrainChunk::m_frequency = 0.008f;
// size_t TerrainChunk::nbOctaves = 4;
float TerrainChunk::m_frequency = 0.01f;
size_t TerrainChunk::nbOctaves = 3;


TerrainChunk::TerrainChunk(size_t cubic_size) : voxels(cubic_size) {
	setName("TerrainChunk");
}

void TerrainChunk::start() {
	assert(m_gameobject != nullptr);

	renderer = m_gameobject->getComponent<MeshRenderer*>();
	
	assert(renderer != nullptr);
	
	generate();

	// calculateMesh();

	// renderer->mesh->createVAO();
}

// TerrainChunk::TerrainChunk(size_t cubic_size, float x, float y, float z) : TerrainChunk(cubic_size, glm::vec3(x, y, z)) {}

void TerrainChunk::generate() {
	glm::vec3 position = m_gameobject->getTransform()->getPosition();
	// std::cerr << position.x << ','<< position.y << ',' << position.z << '\n';

	for(size_t i = 0 ; i < voxels.width() ; ++i) {
		for(size_t k = 0 ; k < voxels.depth() ; ++k) {
			
			// perlin_value in [0, 1]
			// float perlin_value = (snoise.fractal(octaves,
				                  // position.x + i, 
				                  // position.z + k) + 1.0) / 2.0;
			// 
			// size_t max_y = std::round(perlin_value * voxels.cubic_size());
			size_t max_y = getHeightAt(voxels.cubic_size(), position.x + i, position.z + k);
// 
			// voxels(i, max_y, k) = Voxel::Full;

			// if (max_y > 0)
				// voxels(i, max_y - 1, k) = Voxel::Full;
			
			for (size_t j = 0 ; j < max_y ; ++j) // => active les voxel de 0 à Y 
			{
				voxels(i, j, k) = Voxel::Full;
			}
		}
	}
}


std::array<bool, 6> TerrainChunk::surrounding(size_t x, size_t y, size_t z) const {

	std::array<bool, 6> activated_neighbors = {}; // Tout est faux
	glm::vec3 pos = m_gameobject->getTransform()->getPosition();

	if ( (!(x == (voxels.width() - 1))  && (voxels(x + 1, y    , z    ) != Voxel::Empty)) ||
		  ((x == (voxels.width() - 1))  && (y < getHeightAt(voxels.cubic_size(), pos.x + x + 1, pos.z + z))) )
		activated_neighbors[0] = true;
    
    if ( (!(x == 0)                     && (voxels(x - 1, y    , z    ) != Voxel::Empty)) ||
    	  ((x == 0)                     && (y < getHeightAt(voxels.cubic_size(), pos.x + float(x) - 1, pos.z + z))) ) 
    	activated_neighbors[1] = true;
    
    if ( (!(y == (voxels.height() - 1)) && (voxels(x    , y + 1, z    ) != Voxel::Empty)) ||
    	  ((y == (voxels.height() - 1)) && (float(y) + 1 < getHeightAt(voxels.cubic_size(), pos.x + x, pos.z + z))) ) 
    	activated_neighbors[2] = true;
    
    if ( (!(y == 0)                     && (voxels(x    , y - 1, z    ) != Voxel::Empty)) ||
    	  ((y == 0)                     && (float(y) - 1 < getHeightAt(voxels.cubic_size(), pos.x + x, pos.z + z))) ) 
    	activated_neighbors[3] = true;
    
    if ( (!(z == (voxels.depth() - 1))  && (voxels(x    , y    , z + 1) != Voxel::Empty)) ||
    	  ((z == (voxels.depth() - 1))  && (y < getHeightAt(voxels.cubic_size(), pos.x + x, pos.z + z + 1))) ) 
    	activated_neighbors[4] = true;

    if ( (!(z == 0)                     && (voxels(x    , y    , z - 1) != Voxel::Empty)) ||
    	  ((z == 0)                     && (y < getHeightAt(voxels.cubic_size(), pos.x + x, pos.z +  float(z) - 1))) ) 
    	activated_neighbors[5] = true;

	// if ( !(x == (voxels.width() - 1))  && (voxels(x + 1, y    , z    ) != Voxel::Empty) ) activated_neighbors[0] = true;
	// if ( !(x == 0)                     && (voxels(x - 1, y    , z    ) != Voxel::Empty) ) activated_neighbors[1] = true;
	// if ( !(y == (voxels.height()- 1))  && (voxels(x    , y + 1, z    ) != Voxel::Empty) ) activated_neighbors[2] = true;
	// if ( !(y == 0)                     && (voxels(x    , y - 1, z    ) != Voxel::Empty) ) activated_neighbors[3] = true;
	// if ( !(z == (voxels.depth() - 1))  && (voxels(x    , y    , z + 1) != Voxel::Empty) ) activated_neighbors[4] = true;
	// if ( !(z == 0)                     && (voxels(x    , y    , z - 1) != Voxel::Empty) ) activated_neighbors[5] = true;

	return activated_neighbors;
}


void TerrainChunk::addCubeFaces(const std::array<bool, 6>& surrounding, size_t x, size_t y, size_t z) const
{

	float height_ratio = float(y) / voxels.cubic_size();
	// std::cerr << "height_ratio : "<< height_ratio << '\n';

	glm::vec3 color(1.0, 0.8, 0.1);

	// std::cerr << "(" << color.r << ", " << color.g << ", " <<  color.b << ")\n";

	if(height_ratio > 0.25)
		color = glm::vec3(0.1, 1.0 - height_ratio, 0);

	// glm::vec3 normal(0, 0, 0);

	// XPlus
	if (!surrounding[0])
	{
		glm::vec3 v1(x + 1, y    , z);
		glm::vec3 v2(x + 1, y + 1, z);
		glm::vec3 v3(x + 1, y    , z + 1);
		glm::vec3 v4(x + 1, y + 1, z + 1);

		// glm::vec3 normal = glm::cross((v2 - v1), (v3 - v1));
		
		renderer->mesh->addQuad(v1, v2, v3, v4, glm::vec3(1, 0, 0), color); // multiply by voxel_size if != 1.0f
	}

	// XMinus
	if (!surrounding[1])
	{
		glm::vec3 v1(x, y    , z);
		glm::vec3 v2(x, y + 1, z);
		glm::vec3 v3(x, y    , z + 1);
		glm::vec3 v4(x, y + 1, z + 1);

		// glm::vec3 normal = glm::cross((v3 - v1), (v2 - v1));
		
		renderer->mesh->addQuad(v1, v3, v2, v4, glm::vec3(-1, 0, 0), color); // multiply by voxel_size if != 1.0f
	}

	// YPlus
	if (!surrounding[2])
	{
		glm::vec3 v1(x    , y + 1, z);
		glm::vec3 v2(x + 1, y + 1, z);
		glm::vec3 v3(x    , y + 1, z + 1);
		glm::vec3 v4(x + 1, y + 1, z + 1);

		// glm::vec3 normal = glm::cross((v2 - v1), (v3 - v1));
		
		renderer->mesh->addQuad(v1, v3, v2, v4, glm::vec3(0, 1, 0), color); // multiply by voxel_size if != 1.0f
	}

	// YMinus
	if (!surrounding[3])
	{
		glm::vec3 v1(x    , y, z);
		glm::vec3 v2(x + 1, y, z);
		glm::vec3 v3(x    , y, z + 1);
		glm::vec3 v4(x + 1, y, z + 1);

		// glm::vec3 normal = glm::cross((v3 - v1), (v2 - v1));
		
		renderer->mesh->addQuad(v1, v2, v3, v4, glm::vec3(0, -1, 0), color); // multiply by voxel_size if != 1.0f
	}

	// ZPlus
	if (!surrounding[4])
	{
		glm::vec3 v1(x    , y    , z + 1);
		glm::vec3 v2(x + 1, y    , z + 1);
		glm::vec3 v3(x    , y + 1, z + 1);
		glm::vec3 v4(x + 1, y + 1, z + 1);

		// glm::vec3 normal = -glm::cross((v2 - v1), (v3 - v1));
		
		renderer->mesh->addQuad(v1, v2, v3, v4, glm::vec3(0, 0, 1), color); // multiply by voxel_size if != 1.0f
	}

	// ZMinus
	if (!surrounding[5])
	{
		glm::vec3 v1(x    , y    , z);
		glm::vec3 v2(x + 1, y    , z);
		glm::vec3 v3(x    , y + 1, z);
		glm::vec3 v4(x + 1, y + 1, z);

		// glm::vec3 normal = glm::cross((v3 - v1), (v2 - v1));
		
		renderer->mesh->addQuad(v1, v3, v2, v4, glm::vec3(0, 0, -1), color); // multiply by voxel_size if != 1.0f
	}
}

void TerrainChunk::calculateMesh()
{
	for(size_t i = 0 ; i< voxels.width() ; i++) {
		for(size_t j = 0 ; j < voxels.height() ; j++) {
			for(size_t k = 0 ; k < voxels.depth() ; k++) {
				if (voxels(i, j, k) != Voxel::Empty) // si le voxel est activé
				{
					this->addCubeFaces(this->surrounding(i, j, k), i, j, k);
				}
			}
		}
	}
}

size_t TerrainChunk::getHeightAt(size_t chunk_size, float x, float z) {

	SimplexNoise snoise(m_frequency);

	float perlin_value = (snoise.fractal(nbOctaves, x, z) + 1.0) / 2.0;
			
	return std::round(perlin_value * chunk_size);
}
