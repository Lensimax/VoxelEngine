#include "mainRenderer.h"

#include <GL/glew.h>

#include <iostream>

MainRenderer::MainRenderer(){

}

void MainRenderer::makeScene(){
    objectsToDraw = std::vector<DrawableObject*>();

    //object = new Cube(glm::vec3(0.0,0.0,0.0), glm::vec3(0.5,0.5,0.5));

    // glm::vec3(0.0, 45.0, 0.0)
    // objectsToDraw.push_back(c);
    //objectsToDraw.push_back(new Cube(glm::vec3(-0.2,0.0,0.0)));
}


void MainRenderer::paintGL(int width, int height){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,width,height);


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

    //object->draw(viewMat, projectionMat);

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
