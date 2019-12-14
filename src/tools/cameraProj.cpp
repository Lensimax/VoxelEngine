#include "cameraProj.h"

#include "../components/axisRenderer.h"
#include "../components/meshRenderer.h"
#include "../material/lambertian.h"
#include "../models/mesh/meshCube.h"

#include <imgui.h>


CameraProj::CameraProj(int id, std::string name, Transform *transform, float fov, float n, float f) : m_fovy(fov), m_near(n), m_far(f){
    setName(name);
    setID(id);
    m_transform = transform;

 
}




void CameraProj::createUI(char *ID){

    ImGui::BeginChild(ID);
    ImGui::Text(m_name.c_str());
    ImGui::Separator();

    m_transform->createUI();

    ImGui::Separator();

    ImGui::Text("Fov: "); ImGui::SameLine();
    ImGui::DragFloat("##fov", &m_fovy, 0.01f);
    ImGui::Text("Near: "); ImGui::SameLine();
    ImGui::DragFloat("##near", &m_near, 0.01f); //ImGui::SameLine();
    ImGui::Text("Far: "); ImGui::SameLine();
    ImGui::DragFloat("##far", &m_far, 0.01f);

    char label[2048];
    unsigned int i=0;
    while(i<m_components.size()){
        ImGui::Separator();
        // sprintf(label, "%s", m_components[i]->getName());
        if (ImGui::TreeNode(m_components[i]->getName())){
            ImGui::SameLine(); ImGui::Checkbox("##active", &(m_components[i]->m_active));
            ImGui::SameLine();
            if(ImGui::Button("Delete Component")){
                delete m_components[i];
                m_components.erase(m_components.begin()+i);
            } else {
                m_components[i]->createUI();
                i++;
            }
            ImGui::TreePop();
        } else {
            i++;
        }
    }

    ImGui::Separator();  

    if(ImGui::BeginMenu("Add Component")){
        if (ImGui::MenuItem("Add MeshCube")) { addComponent<Mesh*>(new MeshCube()); }
        if (ImGui::MenuItem("Add Material")) { addComponent<Material*>(new Lambertian()); }
        if (ImGui::MenuItem("Add MeshRenderer")) { addComponent<MeshRenderer*>(new MeshRenderer());  }
        if (ImGui::MenuItem("Add AxisRenderer")) { addComponent<AxisRenderer*>(new AxisRenderer());  }
        ImGui::EndMenu();
    }


    ImGui::EndChild();
}



glm::mat4 CameraProj::getProj(float aspect){
    return glm::perspective(m_fovy, aspect, m_near, m_far);
}
