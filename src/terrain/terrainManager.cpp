#include "terrainManager.h"

TerrainManager::TerrainManager(size_t chunk_size, size_t terrain_size) {

	glm::vec3 position(0, 0, 0);

    // glm::vec3 start_pos(-(radius + 1));

    for (size_t i = 0 ; i < terrain_size ; ++i)
    {
    	for (size_t k = 0 ; k < terrain_size ; ++k)
    	{
			m_chunks.emplace_back(createTerrainChunk(position + glm::vec3(i * chunk_size, 0, k * chunk_size)));
    	}
    }
}

void TerrainManager::start() {
	for (auto* chunk : m_chunks)
	{
		m_gameobject->addChild(chunk);
	}
}

GameObject* TerrainManager::createTerrainChunk(glm::vec3 position) {

	std::cerr << "Attention : bricolage sur les id dans TerrainManager::createTerrainChunk !\n";
	static size_t id = 10000;
    
    GameObject* chunk = new GameObject(id, "Chunk", new Transform(position));
    			chunk->addComponent<Mesh*>(new Mesh());
    			chunk->addComponent<Material*>(new Lambertian());
    			chunk->addComponent<MeshRenderer*>(new MeshRenderer());
    			chunk->addComponent<TerrainChunk*>(new TerrainChunk(64));
	
	id++;    

    return chunk;
}
