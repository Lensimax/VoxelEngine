#include "terrainManager.h"
#include "../material/simpleMat.h"
#include <algorithm>

TerrainManager::TerrainManager(size_t chunk_size, size_t terrain_size, Transform* player_transform) : m_chunk_size(chunk_size), m_terrain_size(terrain_size), m_player_transform(player_transform), m_grid_to_chunk_map(ivec3_comp) {
    assert(m_player_transform != nullptr);

    m_oldChunkGridCoord = toChunkGridCoord(getPlayerCoord());
}

void TerrainManager::start() {

    // Création des chunks autour du joueur

    createChunksAround(getPlayerCoord());

    updateChunks();
}

void TerrainManager::inputUpdate() {
    
    glm::vec3 player_coord = getPlayerCoord(); player_coord.y = 0;
    
    glm::ivec3 cg_coord = toChunkGridCoord(player_coord);
    // std::cerr << '(' << cg_coord.x << ", " << cg_coord.y << ", " << cg_coord.z << ")\n";

    if (m_oldChunkGridCoord != cg_coord)
    {

        manageChunksAround(player_coord);
        updateChunks();
        // std::cerr << "deleting old chunks...\n";
        // segmentation fault je sais pas pk ?
        // m_gameobject->deleteAllChildren();
        // m_grid_to_chunk_map.clear()zz;

        // std::cerr << "generating new chunks...\n";
        // createChunksAround(getPlayerCoord());

        m_oldChunkGridCoord = cg_coord;
    }
}

void TerrainManager::createChunksAround(glm::vec3 position) {
    assert(m_gameobject != nullptr);

    glm::ivec3 current_chunk_coord = toChunkGridCoord(position) * glm::ivec3(getChunkSize());
    current_chunk_coord.y = 0;

    glm::ivec3 offset(getChunkSize() * (getTerrainSize() / 2), 0, getChunkSize() * (getTerrainSize() / 2));
    glm::ivec3 min_chunk_pos = current_chunk_coord - offset;

    for (size_t i = 0 ; i < getTerrainSize() ; ++i)
    {
        for (size_t k = 0 ; k < getTerrainSize() ; ++k)
        {
            // Instanciation des chunks
            GameObject* chunk = createTerrainChunk(min_chunk_pos + glm::ivec3(i * getChunkSize(), 0, k * getChunkSize()));
            m_gameobject->addChild(chunk);

            // Ajout des chunks dans une map en fonction de leurs coordonnées dans la grille de chunk
            glm::ivec3 chunk_grid_coord = min_chunk_pos + glm::ivec3(i, 0, k);
            m_grid_to_chunk_map[chunk_grid_coord] = chunk->getComponent<TerrainChunk*>();
        }
    }
}

void TerrainManager::manageChunksAround(glm::vec3 world_coord) {

    glm::ivec3 current_grid_coord(toChunkGridCoord(world_coord));
    glm::ivec3 grid_offset(getTerrainSize() / 2, 0, getTerrainSize() / 2);
    glm::ivec3 min_grid_coord = current_grid_coord - grid_offset;

    std::vector<GameObject*> to_keep;

    // Création des chunks autour de la position world_coord qui n'éxistent pas déja

    // m_grid_to_chunk_map.clear();

    for (size_t i = 0 ; i < getTerrainSize() ; ++i)
    {
        for (size_t k = 0 ; k < getTerrainSize() ; ++k)
        {
            glm::ivec3 chunk_grid_coord = min_grid_coord + glm::ivec3(i, 0, k);

            auto res = m_grid_to_chunk_map.find(chunk_grid_coord);
            
            if (res != m_grid_to_chunk_map.end()) // Trouvé
            {
                TerrainChunk* terrain_chunk = res->second;

                m_grid_to_chunk_map[chunk_grid_coord] = terrain_chunk;
                to_keep.push_back(terrain_chunk->getGameObject());
            }
            else
            {
                // Si le chunk n'est pas dans la map il faut le creer
                GameObject* chunk = createTerrainChunk(toWorldGridCoord(chunk_grid_coord));
                m_gameobject->addChild(chunk);

                m_grid_to_chunk_map[chunk_grid_coord] = chunk->getComponent<TerrainChunk*>();
                to_keep.push_back(chunk);
            }
        }
    }
}

void TerrainManager::updateChunks(){

    // initialize leurs valeurs de terrain

    for (auto& p : m_grid_to_chunk_map)
    {
        TerrainChunk* chunk = p.second;

        if (chunk->needUpdate)
            chunk->generate();
    }

    // Calcul de leurs mesh

    for (auto& p : m_grid_to_chunk_map)
    {
        TerrainChunk* chunk = p.second;
        
        if (chunk->needUpdate)
            chunk->calculateMesh();
    }

    // Envoie des données au GPU pour le dessin

    for (auto& p : m_grid_to_chunk_map)
    {
        TerrainChunk* chunk = p.second;

        if (chunk->needUpdate)
        {
            chunk->renderer->mesh->createVAO();
            chunk->needUpdate = false;
        }
    }
}


GameObject* TerrainManager::createTerrainChunk(glm::vec3 position) {

	// std::cerr << "Attention : bricolage temporaire sur les id dans TerrainManager::createTerrainChunk !\n";
	static size_t id = 10000;
    
    GameObject* chunk = new GameObject(id, "Chunk", new Transform(position));
    			chunk->addComponent<Mesh*>(new Mesh());
    			chunk->addComponent<Material*>(new Lambertian());
    			chunk->addComponent<MeshRenderer*>(new MeshRenderer());
    			chunk->addComponent<TerrainChunk*>(new TerrainChunk(getChunkSize(), this));

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

glm::vec3 TerrainManager::toWorldGridCoord(glm::ivec3 chunk_grid_coord) const {
    return glm::vec3(chunk_grid_coord) * glm::vec3(getChunkSize());
}

glm::uvec3 TerrainManager::toVoxelCoord(glm::vec3 world_coord) const {
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
        glm::uvec3 voxel = toVoxelCoord(world_coord);
        return chunk->voxels(voxel.x, voxel.y, voxel.z);
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
        glm::uvec3 voxel = toVoxelCoord(world_coord);
        chunk->voxels(voxel.x, voxel.y, voxel.z) = v;
        std::cerr << "set\n";
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
