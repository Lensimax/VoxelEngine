

#include "transform.h"


#include <imgui.h>

#include <stdio.h>


Transform::Transform(vec3 center, vec3 position, vec3 scale, vec3 rotation) : m_position(position),m_scale(scale), m_rotation(rotation), m_center(center), m_translateAfter(glm::vec3(0)),
                                        m_positionToSend(position), m_scaleToSend(glm::vec3(1)), m_rotationToSend(glm::vec3(0)), m_samePosition(true), m_sameRotation(true), 
                                        m_animRotSpeedX(m_defaultSpeed), m_animRotSpeedY(m_defaultSpeed), m_animRotSpeedZ(m_defaultSpeed),
                                        m_animChildRotSpeedX(m_defaultSpeed), m_animChildRotSpeedY(m_defaultSpeed), m_animChildRotSpeedZ(m_defaultSpeed), 
                                        m_b_animRotX(false), m_b_animRotY(false), b_animRotZ(false), m_b_animChildRotX(false), m_b_animChildRotY(false), m_b_animChildRotZ(false){


    reset();
    
}



Transform::~Transform(){

}


void Transform::reset(){
    m_animRotX = 0, m_animRotY = 0; m_animRotZ = 0;
    m_animChildRotX = 0; m_animChildRotY = 0; m_animChildRotZ = 0;
}

void Transform::setPosition(vec3 position){
    m_position = position;
}
void Transform::setRotation(vec3 axis){
    m_rotation = axis;
}

void Transform::rotatefromScreen(vec2 v){
    m_rotation.x += v.y;
    m_rotation.y += v.x;
}

void Transform::setCenter(vec3 center) {
    m_center = center;
}

void Transform::scale(vec3 scale){
    m_scale = scale;
}

void Transform::addTranslation(vec3 t){
    m_position += t;
}

void Transform::addTranslationAfter(vec3 t){
    m_translateAfter += t;
}



mat4 Transform::getModelMat(mat4 modelMat){
    modelMat = translate(modelMat, m_position);
    // modelMat = translate(modelMat, center);
    modelMat = glm::rotate(modelMat, m_rotation[0]+m_animRotX, vec3(1.0,0.0,0.0));
    modelMat = glm::rotate(modelMat, m_rotation[1]+m_animRotY, vec3(0.0,1.0,0.0));
    modelMat = glm::rotate(modelMat, m_rotation[2]+m_animRotZ, vec3(0.0,0.0,1.0));
    modelMat = translate(modelMat, m_translateAfter);
    modelMat = glm::scale(modelMat, m_scale);

    m_test = modelMat;
    return modelMat;
}

mat4 Transform::getModelToChild(mat4 modelMat){

    mat4 model = modelMat;



    if(!m_samePosition){
        model = translate(model, m_positionToSend);
    } else {
        model = translate(model, m_position);
    }

    if(!m_sameRotation){
        model = glm::rotate(model, m_rotationToSend[0]+m_animChildRotX, vec3(1.0,0.0,0.0));
        model = glm::rotate(model, m_rotationToSend[1]+m_animChildRotY, vec3(0.0,1.0,0.0));
        model = glm::rotate(model, m_rotationToSend[2]+m_animChildRotZ, vec3(0.0,0.0,1.0));
    } else {
        model = glm::rotate(model, m_rotation[0]+m_animRotX, vec3(1.0,0.0,0.0));
        model = glm::rotate(model, m_rotation[1]+m_animRotY, vec3(0.0,1.0,0.0));
        model = glm::rotate(model, m_rotation[2]+m_animRotZ, vec3(0.0,0.0,1.0));
    }

    model = translate(model, m_translateAfter);    

    return model;

}

