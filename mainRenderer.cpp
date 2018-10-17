#include "mainRenderer.h"

#include <iostream>

MainRenderer::MainRenderer(const QGLFormat &format) : QGLWidget(format), _timer(new QTimer(this)){
    setlocale(LC_ALL,"C");

    _timer->setInterval(10);
    connect(_timer,SIGNAL(timeout()),this,SLOT(updateGL()));
}

void MainRenderer::makeScene(){
    objectsToDraw = std::vector<DrawableObject*>();

    objectsToDraw.push_back(new Cube());
}


void MainRenderer::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,width(),height());


    // camera position, rotation
    glm::vec3 position = glm::vec3(0.0,0.0,5.0);
    glm::vec3 directionOfView = glm::vec3(0.0,0.0,0.0);
    glm::vec3 up = glm::vec3(0.0,1.0,0.0);
    viewMat = glm::lookAt(position, directionOfView, up);

    // projection matrix
    float fovy = 45.0f;
    float aspect = width()/height();
    float near = 0.1;
    float far = 10.0f;
    projectionMat = glm::perspective(fovy, aspect, near, far);

    for(unsigned int i=0; i<objectsToDraw.size(); i++){
        objectsToDraw[i]->draw(viewMat, projectionMat);
    }

}



void MainRenderer::initializeGL(){
    makeCurrent();

    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK) {
        exit(1);
    }


    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glViewport(0,0,width(),height());


    makeScene();


    _timer->start();
}


void MainRenderer::resizeGL(int width,int height){
    glViewport(0,0,width,height);
    updateGL();
}
void MainRenderer::keyPressEvent(QKeyEvent *ke){
    if(ke->key()==Qt::Key_R) {
        //exampleShader->reload("shaders/example.vert","shaders/example.frag");
    }
}

void MainRenderer::mousePressEvent(QMouseEvent *me){

}
void MainRenderer::mouseMoveEvent(QMouseEvent *me){

}

MainRenderer::~MainRenderer(){
    deleteScene();
}


void MainRenderer::deleteScene(){

}
