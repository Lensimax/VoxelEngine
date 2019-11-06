#include "transform.h"

#include <imgui.h>


Transform::Transform(vec3 center, vec3 position, vec3 scale, vec3 rotation){
    this->vecPosition = position;
    this->vecScale = scale;
    this->vecRotation = rotation;
    this->center = center;
}


Transform::~Transform(){

}

void Transform::setPosition(vec3 position){
    this->vecPosition = position;
}
void Transform::rotate(vec3 axis){
    this->vecRotation = axis;
}

void Transform::setCenter(vec3 center) {
    this->center = center;
}

void Transform::scale(vec3 scale){
    this->vecScale = scale;
}

mat4 Transform::getModelMat(){
    mat4 model = mat4(1.0f);
    model = translate(model, vecPosition);
    // model = translate(model, center);
    model = glm::scale(model, vecScale);
    model = glm::rotate(model, vecRotation[0], vec3(1.0,0.0,0.0));
    model = glm::rotate(model, vecRotation[1], vec3(0.0,1.0,0.0));
    model = glm::rotate(model, vecRotation[2], vec3(0.0,0.0,1.0));

    return model;
}

mat4 Transform::getModelMat(mat4 modelMat){
    modelMat = translate(modelMat, vecPosition);
    // modelMat = translate(modelMat, center);
    modelMat = glm::scale(modelMat, vecScale);
    modelMat = glm::rotate(modelMat, vecRotation[0], vec3(1.0,0.0,0.0));
    modelMat = glm::rotate(modelMat, vecRotation[1], vec3(0.0,1.0,0.0));
    modelMat = glm::rotate(modelMat, vecRotation[2], vec3(0.0,0.0,1.0));

    return modelMat;
}



void Transform::createUI(){
    const float lowestValue = -1000.0f;
    const float highestValue = 1000.0f;

    // format d'affichage
    const char *format = "%.3f";

    // to hide label of the input
    ImGui::PushItemWidth(-1);

    ImGui::Text("Transform");
    ImGui::Text("Position: "); ImGui::SameLine();
    ImGui::DragFloat3("position", &vecPosition[0], 0.01f, lowestValue, highestValue, format);
    ImGui::Text("Rotation: "); ImGui::SameLine();
    ImGui::DragFloat3("rotation", &vecRotation[0], 0.01f, lowestValue, highestValue, format);
    ImGui::Text("Scale: "); ImGui::SameLine();
    ImGui::DragFloat3("scale", &vecScale[0], 0.005f, 0.0f, highestValue, format);

    // to hide label of the input
    ImGui::PopItemWidth();
}