void Transform::update(){

    if(m_b_animRotX){ m_animRotX += m_animRotSpeedX; }
    if(m_b_animRotY){ m_animRotY += m_animRotSpeedY; }
    if(b_animRotZ){ m_animRotZ += m_animRotSpeedZ; }

    if(m_b_animChildRotX){ m_animChildRotX += m_animChildRotSpeedX; }
    if(m_b_animChildRotY){ m_animChildRotY += m_animChildRotSpeedY; }
    if(m_b_animChildRotZ){ m_animChildRotZ += m_animChildRotSpeedZ; }

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
    ImGui::DragFloat3("##position", &m_position[0], 0.01f, lowestValue, highestValue, format);
    ImGui::Text("Rotation: "); ImGui::SameLine();
    ImGui::DragFloat3("##rotation", &m_rotation[0], 0.01f, lowestValue, highestValue, format);
    ImGui::Text("Scale: "); ImGui::SameLine();
    ImGui::DragFloat3("##scale", &m_scale[0], 0.005f, 0.0f, highestValue, format);

    ImGui::Text("[%4f, %4f, %4f, %4f\n%4f, %4f, %4f, %4f\n%4f, %4f, %4f, %4f\n%4f, %4f, %4f, %4f]\n", m_test[0][0], m_test[0][1], m_test[0][2], m_test[0][3], m_test[1][0],
    m_test[1][1], m_test[1][2], m_test[1][3], m_test[2][0], m_test[2][1], m_test[2][2], m_test[2][3], m_test[3][0], m_test[3][1], m_test[3][2], m_test[3][3]);

     ImGui::Separator();
    glm::mat4 view = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
    ImGui::Text("[%4f, %4f, %4f, %4f\n%4f, %4f, %4f, %4f\n%4f, %4f, %4f, %4f\n%4f, %4f, %4f, %4f]\n", view[0][0], view[0][1], view[0][2], view[0][3], view[1][0],
    view[1][1], view[1][2], view[1][3], view[2][0], view[2][1], view[2][2], view[2][3], view[3][0], view[3][1], view[3][2], view[3][3]);


    /*bool node_open_anim = ImGui::TreeNodeEx((void*)(intptr_t)0, node_flags, "Animation");

    if (node_open_anim) {
        ImGui::Text("Rotation X : ");
        ImGui::SameLine(); ImGui::Checkbox("##RotX", &m_b_animRotX);
        ImGui::SameLine(); ImGui::Text("speed X: "); ImGui::SameLine();
        ImGui::DragFloat("##speedX", &m_animRotSpeedX, 0.002f, lowestValue, highestValue, format);
        ImGui::Text("Rotation Y : ");
        ImGui::SameLine(); ImGui::Checkbox("##RotY", &m_b_animRotY);
        ImGui::SameLine(); ImGui::Text("speed Y: "); ImGui::SameLine();
        ImGui::DragFloat("##speedY", &m_animRotSpeedY, 0.002f, lowestValue, highestValue, format);
        ImGui::Text("Rotation Z : ");
        ImGui::SameLine(); ImGui::Checkbox("##RotZ", &b_animRotZ);
        ImGui::SameLine(); ImGui::Text("speed Z: "); ImGui::SameLine();
        ImGui::DragFloat("##speedZ", &m_animRotSpeedZ, 0.002f, lowestValue, highestValue, format);

        ImGui::TreePop();
    }

    int node_flags_child = 0;
    bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)1, node_flags_child, "Model Matrix to child");

    if (node_open) {

        ImGui::Text("Same position as parent");
        ImGui::Checkbox("##Transformm_samePositionAsParent", &m_samePosition);
        if(!m_samePosition){
            ImGui::SameLine(); ImGui::Text("Position: "); ImGui::SameLine();
            ImGui::DragFloat3("##position", &m_positionToSend[0], 0.01f, lowestValue, highestValue, format);
        }

        ImGui::Text("Same rotation as parent");
        ImGui::Checkbox("##Transformm_sameRotationAsParent", &m_sameRotation);
        if(!m_sameRotation){
            ImGui::SameLine(); ImGui::Text("Rotation: "); ImGui::SameLine();
            ImGui::DragFloat3("##rotation", &m_rotationToSend[0], 0.01f, lowestValue, highestValue, format);
        }

        int anim_node_flags_child = 0;
        bool node_open_anim_child = ImGui::TreeNodeEx((void*)(intptr_t)2, anim_node_flags_child, "Animation Child");

        if (node_open_anim_child) {
            ImGui::Text("Rotation X : ");
            ImGui::SameLine(); ImGui::Checkbox("##ChildRotX", &m_b_animChildRotX);
            ImGui::SameLine(); ImGui::Text("speed X: "); ImGui::SameLine();
            ImGui::DragFloat("##speedChildX", &m_animChildRotSpeedX, 0.002f, lowestValue, highestValue, format);
            ImGui::Text("Rotation Y : ");
            ImGui::SameLine(); ImGui::Checkbox("##ChildRotY", &m_b_animChildRotY);
            ImGui::SameLine(); ImGui::Text("speed Y: "); ImGui::SameLine();
            ImGui::DragFloat("##speedChildY", &m_animChildRotSpeedY, 0.002f, lowestValue, highestValue, format);
            ImGui::Text("Rotation Z : ");
            ImGui::SameLine(); ImGui::Checkbox("##ChildRotZ", &m_b_animChildRotZ);
            ImGui::SameLine(); ImGui::Text("speed Z: "); ImGui::SameLine();
            ImGui::DragFloat("##speedChildZ", &m_animChildRotSpeedZ, 0.002f, lowestValue, highestValue, format);

            ImGui::TreePop();
        }


        ImGui::TreePop();
    }

    if(ImGui::Button("Reset Animation")){
        reset();
    }*/

    // to hide label of the input
    ImGui::PopItemWidth();
}


