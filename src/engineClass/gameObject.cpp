#include <imgui.h>

#include "gameObject.h"
#include "../components/meshRenderer.h"

#include "../material/lambertian.h"
#include "../models/mesh/meshCube.h"
#include "../components/chunkRenderer.h"

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
    for(unsigned int i=m_listOfChildren.size()-1; i >=0; i--){
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


    for(unsigned int i=0; i<m_components.size(); i++){
        ImGui::Separator();
        m_components[i]->createUI();
    }

    ImGui::Separator();  

    if(ImGui::BeginMenu("Add Component")){
        if (ImGui::MenuItem("Add MeshCube")) { addComponent<Mesh*>(new MeshCube()); }
        if (ImGui::MenuItem("Add Material")) { addComponent<Material*>(new Lambertian()); }
        if (ImGui::MenuItem("Add MeshRenderer")) { addComponent<MeshRenderer*>(new MeshRenderer());  }
        // if (ImGui::MenuItem("Add ChunkRenderer")) { addComponent<ChunkRenderer*>(new ChunkRenderer());  }
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


void GameObject::removeComponentToBeDestroyed(){
    for(int i=m_toRemove.size()-1; i>=0; i--){
        delete m_toRemove[i];
        m_toRemove.erase(m_toRemove.begin()+i);
    }
}

