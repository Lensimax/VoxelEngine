
#include "imgui/imgui.h"
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

#include "models/sphere.h"
#include "models/meshObject.h"


#include <iostream>

MainRenderer::MainRenderer(){

}



void MainRenderer::paintGL(Scene *scene, int width, int height){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    initializeGL();
    glViewport(0,0,width,height);

    if(height == 0){
        fprintf(stderr, "Error height = 0\n");
        exit(1);
    }


    /* CAMERA */

    Camera *c = scene->getCamera();
    if(c == NULL){
        return;
    }

    Light *l = scene->getLight();
    glm::vec3 light;
    if(l == NULL){
        light = glm::vec3(0.0,0.0,0.0);
    } else {
        light = l->getLight();
    }


    for(unsigned int i=0; i<scene->objectsEngine.size(); i++){
        if(DrawableObject* o = dynamic_cast<DrawableObject*>(scene->objectsEngine[i])) {
        // old was safely casted to NewType
            o->draw(c->getView(), c->getProj(), light);
        }
    }



    //printf("Finished\n");
}

MainRenderer::~MainRenderer(){

}



void MainRenderer::initializeGL(){

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    /* to print GLSL version */
    //std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";


}
