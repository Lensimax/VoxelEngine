#ifndef _TERRAIN_MANAGER_H_
#define _TERRAIN_MANAGER_H_

#include "terrainChunk.h"
#include "../engineClass/gameObject.h"

class TerrainManager : public Component {

public:

	/// Constructors

	TerrainManager(size_t chunk_size, size_t terrain_size); // Initialise les valeurs du chunk à partir de sa position dans le monde

	/// Overrides

	void start() override;

	/// Factory

	GameObject* createTerrainChunk(glm::vec3 position);

	/// Accessors

	size_t getHeightAt(float x, float z) const;
	size_t getChunkSize() const;
	size_t getTerrainSize() const;

private:

	size_t m_chunk_size;
	size_t m_terrain_size;
	std::vector<GameObject*> m_chunks;
};

#endif