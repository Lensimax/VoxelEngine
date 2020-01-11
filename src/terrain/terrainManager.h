#ifndef _TERRAIN_MANAGER_H_
#define _TERRAIN_MANAGER_H_

#include <map>

#include "terrainChunk.h"
#include "../engineClass/gameObject.h"

auto ivec3_comp = [](const glm::ivec3& v1, const glm::ivec3& v2)
{
	if (v1.x < v2.x)
	{
		return true;
	}
	else if (v1.x == v2.x)
	{
		if (v1.y < v2.y)
		{
			return true;
		}
		else if (v1.y == v2.y)
		{
			if (v1.z < v2.z){
				return true;
			}
		}
	}
	return false;
};

class TerrainManager : public Component {

public:

	/// Constructors

	TerrainManager(size_t chunk_size, size_t terrain_size, Transform* player_transform); // Initialise les valeurs du chunk à partir de sa position dans le monde

	/// Overrides

	void start() override;
	// void update() override;
	void inputUpdate() override;

	/// Factory

	// Alloue un nouveau chunk
	GameObject* createTerrainChunk(glm::vec3 position);

	/// Modificators

	void createChunksAround(glm::vec3 world_coord);
	void manageChunksAround(glm::vec3 world_coord); // managechunks_around
	void updateChunks();

	/// Accessors

	glm::ivec3 toChunkGridCoord(glm::vec3 world_coord)       const;
	glm::vec3  toWorldGridCoord(glm::ivec3 chunk_grid_coord) const;

	glm::uvec3 toVoxelCoord(glm::vec3 world_coord) const;

	TerrainChunk* getPlayerChunk();
	TerrainChunk* getChunkAt(glm::vec3 world_coord); 

	Voxel getVoxelAt(glm::vec3 world_coord);
	void  setVoxelAt(glm::vec3 world_coord, Voxel v); // change le voxel seulement si il est dans les terrains visibles

	glm::vec3 getPlayerCoord() const;

	size_t getHeightAt(float x, float z) const;
	size_t getChunkSize() const;
	size_t getTerrainSize() const;

private:

	size_t m_chunk_size;
	size_t m_terrain_size;
	Transform* m_player_transform = nullptr;
	glm::ivec3 m_oldChunkGridCoord;

	std::map<glm::ivec3, TerrainChunk*, decltype(ivec3_comp)> m_grid_to_chunk_map;
};

#endif