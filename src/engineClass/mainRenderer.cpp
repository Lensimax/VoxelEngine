
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <drawDebug.h>

#ifndef M_PI
#define M_PI 3.1415926
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

#include <glmCout.h>

#include "../tools/lights/directionnalLight.h"

#include "mainRenderer.h"

#include "../components/cameraControllerFirstPerson.h"

#include "../components/meshRenderer.h"

// #include "models/sphere.h"
// #include "models/meshObject.h"


#include <iostream> 

MainRenderer::MainRenderer() : m_wireActivated(false), m_cullface(true), m_widthScreen(0), m_heightScreen(0), m_gridActivated(true), m_firstFramePassed(false), m_playMode(true) {

    m_postProcessShader = new Shader();
    m_postProcessShader->load("../data/shaders/postProcess.vert","../data/shaders/postProcess.frag");

    createVAOQuad();
    createFBOSceneRender();

    m_camera = new GameObject(-1, "Camera Editor", new Transform(glm::vec3(0,164, 0), glm::vec3(M_PI / 2, M_PI, 0)));
    m_camera->addComponent<CameraProjective*>(new CameraProjective());
    m_camera->addComponent<CameraControllerFirstPerson*>(new CameraControllerFirstPerson());
    m_camProj = m_camera->getComponent<CameraProjective*>();

}


MainRenderer::~MainRenderer(){
    delete m_postProcessShader;
    deleteVAOQuad();
    deleteFBOSceneRender();
}



//// Fait le rendu de la scene dans la version du jeu

void MainRenderer::renderTheScene(Scene *scene, int width, int height){

    if(height <= 0){
        return;
    }

    m_widthScreen = width;
    m_heightScreen = height;

    Transform *rootTransform = new Transform();

    // CAMERA
    CameraProjective * camera = scene->getCamera();
    if(camera == NULL){
        return;
    }


    Light *l = scene->getLight();
    if(l == NULL){
        l = new DirectionnalLight(scene->addNewId());
    }

    if(m_gridActivated){
        drawEditorGrid(rootTransform->getModelToChild(glm::mat4(1)), camera->getView(), camera->getProjection((float)width/(float)height));
    }

    for(unsigned int i=0; i<scene->objectsEngine.size(); i++){
        drawRecursive(rootTransform->getModelToChild(glm::mat4(1)), scene->objectsEngine[i], camera->getView(), camera->getProjection((float)width/(float)height), l, (float)width/(float)height);
    }


    delete rootTransform; 

}

void MainRenderer::renderTheSceneEditor(Scene *scene, int width, int height){

    assert(height > 0);

    Transform *rootTransform = new Transform();
    
    m_widthScreen = width;
    m_heightScreen = height;

    Light *l = scene->getLight();
    if(l == NULL){
        l = new DirectionnalLight(scene->addNewId());
    }

    if(m_gridActivated){
        drawEditorGrid(rootTransform->getModelToChild(glm::mat4(1)), m_camProj->getView(), m_camProj->getProjection((float)width/(float)height));
    }
    
    if(m_wireActivated){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }

    for(unsigned int i=0; i<scene->objectsEngine.size(); i++){
        drawRecursive(rootTransform->getModelToChild(glm::mat4(1)), scene->objectsEngine[i], m_camProj->getView(), m_camProj->getProjection((float)width/(float)height), l, (float)width/(float)height);
    }
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}


void MainRenderer::drawRecursive(glm::mat4 modelMat, GameObject *obj, glm::mat4 viewMat, glm::mat4 projectionMat, Light *l, float screenAspectRatio){

    glm::mat4 matrixTochild = obj->getTransform()->getModelToChild(modelMat);
    glm::mat4 modelMatrix = obj->getTransform()->getModelMat(modelMat);

    std::vector<Renderer*> renderers = obj->getComponents<Renderer*>();
    for(auto *renderer : renderers){
        renderer->draw(modelMatrix, viewMat, projectionMat, l);
    }

    for(unsigned int i=0; i<obj->m_listOfChildren.size(); i++){
        drawRecursive(matrixTochild, obj->m_listOfChildren[i], viewMat, projectionMat, l, screenAspectRatio);
    }
}



