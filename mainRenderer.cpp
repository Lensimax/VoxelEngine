#include "mainRenderer.h"

#include <iostream>

MainRenderer::MainRenderer(const QGLFormat &format) : QGLWidget(format), _timer(new QTimer(this)){
    setlocale(LC_ALL,"C");

    objectsToDraw = std::vector<DrawableObject*>();

    arrayOfBuffers = std::vector<GLuint*>();
    arrayOfVertexArrayID = std::vector<GLuint>();

    Cube *c = new Cube();
    addObjectToScene(c);


    _timer->setInterval(10);
    connect(_timer,SIGNAL(timeout()),this,SLOT(updateGL()));
}


void MainRenderer::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,width(),height());

    // placement of the object
    // we place the object in the center of the scene
    modelMat = glm::mat4(1.0f);
    modelMat = glm::scale(modelMat,glm::vec3(0.5,0.5,0.5));

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

    /*for(int i=0; i<objectsToDraw.size(); i++){
        drawAnObject(objectsToDraw[i], i);
    }*/
}





void MainRenderer::initializeGL(){
    makeCurrent();

    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK) {
        exit(1);
    }

    std::cout << "Glew init result:" << glewInit() << "\n";

    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glViewport(0,0,width(),height());

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

void MainRenderer::addObjectToScene(DrawableObject* object){
    objectsToDraw.push_back(object);
    //createVAOObject(object);

}


void MainRenderer::createVAOObject(DrawableObject* object){
    GLuint buffers[2];
    GLuint vertexArrayID;

    glGenBuffers(2, buffers);
    glGenVertexArrays(1,&vertexArrayID);

    arrayOfBuffers.push_back(buffers);
    arrayOfVertexArrayID.push_back(vertexArrayID);

    glBindVertexArray(vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]); // vertices
    glBufferData(GL_ARRAY_BUFFER,object->nbVertices()*3*sizeof(float),object->getVertices(),GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[1]); // indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,object->nbFaces()*3*sizeof(int),object->getTriangles(),GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void MainRenderer::deleteScene(){
    for(int i=0; objectsToDraw.size(); i++){
        //delete objectsToDraw[i];
        glDeleteBuffers(2,arrayOfBuffers[i]);
        glDeleteVertexArrays(1,&arrayOfVertexArrayID[i]);
    }
}

void MainRenderer::drawAnObject(DrawableObject* object, int i){
    GLuint shaderID = exampleShader->id();

    glUseProgram(shaderID);

    glm::mat4 model = glm::mat4(1.0f);

    // send the transformation matrix
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"modelMat"),1,GL_FALSE,&(model[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"projMat"),1,GL_FALSE,&(projectionMat[0][0]));

    glBindVertexArray(arrayOfVertexArrayID[i]);
    glDrawElements(GL_TRIANGLES,3*object->nbFaces(),GL_UNSIGNED_INT,(void *)0);
    glBindVertexArray(0);

    glUseProgram(0);
}

void MainRenderer::createShaders(){
    exampleShader = new Shader();
    exampleShader->load("shaders/example.vert","shaders/example.frag");
}

void MainRenderer::deleteShaders() {
    delete exampleShader; exampleShader = NULL;
}
