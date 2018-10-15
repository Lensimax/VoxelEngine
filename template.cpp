#include "template.h"


Template::Template(const QGLFormat &format) : QGLWidget(format), _timer(new QTimer(this)){
    setlocale(LC_ALL,"C");

    _timer->setInterval(10);
    connect(_timer,SIGNAL(timeout()),this,SLOT(updateGL()));
}

void Template::createShaders(){
    exampleShader = new Shader();
    exampleShader->load("shaders/example.vert","shaders/example.frag");
}

void Template::deleteShaders() {
    delete exampleShader; exampleShader = NULL;
}

void Template::createQuadVAO(){
    const GLfloat quadData[] = {-1.0f,-1.0f,0.0f, 1.0f,-1.0f,0.0f, -1.0f,1.0f,0.0f, -1.0f,1.0f,0.0f, 1.0f,-1.0f,0.0f, 1.0f,1.0f,0.0f };


    glGenBuffers(1,&_quad);
    glGenVertexArrays(1,&_vaoQuad);

    glBindVertexArray(_vaoQuad);
    glBindBuffer(GL_ARRAY_BUFFER,_quad); // vertices
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadData),quadData,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);
    glEnableVertexAttribArray(0);
}
void Template::deleteQuadVAO(){
    glDeleteBuffers(1,&_quad);
    glDeleteVertexArrays(1,&_vaoQuad);
}

void Template::drawQuad(){
    glBindVertexArray(_vaoQuad);
    glDrawArrays(GL_TRIANGLES,0,6);
    glBindVertexArray(0);
}

void Template::paintGL(){
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

    glUseProgram(exampleShader->id());

    // send the transformation matrix
    glUniformMatrix4fv(glGetUniformLocation(exampleShader->id(),"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(exampleShader->id(),"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(exampleShader->id(),"projMat"),1,GL_FALSE,&(projectionMat[0][0]));


    // draw a red triangle
    drawQuad();


    glUseProgram(0);
}





void Template::initializeGL(){
    makeCurrent();

    glewExperimental = GL_TRUE;

    if(glewInit()!=GLEW_OK) {
        exit(1);
    }

    glClearColor(0.0,0.0,0.0,1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glViewport(0,0,width(),height());

    createQuadVAO();
    createShaders();

    _timer->start();
}


void Template::resizeGL(int width,int height){
    glViewport(0,0,width,height);
    updateGL();
}
void Template::keyPressEvent(QKeyEvent *ke){
    if(ke->key()==Qt::Key_R) {
        exampleShader->reload("shaders/example.vert","shaders/example.frag");
    }
}

void Template::mousePressEvent(QMouseEvent *me){

}
void Template::mouseMoveEvent(QMouseEvent *me){

}

Template::~Template(){
    deleteQuadVAO();
    deleteShaders();
}
