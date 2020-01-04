#include "terrainManager.h"


Terrain::Terrain(size_t chunk_size, size_t radius) {

	// glm::vec3 start_pos(-(radius + 1));

	// for (size_t i = 0 ; i < 2 * radius + 1 ; ++i)
	// {
	// 	for (size_t k = 0 ; k < 2 * radius + 1 ; ++k)
	// 	{
	// 		GameObject* chunk = new GameObject(addNewId(), "Chunk", new Transform(start_pos + glm::vec3(i, 0, k)));
	// 		chunk->addComponent<Mesh*>         (new Mesh());
 //            chunk->addComponent<Material*>     (new Lambertian());
 //            chunk->addComponent<MeshRenderer*> (new MeshRenderer());
 //            chunk->addComponent<TerrainChunk*> (new TerrainChunk(64));
    
	// 		m_chunks.emplace_back(new TerrainChunk(chunk_size) / float(radius + 1)));
	// 	}
	// }
}