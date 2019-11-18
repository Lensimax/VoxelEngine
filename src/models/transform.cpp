#include "transform.h"

#include <imgui.h>

#include <stdio.h>


Transform::Transform(vec3 center, vec3 position, vec3 scale, vec3 rotation){
    this->vecPosition = position;
    this->vecScale = scale;
    this->vecRotation = rotation;
    this->center = center;

    this->positionToSend = position;
    this->scaleToSend = glm::vec3(1);
    this->rotationToSend = glm::vec3(0);

    samePosition = true; sameRotation = true;


    reset();

    animRotSpeedX = defaultSpeed, animRotSpeedY = defaultSpeed; animRotSpeedZ = defaultSpeed;
    animChildRotSpeedX = defaultSpeed; animChildRotSpeedY = defaultSpeed; animChildRotSpeedZ = defaultSpeed;

    b_animRotX = false, b_animRotY = false; b_animRotZ = false;
    b_animChildRotX = false; b_animChildRotY = false; b_animChildRotZ = false;
}



Transform::~Transform(){

}


void Transform::reset(){
    animRotX = 0, animRotY = 0; animRotZ = 0;
    animChildRotX = 0; animChildRotY = 0; animChildRotZ = 0;
}

void Transform::setPosition(vec3 position){
    this->vecPosition = position;
}
void Transform::rotate(vec3 axis){
    this->vecRotation = axis;
}

void Transform::rotatefromScreen(vec2 v){
    vecRotation.x += v.y;
    vecRotation.y += v.x;
}

void Transform::setCenter(vec3 center) {
    this->center = center;
}

void Transform::scale(vec3 scale){
    this->vecScale = scale;
}

void Transform::addTranslation(vec3 t){
    vecPosition += t;
}

mat4 Transform::getModelMat(){
    mat4 model = mat4(1.0f);
    model = translate(model, vecPosition);
    // model = translate(model, center);
    model = glm::rotate(model, vecRotation[0], vec3(1.0,0.0,0.0));
    model = glm::rotate(model, vecRotation[1], vec3(0.0,1.0,0.0));
    model = glm::rotate(model, vecRotation[2], vec3(0.0,0.0,1.0));
    model = glm::scale(model, vecScale);

    return model;
}

mat4 Transform::getModelMat(mat4 modelMat){
    modelMat = translate(modelMat, vecPosition);
    // modelMat = translate(modelMat, center);
    modelMat = glm::rotate(modelMat, vecRotation[0]+animRotX, vec3(1.0,0.0,0.0));
    modelMat = glm::rotate(modelMat, vecRotation[1]+animRotY, vec3(0.0,1.0,0.0));
    modelMat = glm::rotate(modelMat, vecRotation[2]+animRotZ, vec3(0.0,0.0,1.0));
    modelMat = glm::scale(modelMat, vecScale);

    return modelMat;
}

mat4 Transform::getModelToChild(mat4 modelMat){

    mat4 model = modelMat;



    if(!samePosition){
        model = translate(model, positionToSend);
    } else {
        model = translate(model, vecPosition);
    }

    if(!sameRotation){
        model = glm::rotate(model, rotationToSend[0]+animChildRotX, vec3(1.0,0.0,0.0));
        model = glm::rotate(model, rotationToSend[1]+animChildRotY, vec3(0.0,1.0,0.0));
        model = glm::rotate(model, rotationToSend[2]+animChildRotZ, vec3(0.0,0.0,1.0));
    } else {
        model = glm::rotate(model, vecRotation[0]+animRotX, vec3(1.0,0.0,0.0));
        model = glm::rotate(model, vecRotation[1]+animRotY, vec3(0.0,1.0,0.0));
        model = glm::rotate(model, vecRotation[2]+animRotZ, vec3(0.0,0.0,1.0));
    }

    return model;

}

