// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdio.h>
#include <glm/vec3.hpp>
#include <thread>

// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>

#include "engineClass/scene.h"
#include "engineClass/mainRenderer.h"
#include "engineClass/UI.h"
#include "engineClass/InputManager.h"

GLFWwindow* m_window;
int m_display_w, m_display_h;
Scene *m_scene;
InputManager *m_inputManager;
UI *m_ui;
MainRenderer *m_renderer;


const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif



void rendering(){
    assert(m_display_h > 0);
    m_renderer->paintGL(m_scene, m_display_w, m_display_h);
}

void displayOnScreen(){
    m_renderer->displaySceneOnTheScreen(m_display_w, m_display_h);
}

void update(){
    m_inputManager->update();
    m_scene->update();
    m_renderer->update();  
}


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}


int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    m_window = glfwCreateWindow(1280, 720, "Voxel-Engine", NULL, NULL);
    if (m_window == NULL)
        return 1;
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);



    m_renderer = new MainRenderer();
    m_renderer->initializeGL();

    m_scene = new Scene();

    m_ui = new UI();
    m_inputManager = new InputManager();

    m_ui->set(m_scene);
    m_ui->set(m_renderer);
    m_ui->set(m_window);
    
    m_inputManager->setUI(m_ui);
    m_inputManager->setScene(m_scene);
    m_inputManager->setRenderer(m_renderer);


    glfwGetFramebufferSize(m_window, &m_display_w, &m_display_h);

    rendering();
    m_renderer->swapFBO();

    // Our state


    // Main loop
    while (!glfwWindowShouldClose(m_window)){

        glfwPollEvents();
        glfwGetFramebufferSize(m_window, &m_display_w, &m_display_h);

        std::thread updateThread(&update);
        updateThread.join();

        std::thread renderingThread(&rendering);


        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        ///////////////
        // CREATE UI //
        ///////////////

    
        m_ui->drawUI();      

        //ImGui::ShowDemoWindow();

        // ceci est un test travis

        // Rendering
        ImGui::Render();
        glViewport(0, 0, m_display_w, m_display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // draw UI
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        displayOnScreen();
        renderingThread.join();

        m_renderer->swapFBO();
        glfwSwapBuffers(m_window);

    }

    delete(m_scene);
    delete(m_renderer);
    delete(m_ui);
    delete(m_inputManager);

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();

    return 0;
}


