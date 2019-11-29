#include "voxelGrid.h"


VoxelGrid::VoxelGrid(int id, std::string n, Transform *t, float sizeCube){
	assert(sizeCube > 0.0f);
	setID(id);
	setName(n);

	this->sizeCube = sizeCube;

	transform = t;
	mesh = new MeshCube(sizeCube);
	material = new Lambertian();

	chunk = new Chunk(sizeCube);
}



VoxelGrid::~VoxelGrid(){
	delete chunk;
}


void VoxelGrid::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){


    glUseProgram(material->getShaderID());

	chunk->draw(modelMat, viewMat, projectionMat, light, mesh, material);

    glUseProgram(0);


}



void VoxelGrid::createUI(char *ID){
    const int node_flags = 0;

    ImGui::BeginChild(ID);
    ImGui::Text(name.c_str());

    ImGui::Separator();
    transform->createUI();

    ImGui::Separator();
    bool node_mesh = ImGui::TreeNodeEx("Mesh", node_flags);
    if(node_mesh){
        mesh->createUI();
        if (ImGui::Button("Recreate")){
            mesh->recreate();
            
        }
        ImGui::Text("Show bounding box "); ImGui::SameLine();
        ImGui::Checkbox("##showboundingbox"+getID(),&showboundingbox);

        ImGui::TreePop();
    }

    ImGui::Separator();
    bool node_material = ImGui::TreeNodeEx("Material", node_flags);
    if(node_material){
        material->createUI();
        ImGui::TreePop();
    }
    ImGui::Separator();

	ImGui::EndChild();
}
    

