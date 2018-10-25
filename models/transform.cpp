#include "transform.h"

#include "../imgui/imgui.h"


Transform::Transform(vec3 position, vec3 scale, vec3 rotation){
    this->vecPosition = position;
    this->vecScale = scale;
    this->vecRotation = rotation;
}


Transform::~Transform(){

}

void Transform::setPosition(vec3 position){
    this->vecPosition = position;
}
void Transform::rotate(vec3 axis){
    this->vecRotation = axis;
}

void Transform::scale(vec3 scale){
    this->vecScale = scale;
}

mat4 Transform::getMat4(){
    mat4 model = mat4(1.0f);
    model = translate(model, vecPosition);
    model = glm::scale(model, vecScale);
    model = glm::rotate(model, vecRotation[0], vec3(1.0,0.0,0.0));
    model = glm::rotate(model, vecRotation[1], vec3(0.0,1.0,0.0));
    model = glm::rotate(model, vecRotation[2], vec3(0.0,0.0,1.0));
    return model;
}


void Transform::createUI(){
    ImGui::Text("Position");
    ImGui::InputFloat("x", &vecPosition.x, 0.00f, 0.0f);
    ImGui::InputFloat("y", &vecPosition.y, 0.00f, 0.0f);
    ImGui::InputFloat("z", &vecPosition.z, 0.00f, 0.0f);
}
