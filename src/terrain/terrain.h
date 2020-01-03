#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include <map>
#include "terrainChunk.h"

class Terrain {

public:	

	/// Constructors

	Terrain(size_t chunk_size, size_t radius = 0); // Initialise les valeurs du chunk à partir de sa position dans le monde

private:

	std::vector<TerrainChunk> m_chunks;
};

#endif