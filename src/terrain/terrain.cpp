#include "terrain.h"


Terrain::Terrain(size_t chunk_size, size_t radius) {
	for (size_t i = 0 ; i < 2 * radius + 1 ; ++i)
	{
		for (size_t k = 0 ; k < 2 * radius + 1 ; ++k)
		{
			m_chunks.emplace_back(TerrainChunk(chunk_size, glm::vec3(i * chunk_size, 0, k * chunk_size) / float(radius + 1)));
		}
	}
}