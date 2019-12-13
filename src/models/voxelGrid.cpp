#include "voxelGrid.h"
#include <iostream>
#include <random>
// #include <glm_display.h>

VoxelGrid::VoxelGrid(int id, std::string n, Transform *t, float size) : m_chunks(9, Chunk(size)), m_sizeCube(size), m_transform(nullptr){
	assert(m_sizeCube > 0.0f);
	setID(id);
	setName(n);


	m_transform = t;
	m_mesh = new MeshCube(m_sizeCube, false);
	m_material = new Lambertian();


	m_chunk = new Chunk(m_sizeCube, 0, 0, 0);

    m_chunk->calculateMesh(m_mesh);

    m_mesh->createVAO();

    std::cerr << "max size : ";
    std::cerr << m_chunk->max_size() << '\n';

    // glm::vec3 chunkGridMinPosition = glm::vec3(-1, 0, -1);

    // size_t i = 0;
    // for (size_t x = 0; x < m_chunks.size() / 3; x++)
    // {
    //     for (size_t z = 0; z < m_chunks.size() / 3; z++)
    //     {
    //         // chunkWorldPositionOffset + glm::vec3(x, y, z);
    //         // std::cerr << chunkGridMinPosition + glm::vec3(x, 0, z) << ' ';
    //         glm::vec3 chunk_pos = chunkGridMinPosition + glm::vec3(x, 0, z);
    //         m_chunks[i] = Chunk(m_sizeCube, chunk_pos.x, chunk_pos.y, chunk_pos.z);
    //         m_chunks[i].calculateMesh(m_mesh);
    //         i++;
    //         // m_chunk->draw(model, viewMat, projectionMat, light, m_mesh, m_material);
    //     }
    //     // std::cerr << '\n';
    // }
}



VoxelGrid::~VoxelGrid(){
	delete m_chunk;
}

void VoxelGrid::setTransform(Transform * t) {
    m_transform = t;
}

Transform* VoxelGrid::getTransform() {
    return m_transform;
}

glm::ivec3 VoxelGrid::toChunkWorldPosition(const glm::vec3& worldPosition) {

    glm::vec3 positionOffset(
        worldPosition.x < 0 ? worldPosition.x - 3 : worldPosition.x,
        worldPosition.y < 0 ? worldPosition.y - 3 : worldPosition.y,
        worldPosition.z < 0 ? worldPosition.z - 3 : worldPosition.z
    );

    return  glm::vec3(positionOffset) / glm::vec3(m_chunk->dimensions());
}

void VoxelGrid::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){

    glUseProgram(m_material->getShaderID());

    // static std::random_device rd;
    // static std::default_random_engine e(rd());
    // static std::uniform_int_distribution<size_t> dist(0, m_chunk->size());
    // static size_t count = 0;

    // count++;

    // if (count > 1)
    // {
    //     count = 0;
    //     m_mesh->deleteVAO();
    //     (*m_chunk)[dist(e)] = Voxel::Type::Empty;
    //     m_chunk->calculateMesh(m_mesh);
    //     m_mesh->createVAO();

    // }

    // glm::vec3 worldPosition = this->getTransform()->getPosition();
    // glm::vec3 chunkWorldPosition = toChunkWorldPosition(worldPosition);

    // glm::vec3 chunkGridMinPosition = (chunkWorldPosition + glm::vec3(-1, 0, -1));

    // size_t i = 0;
    // for (size_t x = 0; x < m_chunks.size() / 3; x++)
    // {
    //     for (size_t z = 0; z < m_chunks.size() / 3; z++)
    //     {
    //         // chunkWorldPositionOffset + glm::vec3(x, y, z);
    //         // std::cerr << chunkGridMinPosition + glm::vec3(x, 0, z) << ' ';
    //         glm::vec3 chunk_pos = chunkGridMinPosition + glm::vec3(x, 0, z);
    //         m_chunks[i] = Chunk(m_sizeCube, chunk_pos.x, chunk_pos.y, chunk_pos.z);
    //         i++;
    //         // m_chunk->draw(model, viewMat, projectionMat, light, m_mesh, m_material);
    //     }
    // }
    // std::cerr << "\n\n";
    m_chunk->draw(modelMat, viewMat, projectionMat, light, m_mesh, m_material);

    // size_t i = 0;
    // for (size_t x = 0; x < m_chunks.size() / 3; x++)
    // {
    //     for (size_t z = 0; z < m_chunks.size() / 3; z++)
    //     {
    //         // chunkWorldPositionOffset + glm::vec3(x, y, z);
    //         // std::cerr << chunkGridMinPosition + glm::vec3(x, 0, z) << ' ';

    //         glm::mat4 model = glm::translate(modelMat, (chunkGridMinPosition + glm::vec3(x, 0, z)) * glm::vec3(m_chunk->dimensions()));
    //         m_chunks[i].draw(model, viewMat, projectionMat, light, m_mesh, m_material);
    //         i++;
    //         // m_chunk->draw(model, viewMat, projectionMat, light, m_mesh, m_material);
    //     }
    //     // std::cerr << '\n';
    // }
    // std::cerr << "\n\n";

/*
    std::cerr << "dimensions : " << glm::vec3(m_chunk->dimensions()) << '\n';
    std::cerr << "worldPosition : " << worldPosition << '\n';
    // std::cerr << "worldPosition * dimension : " << worldPosition * glm::vec3(m_chunk->dimensions()) << '\n'; 
    std::cerr << "chunkworldPosition : " << chunkWorldPosition << '\n';
    std::cerr << "chunkworldPosition * dimensions : " << chunkWorldPosition * glm::vec3(m_chunk->dimensions()) << '\n';
*/


    glUseProgram(0);
}



void VoxelGrid::createUI(char *ID){
    const int node_flags = 0;

    ImGui::BeginChild(ID);
    ImGui::Text(m_name.c_str());

    ImGui::Separator();
    m_transform->createUI();

    ImGui::Separator();
    bool node_mesh = ImGui::TreeNodeEx("Mesh", node_flags);
    if(node_mesh){
        m_mesh->createUI();
        if (ImGui::Button("Recreate")){
            m_mesh->recreate();
            
        }
        ImGui::Text("Show bounding box "); ImGui::SameLine();
        ImGui::Checkbox("##showboundingbox"+getID(),&m_showboundingbox);

        ImGui::TreePop();
    }

    ImGui::Separator();
    bool node_material = ImGui::TreeNodeEx("Material", node_flags);
    if(node_material){
        m_material->createUI();
        ImGui::TreePop();
    }
    ImGui::Separator();

	ImGui::EndChild();
}
    

