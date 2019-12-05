
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


#include "../tools/lights/directionnalLight.h"

#include "mainRenderer.h"

// #include "models/sphere.h"
// #include "models/meshObject.h"


#include <iostream> 

MainRenderer::MainRenderer(){

    m_transformEditor = new Transform();

    postProcessShader = new Shader();
    postProcessShader->load("../data/shaders/postProcess.vert","../data/shaders/postProcess.frag");

    createVAOQuad();
    createFBOSceneRender();
    m_wireActivated = false;
    cullface = true;

    widthScreen = 0;
    heightScreen = 0;

    m_camera = new CameraProj(-1, "Camera Editor");

}


//// Fait le rendu de la scene dans la version du jeu

void MainRenderer::renderTheScene(Scene *scene, int width, int height){

    assert(height > 0);

    renderTheScene(scene, width, height);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    
    widthScreen = width;
    heightScreen = height;

    Transform *rootTransform = new Transform();

    // CAMERA
    Camera *c = scene->getCamera();
    if(c == NULL){
        return;
    }

    Light *l = scene->getLight();
    if(l == NULL){
        l = new DirectionnalLight(scene->addNewId());
    }


    for(unsigned int i=0; i<scene->objectsEngine.size(); i++){
        drawRecursive(rootTransform->getModelToChild(glm::mat4(1)), scene->objectsEngine[i], c, l, (float)width/(float)height);
    }


    delete rootTransform; 

}

void MainRenderer::renderTheSceneEditor(Scene *scene, int width, int height){

    assert(height > 0);
    
    widthScreen = width;
    heightScreen = height;


    // CAMERA
    Camera *c = scene->getCamera();
    if(c == NULL){
        return;
    }

    Light *l = scene->getLight();
    if(l == NULL){
        l = new DirectionnalLight(scene->addNewId());
    }

    if(m_wireActivated){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }

    for(unsigned int i=0; i<scene->objectsEngine.size(); i++){
        drawRecursive(m_transformEditor->getModelToChild(glm::mat4(1)), scene->objectsEngine[i], c, l, (float)width/(float)height);
    }
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


}


void MainRenderer::drawRecursive(glm::mat4 modelMat, EngineObject *obj, Camera *c, Light *l, float screenAspectRatio){

    glm::mat4 matrixTochild = obj->getTransform()->getModelToChild(modelMat);
    glm::mat4 modelMatrix = obj->getTransform()->getModelMat(modelMat);

    if(DrawableObject* o = dynamic_cast<DrawableObject*>(obj)) { // safe cast
        o->draw(modelMatrix, c->getView(), c->getProj(screenAspectRatio), l);
    }

    for(unsigned int i=0; i<obj->listOfChildren.size(); i++){
        drawRecursive(matrixTochild, obj->listOfChildren[i], c, l, screenAspectRatio);
    }
}



void MainRenderer::paintGL(Scene *scene, int width, int height){




    initFBOSceneRender(width, height);

    glBindFramebuffer(GL_FRAMEBUFFER, fboRenderScene);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    initializeGL();
    glViewport(0,0,width,height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render in texture
    // renderTheScene(scene, width, height);
    renderTheSceneEditor(scene, width, height);

    // disable FBO
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glUseProgram(0);


}

void MainRenderer::displaySceneOnTheScreen(int width, int height){
    glViewport(0,0,width,height);

    glUseProgram(postProcessShader->id());

    // send rendered scene to the post process shader
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,renderedSceneTextureID);
    glUniform1i(glGetUniformLocation(postProcessShader->id(), "sceneRendered"), 0);

    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawQuad();

    glUseProgram(0);
}

MainRenderer::~MainRenderer(){
    delete postProcessShader;
    deleteVAOQuad();
    deleteFBOSceneRender();
    delete m_transformEditor;
}


void MainRenderer::update(){
    m_transformEditor->update();
}


void MainRenderer::createUI(){
    ImGui::Begin("Renderer Setting");

    m_transformEditor->createUI();

    ImGui::Separator();

    m_camera->createUI("Renderer Setting");


    ImGui::End();
}



void MainRenderer::initializeGL(){

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-1,-1);

    // Cull triangles which normal is not towards the camera
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    if(cullface){
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }

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


void MainRenderer::createFBOSceneRender(){
    glGenFramebuffers(1, &fboRenderScene);
    glGenTextures(1,&renderedSceneTextureID);
    glGenTextures(1,&renderedDepth);

}

void MainRenderer::initFBOSceneRender(int width, int height){

    /* la taille est égale au nombre de cases de la grille */
    glBindTexture(GL_TEXTURE_2D,renderedSceneTextureID);


    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA32F,width,height,0,GL_RGBA,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, renderedDepth);
    glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT24,width,height,0,GL_DEPTH_COMPONENT,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER,fboRenderScene);

    glBindTexture(GL_TEXTURE_2D,renderedSceneTextureID);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,renderedSceneTextureID,0);

    glBindTexture(GL_TEXTURE_2D,renderedDepth);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,renderedDepth,0);

    /* on desactive le buffer */
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void MainRenderer::deleteFBOSceneRender(){
    glDeleteFramebuffers(1,&fboRenderScene);
    glDeleteTextures(1, &renderedSceneTextureID);
    glDeleteTextures(1,&renderedDepth);
}

GLuint MainRenderer::getTextureID(){
    return renderedSceneTextureID;
}