void MainRenderer::paintGL(Scene *scene, int width, int height){

    ///// RENDERING SCENE FOR THE GAME

    initFBOSceneRender(width, height);

    glBindFramebuffer(GL_FRAMEBUFFER, m_fboRenderScene);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    initializeGL();
    glViewport(0,0,width,height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // render in texture
    renderTheScene(scene, width, height);

    ///// RENDERING DISPLAY FOR EDITOR
    if(!m_playMode){
        glDrawBuffer(GL_COLOR_ATTACHMENT1);

        initializeGL();
        glViewport(0,0,width,height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderTheSceneEditor(scene, width, height);
    }
    

    // disable FBO
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glUseProgram(0);

    m_firstFramePassed = true;


}

void MainRenderer::displaySceneOnTheScreen(int width, int height){
    glViewport(0,0,width,height);

    glUseProgram(m_postProcessShader->id());

    // send rendered scene to the post process shader
    glActiveTexture(GL_TEXTURE0);
    if(m_playMode){
        glBindTexture(GL_TEXTURE_2D,getGameTextureID()); 
    } else {
        glBindTexture(GL_TEXTURE_2D,getEditorTextureID()); 
    }
    glUniform1i(glGetUniformLocation(m_postProcessShader->id(), "sceneRendered"), 0);

    glDisable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawQuad();

    glUseProgram(0);
}



void MainRenderer::drawEditorGrid(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat){
    Shader shader = Shader();
    shader.load("../data/shaders/simple.vert","../data/shaders/simple.frag");

    glm::vec4 color = glm::vec4(0.217f, 0.217f, 0.217f, 1.0f);

    glUseProgram(shader.id());

    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"projMat"),1,GL_FALSE,&(projectionMat[0][0]));

    glUniform4fv(glGetUniformLocation(shader.id(),"color"),1,&color[0]);

    glLineWidth(1);
    
    const int size = 64;
    const float step = 1;

    std::vector<glm::vec3> arrayVertices;
    arrayVertices.resize(size*size);

    for(int i=-(size/2); i<size/2; i++){
        for(int j=-(size/2); j<size/2; j++){
            if(i != (size/2)-1){
                arrayVertices.push_back(glm::vec3(i*step, 0, j*step));
                arrayVertices.push_back(glm::vec3((i+1)*step, 0, j*step));
            }

            if(j != (size/2)-1){
                arrayVertices.push_back(glm::vec3(i*step, 0, j*step));
                arrayVertices.push_back(glm::vec3((i)*step, 0, (j+1)*step));
            }
        }

    }
    DrawDebug::drawArrayPosition(arrayVertices.size(), (float*)&(arrayVertices[0]), GL_LINES);

    glUseProgram(0);
}


void MainRenderer::update(){
    if(!m_playMode){
        m_camera->update();
    }
}


void MainRenderer::createUI(){
    ImGui::Begin("MainRenderer Setting");

    m_camera->createUI("MainRenderer Setting");

    ImGui::End();


    if(m_firstFramePassed && !m_playMode){
        ImGui::Begin("Game View", nullptr, ImGuiWindowFlags_NoResize);
        ImGui::Image((void*)(intptr_t)getGameTextureID(), ImVec2(426,240), ImVec2(0,1), ImVec2(1,0));
        ImGui::End();        
    }
}



void MainRenderer::initializeGL(){

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glDepthMask(GL_TRUE);
    //glDepthFunc(GL_LESS);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonOffset(-1,-1);

    // Cull triangles which normal is not towards the camera
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    if(m_cullface){
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }

    /* to print GLSL version */
    //std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";


}


void MainRenderer::createVAOQuad(){
    const GLfloat quadData[] = {-1.0f,-1.0f,0.0f, 1.0f,-1.0f,0.0f, -1.0f,1.0f,0.0f, -1.0f,1.0f,0.0f, 1.0f,-1.0f,0.0f, 1.0f,1.0f,0.0f };

    glGenBuffers(1,&m_quad);
    glGenVertexArrays(1,&m_vaoQuad);

    glBindVertexArray(m_vaoQuad);
    glBindBuffer(GL_ARRAY_BUFFER,m_quad); // vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadData),quadData,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);
    glEnableVertexAttribArray(0);
}

void MainRenderer::deleteVAOQuad(){
    glDeleteBuffers(1,&m_quad);
    glDeleteVertexArrays(1,&m_vaoQuad);
}


void MainRenderer::drawQuad(){
    glBindVertexArray(m_vaoQuad);
    glDrawArrays(GL_TRIANGLES,0,6);
    glBindVertexArray(0);
}


void MainRenderer::createFBOSceneRender(){
    glGenFramebuffers(1, &m_fboRenderScene);
    glGenTextures(1,&m_renderedSceneTextureID);
    glGenTextures(1,&m_editorTextureID);
    glGenTextures(1,&m_renderedDepth);

}

void MainRenderer::initFBOSceneRender(int width, int height){
    glBindFramebuffer(GL_FRAMEBUFFER,m_fboRenderScene);

    /* la taille est égale au nombre de cases de la grille */
    // TEXTURE FOR GAME
    glBindTexture(GL_TEXTURE_2D,m_renderedSceneTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA32F,width,height,0,GL_RGBA,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,m_renderedSceneTextureID,0);

    // TEXTURE FOR EDITOR
    glBindTexture(GL_TEXTURE_2D,m_editorTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA32F,width,height,0,GL_RGBA,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT1,GL_TEXTURE_2D,m_editorTextureID,0);


    glBindTexture(GL_TEXTURE_2D, m_renderedDepth);
    glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT24,width,height,0,GL_DEPTH_COMPONENT,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,m_renderedDepth,0);



    /* on desactive le buffer */
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void MainRenderer::deleteFBOSceneRender(){
    glDeleteFramebuffers(1,&m_fboRenderScene);
    glDeleteTextures(1, &m_renderedSceneTextureID);
    glDeleteTextures(1,&m_renderedDepth);
    glDeleteTextures(1,&m_editorTextureID);
}



