#include "voxelGrid.h"


VoxelGrid::VoxelGrid(int id, std::string n, Transform *t, float size) : m_sizeCube(size){
	assert(m_sizeCube > 0.0f);
	setID(id);
	setName(n);


	m_transform = t;
	m_mesh = new MeshCube(m_sizeCube, false);
	m_material = new Lambertian();

	m_chunk = new Chunk(m_sizeCube);
}



VoxelGrid::~VoxelGrid(){
	delete m_chunk;
}


void VoxelGrid::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){


    glUseProgram(m_material->getShaderID());

	m_chunk->draw(modelMat, viewMat, projectionMat, light, m_mesh, m_material);

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
    

