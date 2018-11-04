
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
    objectsEngine = std::vector<EngineObject*>();

    Cube *c = new Cube("Cube 1", glm::vec3(0.0,0.0,0.0), glm::vec3(0.5,0.5,0.5), glm::vec3(45.0,45.0,0.0));

    objectsEngine.push_back(c);
    objectsEngine.push_back(new Cube("Cube 2", glm::vec3(-0.5,0.0,0.0)));

    Camera *cam = new CameraProj();

    objectsEngine.push_back(cam);

}


void MainRenderer::paintGL(int width, int height){
    /*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
    glViewport(0,0,width,height);

    if(height == 0){
        fprintf(stderr, "Error height = 0\n");
        exit(1);
    }


    /* CAMERA */

    Camera *c = getCamera();

    if(c == NULL){
        return;
    }

    for(unsigned int i=0; i<objectsEngine.size(); i++){
        if(DrawableObject* o = dynamic_cast<DrawableObject*>(objectsEngine[i])) {
        // old was safely casted to NewType
            o->draw(c->getView(), c->getProj());
        }
    }



    //printf("Finished\n");
}




void MainRenderer::initializeGL(){

    /*glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);*/
    /* to print GLSL version */
    //std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";


    makeScene();


}

Camera *MainRenderer::getCamera(){
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        if(Camera* c = dynamic_cast<Camera*>(objectsEngine[i])) {
        // old was safely casted to NewType
            return c;
        }
    }
    return NULL;
}


MainRenderer::~MainRenderer(){
    deleteScene();
}

void MainRenderer::createUI(char *ID){
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        objectsEngine[i]->createUI(ID);
    }
}


void MainRenderer::deleteScene(){
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        delete objectsEngine[i];
    }
}


void MainRenderer::createUIAtID(int indexItem, char *ID){
    if(indexItem >= 0 && indexItem < (int)objectsEngine.size()){
        objectsEngine[indexItem]->createUI(ID);
    }
}

std::vector<std::string> MainRenderer::getNameOfAllObjects(){
    std::vector<std::string> list = std::vector<std::string>();

    for(unsigned int i=0; i<objectsEngine.size(); i++){
        list.push_back(objectsEngine[i]->getName());
    }

    return list;
}
