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


void EngineObject::createUI(char *ID){

	ImGui::BeginChild(ID);
    ImGui::Text(name.c_str()); ImGui::SameLine();
    ImGui::Text("id : %d", getID());
    ImGui::Separator();
    transform->createUI();

    
    ImGui::EndChild();
}