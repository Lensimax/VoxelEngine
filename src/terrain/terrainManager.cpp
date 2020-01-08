#include "terrainManager.h"
#include "../material/simpleMat.h"
#include <algorithm>

TerrainManager::TerrainManager(size_t chunk_size, size_t terrain_size, Transform* player_transform) : m_chunk_size(chunk_size), m_terrain_size(terrain_size), m_player_transform(player_transform) {
    assert(m_player_transform != nullptr);

    m_oldChunkGridCoord = toChunkGridCoord(getPlayerCoord());
}

void TerrainManager::start() {

    // Ajoute les chunks autour de la position du joueur
    generateAround(getPlayerCoord());
}

void TerrainManager::inputUpdate() {
    
    glm::vec3 player_coord = getPlayerCoord();
    
    glm::ivec3 cg_coord = toChunkGridCoord(player_coord);
    // std::cerr << '(' << cg_coord.x << ", " << cg_coord.y << ", " << cg_coord.z << ")\n";

    if (m_oldChunkGridCoord != cg_coord)
    {
        // std::cerr << "deleting old chunks...\n";
        // segmentation fault je sais pas pk ?
        // m_gameobject->deleteAllChildren();

        // std::cerr << "generating new chunks...\n";
        generateAround(getPlayerCoord());

        m_oldChunkGridCoord = cg_coord;
    }
}

void TerrainManager::generateAround(glm::vec3 position) {
    assert(m_gameobject != nullptr);

    glm::ivec3 current_chunk_coord = toChunkGridCoord(position) * glm::ivec3(getChunkSize());
    current_chunk_coord.y = 0;

    glm::ivec3 offset(getChunkSize() * (getTerrainSize() / 2), 0, getChunkSize() * (getTerrainSize() / 2));
    glm::ivec3 min_chunk_pos = current_chunk_coord - offset;

    for (size_t i = 0 ; i < getTerrainSize() ; ++i)
    {
        for (size_t k = 0 ; k < getTerrainSize() ; ++k)
        {
            GameObject* chunk = createTerrainChunk(min_chunk_pos + glm::ivec3(i * getChunkSize(), 0, k * getChunkSize()));
            m_gameobject->addChild(chunk);
        }
    }
}

GameObject* TerrainManager::createTerrainChunk(glm::vec3 position) const{

	// std::cerr << "Attention : bricolage temporaire sur les id dans TerrainManager::createTerrainChunk !\n";
	static size_t id = 10000;
    
    GameObject* chunk = new GameObject(id, "Chunk", new Transform(position));
    			chunk->addComponent<Mesh*>(new Mesh());
    			chunk->addComponent<Material*>(new Lambertian());
    			chunk->addComponent<MeshRenderer*>(new MeshRenderer());
    			chunk->addComponent<TerrainChunk*>(new TerrainChunk(getChunkSize()));

	id++;

    return chunk;
}

glm::ivec3 TerrainManager::toChunkGridCoord(glm::vec3 world_coord) const {
    glm::vec3 coord = world_coord / glm::vec3(getChunkSize());
    coord.x = coord.x < 0 ? std::floor(coord.x) : coord.x; 
    coord.y = coord.y < 0 ? std::floor(coord.y) : coord.y; 
    coord.z = coord.z < 0 ? std::floor(coord.z) : coord.z; 
    return glm::ivec3(coord);
}

glm::uvec3 TerrainManager::toChunkCoord(glm::vec3 world_coord) const {
    return glm::uvec3(
        world_coord.x < 0 ? (getChunkSize() - 1) - (size_t(abs(world_coord.x)) % getChunkSize()) : size_t(world_coord.x) % getChunkSize(),
        world_coord.y < 0 ? (getChunkSize() - 1) - (size_t(abs(world_coord.y)) % getChunkSize()) : size_t(world_coord.y) % getChunkSize(),
        world_coord.z < 0 ? (getChunkSize() - 1) - (size_t(abs(world_coord.z)) % getChunkSize()) : size_t(world_coord.z) % getChunkSize()
    );
}

TerrainChunk* TerrainManager::getPlayerChunk() {
    return getChunkAt(getPlayerCoord());
}

TerrainChunk* TerrainManager::getChunkAt(glm::vec3 world_coord) {
    glm::vec3 chunk_coord = toChunkGridCoord(world_coord) * glm::ivec3(getChunkSize()); 

    auto res = std::find_if(std::begin(m_gameobject->m_listOfChildren), std::end(m_gameobject->m_listOfChildren), [&](GameObject* go){return go->getTransform()->getPosition() == chunk_coord;});
    if (res != std::end(m_gameobject->m_listOfChildren))
        return (*res)->getComponent<TerrainChunk*>();
    else
        return nullptr;
}

Voxel TerrainManager::getVoxelAt(glm::vec3 world_coord) {
    TerrainChunk* chunk = getChunkAt(world_coord);
    if (chunk != nullptr)
    {
        glm::uvec3 chunk_coord = toChunkCoord(world_coord);
        return chunk->voxels(chunk_coord.x, chunk_coord.y, chunk_coord.z);
    }
    else
    {
        return Voxel::Empty;
    }
}

void  TerrainManager::setVoxelAt(glm::vec3 world_coord, Voxel v) {
    TerrainChunk* chunk = getChunkAt(world_coord);
    
    if (chunk != nullptr)
    {
        glm::uvec3 chunk_coord = toChunkCoord(world_coord);
        chunk->voxels(chunk_coord.x, chunk_coord.y, chunk_coord.z) = v;
    }

}


glm::vec3 TerrainManager::getPlayerCoord() const {
    return m_player_transform->getPosition();
}

size_t TerrainManager::getHeightAt(float x, float z) const {
    return TerrainChunk::getHeightAt(getChunkSize(), x, z); 
}

size_t TerrainManager::getChunkSize() const {
    return m_chunk_size;
}

size_t TerrainManager::getTerrainSize() const {
    return m_terrain_size;
}
