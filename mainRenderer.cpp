
#include "imgui.h"
#include "impl/imgui_impl_glfw.h"
#include "impl/imgui_impl_opengl3.h"


#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif


#include "mainRenderer.h"


#include <iostream>

MainRenderer::MainRenderer(){

}

void MainRenderer::makeScene(){
    //objectsToDraw = std::vector<DrawableObject*>();

    object = new Cube(glm::vec3(0.0,0.0,0.0), glm::vec3(0.5,0.5,0.5));

    // glm::vec3(0.0, 45.0, 0.0)
    // objectsToDraw.push_back(c);
    //objectsToDraw.push_back(new Cube(glm::vec3(-0.2,0.0,0.0)));
}


void MainRenderer::paintGL(int width, int height){
    /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,width,height);*/

    if(height == 0){
        fprintf(stderr, "Error height = 0\n");
        exit(1);
    }

    // camera position, rotation
    glm::vec3 position = glm::vec3(0.0,0.0,5.0);
    glm::vec3 directionOfView = glm::vec3(0.0,0.0,0.0);
    glm::vec3 up = glm::vec3(0.0,1.0,0.0);
    viewMat = glm::lookAt(position, directionOfView, up);


    // projection matrix
    float fovy = 45.0f;
    float aspect = (float)width/(float)height;
    float near = 0.1;
    float far = 10.0f;
    projectionMat = glm::perspective(fovy, aspect, near, far);

    /*for(unsigned int i=0; i<objectsToDraw.size(); i++){
        objectsToDraw[i]->draw(viewMat, projectionMat);
    }*/

    object->draw(viewMat, projectionMat);

    printf("Finished\n");
}



void MainRenderer::initializeGL(){


    /* to print GLSL version */
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_MULTISAMPLE);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


    makeScene();


}


MainRenderer::~MainRenderer(){
    deleteScene();
}


void MainRenderer::deleteScene(){

}
