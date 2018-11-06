
#include "imgui.h"
#include "imgui_internal.h"
#include "impl/imgui_impl_glfw.h"
#include "impl/imgui_impl_opengl3.h"
#include <stdio.h>

#ifndef GLM_H
#define GLM_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#endif


#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL definitions


#include "../mainRenderer.h"
#include <iostream>
// #include <string>
// #include <vector>

/*bool Splitter(bool split_vertically, float thickness, float* size1, float* size2, float min_size1, float min_size2, float splitter_long_axis_size = -1.0f)
{
    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = g.CurrentWindow;
    ImGuiID id = window->GetID("##Splitter");
    ImRect bb;
    bb.Min = window->DC.CursorPos + (split_vertically ? ImVec2(*size1, 0.0f) : ImVec2(0.0f, *size1));
    bb.Max = bb.Min + ImGui::CalcItemSize(split_vertically ? ImVec2(thickness, splitter_long_axis_size) : ImVec2(splitter_long_axis_size, thickness), 0.0f, 0.0f);
    return ImGui::SplitterBehavior(bb,id, split_vertically ? ImGuiAxis_X : ImGuiAxis_Y, size1, size2, min_size1, min_size2, 0.0f);
}*/

void DrawSplitter(int split_vertically, float thickness, float* size0, float* size1, float min_size0, float min_size1)
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

static void glfw_error_callback(int error, const char* description){
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}


int initializeOpenGLLoader(){
    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() != 0;
#endif
    if(err){
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    } else {
        return 0;
    }
}

static void createInfoWindow(){
    ImGui::Begin("Info Window");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

using namespace ImGui;

int main(int, char**){

    glfwSetErrorCallback(glfw_error_callback);


    // init glfw: if it return an error we stop
    if (!glfwInit()){
        return 1;
    }

    // constraint on glsl_version
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    // create window
    GLFWwindow* window = glfwCreateWindow(1000, 600, "Green Engine", NULL, NULL);
    if (window == NULL){
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if(initializeOpenGLLoader() == 1){
        return 1;
    }
    //ImGuiWindow* windowImGui = ImGui::GetCurrentWindow();

    // A EXPLIQUER
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup style
    ImGui::StyleColorsDark();

    MainRenderer *renderer = new MainRenderer();
    renderer->initializeGL();



    float sizeLeft = 200;
    float sizeRight = 200;



    // the window is runnin
    while (!glfwWindowShouldClose(window)){

        glfwPollEvents();


        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();



        createInfoWindow();

        std::vector<std::string> listOfObjects = renderer->getNameOfAllObjects();
        Begin("Project");

        DrawSplitter(false, 10.0f, &sizeLeft, &sizeRight, 10.0f, 10.f); // code above

        ImGui::BeginChild("left", ImVec2(sizeLeft, 0), true); // pass width here
        ImGui::Text("Project");

        static int selected = -1;
        for (unsigned int i = 0; i < listOfObjects.size(); i++){

            if (ImGui::Selectable(listOfObjects[i].c_str(), selected == (int)i))
                selected = i;
        }

        ImGui::EndChild();

        ImGui::SameLine();

        ImGui::BeginChild("right", ImVec2(0, -ImGui::GetFrameHeight()),true); // pass width here

        if(selected > -1){
            char idInspector[10];
            sprintf(idInspector, "right");
            renderer->createUIAtID(selected, idInspector);
        }

        ImGui::EndChild();

        End();


        /* RENDERING */
        ImGui::EndFrame();
        ImGui::Render();
        glfwMakeContextCurrent(window);

        glViewport(0, 0, display_w, display_h);
        glClearColor(0.239f, 0.478f, 0.647f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        //renderer->paintGL(display_w, display_h);

        /* draw the widget */
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(window);
        glfwSwapBuffers(window);

    }


    delete renderer;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();


    return 0;
}
