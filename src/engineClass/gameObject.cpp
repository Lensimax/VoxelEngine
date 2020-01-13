#include <imgui.h>

#include "gameObject.h"
#include "../components/meshRenderer.h"

#include "../material/lambertian.h"
#include "../models/mesh/meshCube.h"
// #include "../components/chunkRenderer.h"
#include "../components/axisRenderer.h"
#include "../components/colliders/collider.h"
#include "../components/rigidbody.h"
#include "../components/playerController.h"

#include <stdio.h>
#include <iostream>


GameObject::GameObject(int id, std::string n, Transform *t) : m_transform(t){
	setID(id);
	setName(n);

    m_components = std::vector<Component*>();
    m_toRemove = std::vector<Component*>();
}

GameObject::~GameObject(){
    delete m_transform;

    for(Component * comp : m_components){
        delete comp;
    }

    for(unsigned int i=0; i<m_listOfChildren.size(); i++){
        delete m_listOfChildren[i];
    }
    m_components.clear();
    m_listOfChildren.clear();
}

void GameObject::setName(std::string n){
    m_name = n;
}

std::string GameObject::getName(){
    return m_name;
}

int GameObject::getID(){
	return m_id;
}


void GameObject::setID(int i){
	m_id = i;
}


Transform *GameObject::getTransform(){
    return m_transform;
}

void GameObject::addChild(GameObject *obj){

    m_listOfChildren.push_back(obj);
}


// trouve l'enfant avec l'ID correspondant et le supprime en récursif
void GameObject::removeChild(int id){
    for(unsigned int i=0; i<m_listOfChildren.size(); i++){
        if(m_listOfChildren[i]->getID() == id){

            m_listOfChildren[i]->deleteAllChildren();
            delete(m_listOfChildren[i]);
            m_listOfChildren.erase(m_listOfChildren.begin()+i);
            return;
        }
    }
}


// supprime tous les enfants de ce gameobject en récursif
void GameObject::deleteAllChildren(){
    for(int i=m_listOfChildren.size()-1; i >=0; i--){
        if(m_listOfChildren[i]->m_listOfChildren.size() == 0){ // n'a pas d'enfant
            delete(m_listOfChildren[i]);
            m_listOfChildren.erase(m_listOfChildren.begin()+i);
        } else {
            m_listOfChildren[i]->deleteAllChildren();
            delete(m_listOfChildren[i]);
        }
    }
}


void GameObject::createUI(char *ID){
    ImGui::BeginChild(ID);
    ImGui::Text(m_name.c_str()); //ImGui::SameLine();
    //ImGui::Text("id : %d", getID());
    ImGui::Separator();
    m_transform->createUI();

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
        if (ImGui::MenuItem("Add Collider")) { addComponent<Collider*>(new Collider());  }
        if (ImGui::MenuItem("Add Rigidbody")) { addComponent<Rigidbody*>(new Rigidbody());  }
        if (ImGui::MenuItem("Add Player Controller")) { addComponent<PlayerController*>(new PlayerController());  }
        ImGui::EndMenu();
    }
    
    ImGui::EndChild();
}


void GameObject::update(){
    removeComponentToBeDestroyed();
    m_transform->update();

    for(unsigned int i=0; i<m_components.size(); i++){
        m_components[i]->update();
    }
}


void GameObject::inputUpdate(){
    for(unsigned int i=0; i<m_components.size(); i++){
        m_components[i]->inputUpdate();
    }
}

void GameObject::physicsUpdate(){
    for(unsigned int i=0; i<m_components.size(); i++){
        m_components[i]->physicsUpdate();
    }
}


void GameObject::removeComponentToBeDestroyed(){
    for(int i=m_toRemove.size()-1; i>=0; i--){
        delete m_toRemove[i];
        m_toRemove.erase(m_toRemove.begin()+i);
    }
}