void Transform::setAnimation(bool b_X, bool b_Y, bool b_Z, float SpeedX, float SpeedY, float SpeedZ){
    m_b_animRotX = b_X; m_b_animRotY = b_Y; b_animRotZ = b_Z;
    m_animRotSpeedX = SpeedX; m_animRotSpeedY = SpeedY; m_animRotSpeedZ = SpeedZ;
}


void Transform::setChildAnimation(bool b_X, bool b_Y, bool b_Z, float SpeedX, float SpeedY, float SpeedZ){
    m_b_animChildRotX = b_X; m_b_animChildRotY = b_Y; m_b_animChildRotZ = b_Z;
    m_animChildRotSpeedX = SpeedX; m_animChildRotSpeedY = SpeedY; m_animChildRotSpeedZ = SpeedZ;
}

void Transform::setSameAsParent(bool position, bool rotation){
    m_samePosition = position;
    m_sameRotation = rotation;
}


vec3 Transform::getPosition(){
    return m_position;
}

vec3 Transform::getRotation(){
    return m_rotation;
}

vec3 Transform::getScale(){
    return m_scale;
}

void Transform::decompose(mat4 mat){


    printf("(%f, %f, %f, %f)\n", mat[0][0],mat[0][1], mat[0][2], mat[0][3]);
    printf("(%f, %f, %f, %f)\n", mat[1][0],mat[1][1], mat[1][2], mat[1][3]);
    printf("(%f, %f, %f, %f)\n", mat[2][0],mat[2][1], mat[2][2], mat[2][3]);
    printf("(%f, %f, %f, %f)\n\n", mat[3][0],mat[3][1], mat[3][2], mat[3][3]);

    m_position = vec3(mat[0][3], mat[1][3], mat[2][3]);


    m_rotation = rotationMatrixToEulerAngles(mat);
    m_scale = glm::vec3(1,1,1);

}

vec3 Transform::rotationMatrixToEulerAngles(mat4 r){
     
    float sy = sqrt(r[0][0] * r[0][0] +  r[1][0] * r[1][0] );
 
    bool singular = sy < 1e-6; // If
 
    float x, y, z;
    if (!singular)
    {
        x = atan2(r[2][1] , r[2][2]);
        y = atan2(-r[2][0], sy);
        z = atan2(r[1][0], r[0][0]);
    }
    else
    {
        x = atan2(-r[1][2], r[1][1]);
        y = atan2(-r[2][0], sy);
        z = 0;
    }
    return vec3(x, y, z);

}