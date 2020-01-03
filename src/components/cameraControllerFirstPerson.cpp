#include <imgui.h>
#include "cameraControllerFirstPerson.h"
#include "../engineClass/gameObject.h"



CameraControllerFirstPerson::CameraControllerFirstPerson() : m_sensitivityRotateWorld(glm::vec2(0.5f)), m_scrollZoomSensitivity(1.f) {

    setName("Camera Controller");

}


CameraControllerFirstPerson::~CameraControllerFirstPerson(){

}

void CameraControllerFirstPerson::update(){
    if(!m_active){
        return;
    }

    ImGuiIO& io = ImGui::GetIO();

    // CAMERA EDITOR CONTROL
    if(!io.WantCaptureMouse){
        
        glm::vec3 position = m_gameobject->getTransform()->getPosition();
        glm::vec3 rotation = m_gameobject->getTransform()->getRotation();
 
        float dx = glm::sin(rotation.y);
        float dz = glm::cos(rotation.y);

        glm::vec3 move = glm::vec3(0,0,0);
        // mouse wheel
        if(io.MouseWheel != 0.0){

            const mat4 inverted = glm::inverse(m_gameobject->getTransform()->getModelMat());
            const vec3 forward = normalize(glm::vec3(inverted[2]));

            move -= io.MouseWheel*forward*m_scrollZoomSensitivity;
            
        }

        // right click
        if(ImGui::IsMouseDown(1)){
            glm::vec2 vectorTranslate = glm::vec2(io.MouseDelta.x, io.MouseDelta.y);
            vectorTranslate *= -1.0f;
            vectorTranslate *= 0.01f;
            //m_gameobject->getTransform()->addTranslation(glm::vec3(vectorTranslate.x, vectorTranslate.y,0));

            move.x += vectorTranslate.x*dz;
            move.z += vectorTranslate.x*dx;

            move.y -= vectorTranslate.y;
        }

        // Left click
        if(ImGui::IsMouseDown(0)){

            // ROTATION OF the world
            glm::vec2 vectorMouse = glm::vec2(io.MouseDelta.x, io.MouseDelta.y);
            vectorMouse *= -1.0f;
            vectorMouse *= m_sensitivityRotateWorld*0.01f;

            //m_gameobject->getTransform()->rotatefromScreen(vectorMouse);

            rotation.x -= vectorMouse.y;
            rotation.y -= vectorMouse.x;

        }

        m_gameobject->getTransform()->setPosition(position + move);
        m_gameobject->getTransform()->setRotation(rotation);
    }

}


void CameraControllerFirstPerson::createUI(){
    ImGui::Text("Rotation world sensitivity : (x0.01)");
    ImGui::DragFloat2("##rotationsensitivity", &m_sensitivityRotateWorld[0], 0.01, 0.0, 100.);
    ImGui::Text("Scroll zoom sensitivity : ");
    ImGui::DragFloat("##m_scrollZoomSensitivity", &m_scrollZoomSensitivity, 0.01, 0.0, 100.);
}