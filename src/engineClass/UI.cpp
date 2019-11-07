
#include "UI.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


UI::UI(){
    selectedID = 0;
    hasToBeDisplayed = true;
    scene = NULL;
    mainRenderer = NULL;
    window = NULL;
}

UI::~UI(){

}

void UI::drawUI(){
    if(!hasToBeDisplayed){
        return;
    }
    createInfoWindow();

    if(scene != NULL){
        createUISceneManager(scene);
    }
}


void UI::createInfoWindow(){
    ImGui::Begin("Info Window");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}


void UI::displayEngineNode(std::vector<EngineObject*> obj){

    char strobj[1024]; // label object


    for(unsigned int i=0; i<obj.size(); i++){
        ImGuiTreeNodeFlags node_flags = 0;
        int id = obj[i]->getID();

        sprintf(strobj,"##obj %i", id); // hidden label


        if(obj[i]->listOfChildren.size() == 0){
            bool is_selected = selectedID == id;
            if(ImGui::Selectable(strobj, is_selected)){
                selectedID = obj[i]->getID();
            }
            ImGui::SameLine();
            ImGui::Text(obj[i]->getName().c_str());
        } else {
            bool node_open = ImGui::TreeNodeEx(strobj, node_flags);
            ImGui::SameLine();
            // add selectable
            bool is_selected = selectedID == id;
            if(ImGui::Selectable(strobj, is_selected)){
                selectedID = obj[i]->getID();
            }
            ImGui::SameLine();
            ImGui::Text(obj[i]->getName().c_str());

            // if the node is open
            if(node_open){
                displayEngineNode(obj[i]->listOfChildren);

                ImGui::TreePop();
            }

        }




    }

}

void UI::createUISceneManager(Scene *scene){
    float sizeLeft = 200;
    float sizeRight = 200;


    std::vector<std::string> listOfObjects;
    std::vector<int> listOfID;
    scene->getAllObjects(listOfObjects, listOfID);


    ImGui::Begin("Scene Manager", NULL, ImGuiWindowFlags_MenuBar);

    if(scene == NULL) return;

    // Menu on the top
    if (ImGui::BeginMenuBar()){
        if (ImGui::BeginMenu("File")){
            if (ImGui::MenuItem("New Scene", "WIP")) { /* Do stuff */ }
            if (ImGui::MenuItem("Load Scene", "WIP")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save Scene", "WIP")) { /* Do stuff */ }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")){
            if (ImGui::MenuItem("Add EngineObject", "Ctrl+T")) { scene->addEngineObject(); }
            if (ImGui::MenuItem("Add MeshObject", "Ctrl+N")) { scene->addMeshObject(); }
            if (ImGui::MenuItem("Add Plane", "")) { scene->addPlane(); }
            if (ImGui::MenuItem("Add Cube", "WIP")) { /* Do stuff */ }
            if (ImGui::MenuItem("Add Sphere")) { scene->addSphere();}
            if (ImGui::MenuItem("Delete selection", "SUPPR")) { scene->deleteObject(selectedID); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")){
            if (ImGui::MenuItem("Toggle wire frame")) { if(mainRenderer != NULL) mainRenderer->toggleWire(); }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window")){
            if (ImGui::MenuItem("640*480")) { if(window != NULL) glfwSetWindowSize(window, 640, 480); }
            if (ImGui::MenuItem("1280*720")) { if(window != NULL) glfwSetWindowSize(window, 1280, 720); }
            if (ImGui::MenuItem("1920*1080")) { if(window != NULL) glfwSetWindowSize(window, 1920, 1080); }
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Animation")){
            if (ImGui::MenuItem("Pause/Resume", "CTRL+P")) { scene->togglePause(); }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }


    DrawSplitter(true, 10.0f, &sizeLeft, &sizeRight, 10.0f, 10.f); // code above

    ImGui::BeginChild("left", ImVec2(sizeLeft, 0), true); // pass width here

    displayEngineNode(scene->objectsEngine);


    ImGui::EndChild();

    ImGui::SameLine();

    // pour afficher le détail de l'objet selectionné
    ImGui::BeginChild("right", ImVec2(0, -ImGui::GetFrameHeight()),true); // pass width here

    if(selectedID > -1){
        char idInspector[10];
        sprintf(idInspector, "right");
        scene->createUIAtID(selectedID, idInspector);
    }

    ImGui::EndChild();

    ImGui::End();
}


// SPLITTER
void UI::DrawSplitter(int split_vertically, float thickness, float* size0, float* size1, float min_size0, float min_size1)
{
    ImVec2 backup_pos = ImGui::GetCursorPos();
    if (split_vertically)
        ImGui::SetCursorPosY(backup_pos.y + *size0);
    else
        ImGui::SetCursorPosX(backup_pos.x + *size0);

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0,0,0,0));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0,0,0,0));          // We don't draw while active/pressed because as we move the panes the splitter button will be 1 frame late
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.6f,0.6f,0.6f,0.10f));
    ImGui::Button("##Splitter", ImVec2(!split_vertically ? thickness : -1.0f, split_vertically ? thickness : -1.0f));
    ImGui::PopStyleColor(3);

    ImGui::SetItemAllowOverlap(); // This is to allow having other buttons OVER our splitter.

    if (ImGui::IsItemActive())
    {
        float mouse_delta = split_vertically ? ImGui::GetIO().MouseDelta.y : ImGui::GetIO().MouseDelta.x;

        // Minimum pane size
        if (mouse_delta < min_size0 - *size0)
            mouse_delta = min_size0 - *size0;
        if (mouse_delta > *size1 - min_size1)
            mouse_delta = *size1 - min_size1;

        // Apply resize
        *size0 += mouse_delta;
        *size1 -= mouse_delta;
    }
    ImGui::SetCursorPos(backup_pos);
}

int UI::getSelected(){
    return selectedID;
}


void UI::toggleHasToBeDisplayed(){
    hasToBeDisplayed = !hasToBeDisplayed;
}



void UI::set(Scene *sc){
    scene = sc;
}


void UI::set(MainRenderer *main){
    mainRenderer = main;
}

void UI::set(GLFWwindow *win){
    window = win;
}
