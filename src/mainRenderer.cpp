
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>



#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include "tools/lights/directionnalLight.h"

#include "mainRenderer.h"

#include "models/sphere.h"
#include "models/meshObject.h"


#include <iostream>

MainRenderer::MainRenderer(){

    postProcessShader = new Shader();
    postProcessShader->load("data/shaders/postProcess.vert","data/shaders/postProcess.frag");

    createVAOQuad();

}

void MainRenderer::renderTheScene(Scene *scene, int width, int height){


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
    if(l == NULL){
        l = new DirectionnalLight();
    }


    for(unsigned int i=0; i<scene->objectsEngine.size(); i++){
        if(DrawableObject* o = dynamic_cast<DrawableObject*>(scene->objectsEngine[i])) {
            // old was safely casted to NewType
            o->draw(c->getView(), c->getProj(), l);
        }
    }



}



void MainRenderer::paintGL(Scene *scene, int width, int height){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    initializeGL();
    glViewport(0,0,width,height);

    // renderTheScene(scene, width, height);

    glUseProgram(postProcessShader->id());

    drawQuad();

    // printf("Finisshed\n");
}

MainRenderer::~MainRenderer(){
    delete postProcessShader;
    deleteVAOQuad();
}



void MainRenderer::initializeGL(){

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    /* to print GLSL version */
    //std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";


}


void MainRenderer::createVAOQuad(){
    const GLfloat quadData[] = {-1.0f,-1.0f,0.0f, 1.0f,-1.0f,0.0f, -1.0f,1.0f,0.0f, -1.0f,1.0f,0.0f, 1.0f,-1.0f,0.0f, 1.0f,1.0f,0.0f };

    glGenBuffers(1,&_quad);
    glGenVertexArrays(1,&_vaoQuad);

    glBindVertexArray(_vaoQuad);
    glBindBuffer(GL_ARRAY_BUFFER,_quad); // vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadData),quadData,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);
    glEnableVertexAttribArray(0);
}

void MainRenderer::deleteVAOQuad(){
    glDeleteBuffers(1,&_quad);
    glDeleteVertexArrays(1,&_vaoQuad);
}


void MainRenderer::drawQuad(){
    glBindVertexArray(_vaoQuad);
    glDrawArrays(GL_TRIANGLES,0,6);
    glBindVertexArray(0);
}
