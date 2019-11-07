#include <imgui.h>

#include "engineObject.h"

#include <stdio.h>


EngineObject::EngineObject(int id, std::string n, Transform *t){
	setID(id);
	setName("EngineObject");
	transform = t;
}



void EngineObject::setName(std::string n){
    name = n;
}

std::string EngineObject::getName(){
    return name;
}

int EngineObject::getID(){
	return ID;
}


void EngineObject::setID(int i){
	ID = i;
}


Transform *EngineObject::getTransform(){
    return transform;
}

void EngineObject::addChild(EngineObject *obj){

    listOfChildren.push_back(obj);
}


// trouve l'enfant avec l'ID correspondant et le supprime en récursif
void EngineObject::removeChild(int id){
    for(unsigned int i=0; i<listOfChildren.size(); i++){
        if(listOfChildren[i]->getID() == id){

            listOfChildren[i]->deleteAllChildren();
            delete(listOfChildren[i]);
            listOfChildren.erase(listOfChildren.begin()+i);
            return;
        }
    }
}


// supprime tous les enfants de ce gameobject en récursif
void EngineObject::deleteAllChildren(){
    for(unsigned int i=listOfChildren.size()-1; i >=0; i--){
        if(listOfChildren[i]->listOfChildren.size() == 0){ // n'a pas d'enfant
            delete(listOfChildren[i]);
            listOfChildren.erase(listOfChildren.begin()+i);
        } else {
            listOfChildren[i]->deleteAllChildren();
            delete(listOfChildren[i]);
        }
    }
}



void EngineObject::createUI(char *ID){

	ImGui::BeginChild(ID);
    ImGui::Text(name.c_str()); ImGui::SameLine();
    ImGui::Text("id : %d", getID());
    ImGui::Separator();
    transform->createUI();

    
    ImGui::EndChild();
}

void EngineObject::update(){
    
}