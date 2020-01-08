#include "InputManager.h"
#include <imgui.h>

#include "UI.h"

#include <iostream>

InputManager::InputManager(){
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

    if(m_scene != NULL && m_ui != NULL){

        // suppr

        // if(ImGui::IsKeyPressed(ImGuiKey_Delete)){
        if(ImGui::IsKeyPressed(261)){ // 0x105
            m_scene->deleteObject(m_ui->getSelected());

        }

        if(io.KeyCtrl && ImGui::IsKeyPressed('T')){
            m_scene->addGameObject();
        }
        if(io.KeyCtrl && ImGui::IsKeyPressed('O')){
            m_scene->addCube();
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
