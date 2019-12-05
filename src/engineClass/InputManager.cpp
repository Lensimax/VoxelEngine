#include "InputManager.h"
#include <imgui.h>

#include <iostream>

InputManager::InputManager() : m_sensitivityRotateWorld(glm::vec2(1)), m_scrollZoomSensitivity(1.f) {
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

    // WORLD CONTROL
    if(!io.WantCaptureMouse){
        if(io.MouseWheel != 0.0){
            if(m_renderer != NULL){
                m_renderer->getTransformEditor()->addTranslation(glm::vec3(0,0,io.MouseWheel*0.5));
            }
        }

        if(ImGui::IsMouseDown(1)){
            glm::vec2 vectorTranslate = glm::vec2(io.MouseDelta.x, io.MouseDelta.y);
            vectorTranslate.y *= -1;
            vectorTranslate *= 0.01f;
            m_renderer->getTransformEditor()->addTranslation(glm::vec3(vectorTranslate.x, vectorTranslate.y,0));
        }


        if(ImGui::IsMouseDown(0)){

            // ROTATION OF the world
            glm::vec2 vectorMouse = glm::vec2(io.MouseDelta.x, io.MouseDelta.y);
            vectorMouse *= m_sensitivityRotateWorld*0.01f;

            if(m_renderer != NULL){
                m_renderer->getTransformEditor()->rotatefromScreen(vectorMouse);
            }
        }
    }
    



    if(m_scene != NULL && m_ui != NULL){

        // suppr

        // if(ImGui::IsKeyPressed(ImGuiKey_Delete)){
        if(ImGui::IsKeyPressed(261)){ // 0x105
            m_scene->deleteObject(m_ui->getSelected());

        }

        if(io.KeyCtrl && ImGui::IsKeyPressed('T')){
            m_scene->addEngineObject();
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
    }


}
