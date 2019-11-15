#include "InputManager.h"
#include <imgui.h>

#include <stdio.h>

InputManager::InputManager(){

}

InputManager::~InputManager(){

}

void InputManager::setScene(Scene *sc){
    scene = sc;
}

void InputManager::setUI(UI *u){
    ui = u;
}

void InputManager::setRenderer(MainRenderer *r){
    renderer = r;
}

void InputManager::update(){
    ImGuiIO& io = ImGui::GetIO();


    if(scene != NULL && ui != NULL){

        // suppr

        // if(ImGui::IsKeyPressed(ImGuiKey_Delete)){
        if(ImGui::IsKeyPressed(261)){ // 0x105
            scene->deleteObject(ui->getSelected());

        }

        if(io.KeyCtrl && ImGui::IsKeyPressed('N')){
            scene->addMeshObject();
        } else if(io.KeyCtrl && ImGui::IsKeyPressed('T')){
            scene->addEngineObject();
        }
    }

    if(io.KeyCtrl){
        if(ImGui::IsKeyPressed('P')){
            if(scene != NULL){
                scene->togglePause();
            }
        }
        if(ImGui::IsKeyPressed('F')){
            if(renderer != NULL){
                renderer->toggleWire();
            }
        }
        if(ImGui::IsKeyPressed('H')){
            if(ui != NULL){
                ui->toggleHasToBeDisplayed();
            }
        }
    }


}
