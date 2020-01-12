#ifndef _TERRAIN_MANAGER_H_
#define _TERRAIN_MANAGER_H_

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include <map>
#include <functional>

#include "terrainChunk.h"
#include "../engineClass/gameObject.h"


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
	void manageChunksAround(glm::vec3 world_coord);
	
	void updateChunkAt(glm::vec3 world_coord);
	void updateChunks();

	/// Accessors

	glm::ivec3 toChunkGridCoord(glm::vec3 world_coord) const;
	glm::uvec3 toChunkCoord(glm::vec3 world_coord) const;
	glm::vec3 toVoxelCoordInChunk(glm::vec3 world_coord) const;
	glm::vec3 toVoxelWorldCoord(glm::vec3 world_coord) const;
	glm::vec3 toWorldGridCoord(glm::ivec3 chunk_grid_coord) const;
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

	std::map<glm::ivec3, TerrainChunk*, std::function<bool(const glm::ivec3& v1, const glm::ivec3& v2)>> m_grid_to_chunk_map;
};

#endif