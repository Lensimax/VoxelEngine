
#include "UI.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


UI::UI() : m_scene(NULL), m_mainRenderer(NULL), m_inputManager(NULL), m_window(NULL), m_selectedID(0), m_hasToBeDisplayed(true) {
}

UI::~UI(){

}

void UI::drawUI(){
    if(!m_hasToBeDisplayed){
        return;
    }
    // createInfoWindow();

    if(m_scene != NULL){
        createUISceneManager(m_scene);
    }

    if(m_mainRenderer != NULL){
        m_mainRenderer->createUI();
    }

    if(m_inputManager != NULL){
        m_inputManager->createUI();
    }

   
}


void UI::createInfoWindow(){
    ImGui::Begin("Debug");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}


void UI::displayEngineNode(std::vector<GameObject*> obj){

    char strobj[1024]; // label object


    for(unsigned int i=0; i<obj.size(); i++){
        ImGuiTreeNodeFlags node_flags = 0;
        int id = obj[i]->getID();

        sprintf(strobj,"##obj %i", id); // hidden label


        if(obj[i]->m_listOfChildren.size() == 0){
            bool is_selected = m_selectedID == id;
            if(ImGui::Selectable(strobj, is_selected)){
                m_selectedID = obj[i]->getID();
            }
            ImGui::SameLine();
            ImGui::Text(obj[i]->getName().c_str());
        } else {
            bool node_open = ImGui::TreeNodeEx(strobj, node_flags);
            ImGui::SameLine();
            // add selectable
            bool is_selected = m_selectedID == id;
            if(ImGui::Selectable(strobj, is_selected)){
                m_selectedID = obj[i]->getID();
            }
            ImGui::SameLine();
            ImGui::Text(obj[i]->getName().c_str());

            // if the node is open
            if(node_open){
                displayEngineNode(obj[i]->m_listOfChildren);

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
            if (ImGui::BeginMenu("Scene Example")){
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")){
            if (ImGui::MenuItem("Add GameObject", "Ctrl+T")) { scene->addGameObject(); }
            if (ImGui::MenuItem("Add Cube")) { scene->addCube(); }
            if (ImGui::MenuItem("Delete selection", "SUPPR")) { scene->deleteObject(m_selectedID); }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")){
            if (ImGui::MenuItem("Toggle wire frame","CTRL+F")) { if(m_mainRenderer != NULL) m_mainRenderer->toggleWire(); }
            if (ImGui::MenuItem("Toggle grid")) { if(m_mainRenderer != NULL) m_mainRenderer->toggleGrid(); }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window")){
            if (ImGui::MenuItem("640*480")) { if(m_window != NULL) glfwSetWindowSize(m_window, 640, 480); }
            if (ImGui::MenuItem("1280*720")) { if(m_window != NULL) glfwSetWindowSize(m_window, 1280, 720); }
            if (ImGui::MenuItem("1920*1080")) { if(m_window != NULL) glfwSetWindowSize(m_window, 1920, 1080); }
            if (ImGui::BeginMenu("Limit FPS ")){
                extern float global_limitFramerate;
                if (ImGui::MenuItem("30 FPS")) { global_limitFramerate = 30.0f; }
                if (ImGui::MenuItem("60 FPS")) { global_limitFramerate = 60.0f; }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Animation")){
            if (ImGui::MenuItem("Pause/Resume", "CTRL+P")) { scene->togglePause(); }
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Rendering Settings")){
            if (ImGui::MenuItem("Toggle Cull Face")) { m_mainRenderer->toggleCullface(); }
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

    if(m_selectedID > -1){
        char idInspector[10];
        sprintf(idInspector, "right");
        scene->createUIAtID(m_selectedID, idInspector);
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
    return m_selectedID;
}


void UI::set(Scene *sc){
    m_scene = sc;
}


void UI::set(MainRenderer *main){
    m_mainRenderer = main;
}

void UI::set(GLFWwindow *win){
    m_window = win;
}
