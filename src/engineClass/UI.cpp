
#include "UI.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


UI::UI(){
    selectedID = -1;
    hasToBeDisplayed = true;
    scene = NULL;
    mainRenderer = NULL;
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


void UI::displayEngineNode(EngineObject *obj){

}

void UI::createUISceneManager(Scene *scene){
    float sizeLeft = 200;
    float sizeRight = 200;


    std::vector<std::string> listOfObjects;
    std::vector<int> listOfID;
    scene->getAllObjects(listOfObjects, listOfID);


    ImGui::Begin("Scene Manager", NULL, ImGuiWindowFlags_MenuBar);



    // Menu on the top
    if (ImGui::BeginMenuBar()){
        if (ImGui::BeginMenu("File")){
            if (ImGui::MenuItem("New Scene", "WIP")) { /* Do stuff */ }
            if (ImGui::MenuItem("Load Scene", "WIP")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save Scene", "WIP")) { /* Do stuff */ }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")){
            if (ImGui::MenuItem("Add MeshObject", "Ctrl+T")) { scene->addEngineObject(); }
            if (ImGui::MenuItem("Add MeshObject", "Ctrl+N")) { scene->addMeshObject(); }
            if (ImGui::MenuItem("Add Plane", "")) { scene->addPlane(); }
            if (ImGui::MenuItem("Add Cube", "WIP")) { /* Do stuff */ }
            if (ImGui::MenuItem("Add Sphere")) { scene->addSphere();}
            if (ImGui::MenuItem("Delete selection", "SUPPR")) { scene->deleteObject(selectedID); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")){
            if (ImGui::MenuItem("Toggle wire frame", "WIP")) { /*if(mainRenderer != NULL) mainRenderer->toggleWire();*/ }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }


    DrawSplitter(true, 10.0f, &sizeLeft, &sizeRight, 10.0f, 10.f); // code above

    ImGui::BeginChild("left", ImVec2(sizeLeft, 0), true); // pass width here


    // pour l'arbre de scene
    int node_clicked;
    char obj[1024]; // label object


    for(unsigned int i=0; i<scene->objectsEngine.size(); i++){
        ImGuiTreeNodeFlags node_flags = 0;
        sprintf(obj,"##obj %i", i); // hidden label

        if(scene->objectsEngine[i]->listOfChildren.size() == 0){
            node_flags = ImGuiTreeNodeFlags_NoTreePushOnOpen;
        }

        bool node_open = ImGui::TreeNodeEx(obj, node_flags);
        if (ImGui::IsItemClicked()){
            node_clicked = i;
        }


        ImGui::SameLine();
        ImGui::Text(listOfObjects[i].c_str());

    }

    printf("Node clicked\n");

    /*const bool is_selected = (selection_mask & (1 << i)) != 0;
    if (is_selected)
        node_flags |= ImGuiTreeNodeFlags_Selected;
    if (i < 3)
    {
        // Items 0..2 are Tree Node
        bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Node %d", i);
        if (ImGui::IsItemClicked())
            node_clicked = i;
        if (node_open)
        {
            ImGui::BulletText("Blah blah\nBlah Blah");
            ImGui::TreePop();
        }
    }
*/



    // on cherche celui selectionné
    /*char obj[1024];
    for (unsigned int i = 0; i < listOfObjects.size(); i++){
        sprintf(obj,"##obj %i", i); // hidden label
        bool is_selected = listOfID[i] == selectedID;
        if (ImGui::Selectable(obj, is_selected)){
              selectedID = listOfID[i];
        }
        ImGui::SameLine();
        ImGui::Text(listOfObjects[i].c_str());
    }
*/
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