void Transform::update(){

    if(b_animRotX){ animRotX += animRotSpeedX; }
    if(b_animRotY){ animRotY += animRotSpeedY; }
    if(b_animRotZ){ animRotZ += animRotSpeedZ; }

    if(b_animChildRotX){ animChildRotX += animChildRotSpeedX; }
    if(b_animChildRotY){ animChildRotY += animChildRotSpeedY; }
    if(b_animChildRotZ){ animChildRotZ += animChildRotSpeedZ; }

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
        ImGui::SameLine(); ImGui::Text("speed X: "); ImGui::SameLine();
        ImGui::DragFloat("speedX", &animRotSpeedX, 0.002f, lowestValue, highestValue, format);
        ImGui::Text("Rotation Y : ");
        ImGui::SameLine(); ImGui::Checkbox("##RotY", &b_animRotY);
        ImGui::SameLine(); ImGui::Text("speed Y: "); ImGui::SameLine();
        ImGui::DragFloat("speedY", &animRotSpeedY, 0.002f, lowestValue, highestValue, format);
        ImGui::Text("Rotation Z : ");
        ImGui::SameLine(); ImGui::Checkbox("##RotZ", &b_animRotZ);
        ImGui::SameLine(); ImGui::Text("speed Z: "); ImGui::SameLine();
        ImGui::DragFloat("speedZ", &animRotSpeedZ, 0.002f, lowestValue, highestValue, format);

        ImGui::TreePop();
    }

    int node_flags_child = 0;
    bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)1, node_flags_child, "Model Matrix to child");

    if (node_open) {

        ImGui::Text("Same position as parent");
        ImGui::Checkbox("##TransformSamePositionAsParent", &samePosition);
        if(!samePosition){
            ImGui::SameLine(); ImGui::Text("Position: "); ImGui::SameLine();
            ImGui::DragFloat3("##position", &positionToSend[0], 0.01f, lowestValue, highestValue, format);
        }

        ImGui::Text("Same rotation as parent");
        ImGui::Checkbox("##TransformSameRotationAsParent", &sameRotation);
        if(!sameRotation){
            ImGui::SameLine(); ImGui::Text("Rotation: "); ImGui::SameLine();
            ImGui::DragFloat3("##rotation", &rotationToSend[0], 0.01f, lowestValue, highestValue, format);
        }

        /*ImGui::Text("Same matrix as parent");
        ImGui::SameLine(); ImGui::Checkbox("##TransformSameAsParent", &sameAsModelMat);
        ImGui::Text("Position: "); ImGui::SameLine();
        ImGui::DragFloat3("position", &positionToSend[0], 0.01f, lowestValue, highestValue, format);
        ImGui::Text("Rotation: "); ImGui::SameLine();
        ImGui::DragFloat3("rotation", &rotationToSend[0], 0.01f, lowestValue, highestValue, format);
        ImGui::Text("Scale: "); ImGui::SameLine();
        ImGui::DragFloat3("scale", &scaleToSend[0], 0.005f, 0.0f, highestValue, format);*/

        int anim_node_flags_child = 0;
        bool node_open_anim_child = ImGui::TreeNodeEx((void*)(intptr_t)2, anim_node_flags_child, "Animation Child");

        if (node_open_anim_child) {
            ImGui::Text("Rotation X : ");
            ImGui::SameLine(); ImGui::Checkbox("##ChildRotX", &b_animChildRotX);
            ImGui::SameLine(); ImGui::Text("speed X: "); ImGui::SameLine();
            ImGui::DragFloat("speedX", &animChildRotSpeedX, 0.002f, lowestValue, highestValue, format);
            ImGui::Text("Rotation Y : ");
            ImGui::SameLine(); ImGui::Checkbox("##ChildRotY", &b_animChildRotY);
            ImGui::SameLine(); ImGui::Text("speed Y: "); ImGui::SameLine();
            ImGui::DragFloat("speedY", &animChildRotSpeedY, 0.002f, lowestValue, highestValue, format);
            ImGui::Text("Rotation Z : ");
            ImGui::SameLine(); ImGui::Checkbox("##ChildRotZ", &b_animChildRotZ);
            ImGui::SameLine(); ImGui::Text("speed Z: "); ImGui::SameLine();
            ImGui::DragFloat("speedZ", &animChildRotSpeedZ, 0.002f, lowestValue, highestValue, format);

            ImGui::TreePop();
        }


        ImGui::TreePop();
    }

    if(ImGui::Button("Reset Animation")){
        reset();
    }

    // to hide label of the input
    ImGui::PopItemWidth();
}


void Transform::setAnimation(bool b_X, bool b_Y, bool b_Z, float SpeedX, float SpeedY, float SpeedZ){
    b_animRotX = b_X; b_animRotY = b_Y; b_animRotZ = b_Z;
    animRotSpeedX = SpeedX; animRotSpeedY = SpeedY; animRotSpeedZ = SpeedZ;
}


void Transform::setChildAnimation(bool b_X, bool b_Y, bool b_Z, float SpeedX, float SpeedY, float SpeedZ){
    b_animChildRotX = b_X; b_animChildRotY = b_Y; b_animChildRotZ = b_Z;
    animChildRotSpeedX = SpeedX; animChildRotSpeedY = SpeedY; animChildRotSpeedZ = SpeedZ;
}

void Transform::setSameAsParent(bool position, bool rotation){
    samePosition = position;
    sameRotation = rotation;
}


vec3 Transform::getPosition(){
    return vecPosition;
}

vec3 Transform::getRotation(){
    return vecRotation;
}

vec3 Transform::getScale(){
    return vecScale;
}