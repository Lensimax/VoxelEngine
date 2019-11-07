#include "transform.h"

#include <imgui.h>

#include <stdio.h>


Transform::Transform(vec3 center, vec3 position, vec3 scale, vec3 rotation){
    this->vecPosition = position;
    this->vecScale = scale;
    this->vecRotation = rotation;
    this->center = center;

    this->positionToSend = position;
    this->scaleToSend = scale;
    this->rotationToSend = rotation;
    sameAsModelMat = true;

    animRotX = 0, animRotY = 0; animRotZ = 0;
    animChildRotX = 0; animChildRotY = 0; animChildRotZ = 0;

    b_animRotX = false, b_animRotY = false; b_animRotZ = false;
    b_animChildRotX = false; b_animChildRotY = false; b_animChildRotZ = false;
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
    modelMat = glm::rotate(modelMat, vecRotation[0]+animRotX, vec3(1.0,0.0,0.0));
    modelMat = glm::rotate(modelMat, vecRotation[1]+animRotY, vec3(0.0,1.0,0.0));
    modelMat = glm::rotate(modelMat, vecRotation[2]+animRotZ, vec3(0.0,0.0,1.0));

    return modelMat;
}

mat4 Transform::getModelToChild(mat4 modelMat){
    if(sameAsModelMat){
        return getModelMat(modelMat);
    } else {
        modelMat = translate(modelMat, positionToSend);
    // modelMat = translate(modelMat, center);
        modelMat = glm::scale(modelMat, scaleToSend);
        modelMat = glm::rotate(modelMat, rotationToSend[0]+animChildRotX, vec3(1.0,0.0,0.0));
        modelMat = glm::rotate(modelMat, rotationToSend[1]+animChildRotY, vec3(0.0,1.0,0.0));
        modelMat = glm::rotate(modelMat, rotationToSend[2]+animChildRotZ, vec3(0.0,0.0,1.0));

        return modelMat;
    }

}

void Transform::update(){

    if(b_animRotX){ animRotX += 0.01; }
    if(b_animRotY){ animRotY += 0.01; }
    if(b_animRotZ){ animRotZ += 0.01; }

    if(b_animChildRotX){ animChildRotX += 0.01; }
    if(b_animChildRotY){ animChildRotY += 0.01; }
    if(b_animChildRotZ){ animChildRotZ += 0.01; }

}



void Transform::createUI(){
    const float lowestValue = -1000.0f;
    const float highestValue = 1000.0f;
    int node_flags = 0;

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

    bool node_open_anim = ImGui::TreeNodeEx((void*)(intptr_t)0, node_flags, "Animation");

    if (node_open_anim) {
        ImGui::Text("Rotation X : ");
        ImGui::SameLine(); ImGui::Checkbox("##RotX", &b_animRotX);
        ImGui::Text("Rotation Y : ");
        ImGui::SameLine(); ImGui::Checkbox("##RotY", &b_animRotY);
        ImGui::Text("Rotation Z : ");
        ImGui::SameLine(); ImGui::Checkbox("##RotZ", &b_animRotZ);

        ImGui::TreePop();
    }

    int node_flags_child = 0;
    bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)1, node_flags_child, "Model Matrice to child");

    if (node_open) {
        ImGui::Text("Same matrice as parent");
        ImGui::SameLine(); ImGui::Checkbox("##TransformSameAsParent", &sameAsModelMat);
        ImGui::Text("Position: "); ImGui::SameLine();
        ImGui::DragFloat3("position", &positionToSend[0], 0.01f, lowestValue, highestValue, format);
        ImGui::Text("Rotation: "); ImGui::SameLine();
        ImGui::DragFloat3("rotation", &rotationToSend[0], 0.01f, lowestValue, highestValue, format);
        ImGui::Text("Scale: "); ImGui::SameLine();
        ImGui::DragFloat3("scale", &scaleToSend[0], 0.005f, 0.0f, highestValue, format);

        int anim_node_flags_child = 0;
        bool node_open_anim_child = ImGui::TreeNodeEx((void*)(intptr_t)2, anim_node_flags_child, "Animation Child");

        if (node_open_anim_child) {
            ImGui::Text("Rotation X : ");
            ImGui::SameLine(); ImGui::Checkbox("##ChildRotX", &b_animChildRotX);
            ImGui::Text("Rotation Y : ");
            ImGui::SameLine(); ImGui::Checkbox("##ChildRotY", &b_animChildRotY);
            ImGui::Text("Rotation Z : ");
            ImGui::SameLine(); ImGui::Checkbox("##ChildRotZ", &b_animChildRotZ);

            ImGui::TreePop();
        }


        ImGui::TreePop();
    }

    // to hide label of the input
    ImGui::PopItemWidth();
}
