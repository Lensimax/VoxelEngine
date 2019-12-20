#include "InputManager.h"
#include <imgui.h>

#include "UI.h"

#include <iostream>

InputManager::InputManager() : m_sensitivityRotateWorld(glm::vec2(0.5f)), m_scrollZoomSensitivity(1.f) {
}

InputManager::~InputManager(){

}

void InputManager::setScene(Scene *sc){
    m_scene = sc;
}

void InputManager::setUI(UI *u){
    m_ui = u;
}

void InputManager::setRenderer(MainRenderer *r){
    m_renderer = r;
}

void InputManager::createUI(){

    if(m_ui == NULL){
        return;
    } else {
        if(!m_ui->hasToDisplayed()){ return; }
    }

    ImGui::Begin("Settings");

    ImGui::Text("Input Manager");
    ImGui::Separator();
    ImGui::Text("Rotation world sensitivity : (x0.01)");
    ImGui::DragFloat2("##rotationsensitivity", &m_sensitivityRotateWorld[0], 0.01, 0.0, 100.);
    ImGui::Text("Scroll zoom sensitivity : ");
    ImGui::DragFloat("##m_scrollZoomSensitivity", &m_scrollZoomSensitivity, 0.01, 0.0, 100.);


    ImGui::End();


    ImGuiIO& io = ImGui::GetIO();
    ImGui::Begin("Debug");
    ImGui::Separator();

    if(ImGui::IsMouseDown(0) && !io.WantCaptureMouse){
        ImGui::Text("Mouse click position : (%3f, %3f)", io.MousePos.x, io.MousePos.y);
        ImGui::Text("Vector mouse : (%2f, %2f)\n", io.MouseDelta.x, io.MouseDelta.y);
        
    } else {
        ImGui::Text("Mouse click position : \n");
        ImGui::Text("Vector mouse : \n");
    }

    ImGui::Text("Mouse wheel: %.1f", io.MouseWheel);

    ImGui::End();
}

void InputManager::update(){
    ImGuiIO& io = ImGui::GetIO();

    // CAMERA EDITOR CONTROL
    if(!io.WantCaptureMouse && m_renderer != NULL){
        
        glm::vec3 position = m_renderer->getCamera()->getTransform()->getPosition();
        glm::vec3 rotation = m_renderer->getCamera()->getTransform()->getRotation();
 
        float dx = glm::sin(rotation.y);
        float dz = glm::cos(rotation.y);

        glm::vec3 move = glm::vec3(0,0,0);
        // mouse wheel
        if(io.MouseWheel != 0.0){

            const mat4 inverted = glm::inverse(m_renderer->getCamera()->getTransform()->getModelMat());
            const vec3 forward = normalize(glm::vec3(inverted[2]));

            move -= io.MouseWheel*forward*m_scrollZoomSensitivity;
            
        }

        // right click
        if(ImGui::IsMouseDown(1)){
            glm::vec2 vectorTranslate = glm::vec2(io.MouseDelta.x, io.MouseDelta.y);
            vectorTranslate *= -1.0f;
            vectorTranslate *= 0.01f;
            //m_renderer->getCamera()->getTransform()->addTranslation(glm::vec3(vectorTranslate.x, vectorTranslate.y,0));

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

            //m_renderer->getCamera()->getTransform()->rotatefromScreen(vectorMouse);

            rotation.x -= vectorMouse.y;
            rotation.y -= vectorMouse.x;

        }

        m_renderer->getCamera()->getTransform()->setPosition(position + move);
        m_renderer->getCamera()->getTransform()->setRotation(rotation);

    }
    



    if(m_scene != NULL && m_ui != NULL){

        // suppr

        // if(ImGui::IsKeyPressed(ImGuiKey_Delete)){
        if(ImGui::IsKeyPressed(261)){ // 0x105
            m_scene->deleteObject(m_ui->getSelected());

        }

        if(io.KeyCtrl && ImGui::IsKeyPressed('T')){
            m_scene->addGameObject();
        }
    }

    if(io.KeyCtrl){
        if(ImGui::IsKeyPressed('P')){
            if(m_scene != NULL){
                m_scene->togglePause();
            }
        }
        if(ImGui::IsKeyPressed('F')){
            if(m_renderer != NULL){
                m_renderer->toggleWire();
            }
        }
        if(ImGui::IsKeyPressed('H')){
            if(m_ui != NULL){
                m_ui->toggleHasToBeDisplayed();
            }
        }
        if(ImGui::IsKeyPressed('U')){
            if(m_renderer != NULL){
                m_renderer->togglePlayMode();
            }
        }
    }


}
