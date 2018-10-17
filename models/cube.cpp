#include "cube.h"

#include <iostream>

Cube::Cube(){


    vertices = createVertices();
    faces = createTriangles();

    createVAO();
    createShader();


}

Cube::~Cube(){
    deleteVAO();
    deleteShader();
}

std::vector<float> Cube::createVertices(){
    std::vector<float> vert = std::vector<float>();

    // 0
    vert.push_back(-1.0f);
    vert.push_back(-1.0f);
    vert.push_back(1.0f);
    // 1
    vert.push_back(-1.0f);
    vert.push_back(1.0f);
    vert.push_back(1.0f);
    // 2
    vert.push_back(1.0f);
    vert.push_back(1.0f);
    vert.push_back(1.0f);
    // 3
    vert.push_back(1.0f);
    vert.push_back(-1.0f);
    vert.push_back(1.0f);
    // 4
    vert.push_back(-1.0f);
    vert.push_back(-1.0f);
    vert.push_back(-1.0f);
    // 5
    vert.push_back(-1.0f);
    vert.push_back(1.0f);
    vert.push_back(-1.0f);
    // 6
    vert.push_back(1.0f);
    vert.push_back(1.0f);
    vert.push_back(-1.0f);
    // 7
    vert.push_back(1.0f);
    vert.push_back(-1.0f);
    vert.push_back(-1.0f);

    return vert;
}

std::vector<int> Cube::createTriangles(){
    std::vector<int> trian = std::vector<int>();

    // front face
    trian.push_back(0); trian.push_back(1); trian.push_back(2);
    trian.push_back(0); trian.push_back(2); trian.push_back(3);
    // back face
    trian.push_back(7); trian.push_back(6); trian.push_back(5);
    trian.push_back(7); trian.push_back(5); trian.push_back(4);
    // upper face
    trian.push_back(1); trian.push_back(5); trian.push_back(6);
    trian.push_back(1); trian.push_back(6); trian.push_back(2);
    // bottom face
    trian.push_back(4); trian.push_back(0); trian.push_back(3);
    trian.push_back(4); trian.push_back(3); trian.push_back(7);
    // left face
    trian.push_back(4); trian.push_back(5); trian.push_back(1);
    trian.push_back(4); trian.push_back(1); trian.push_back(0);
    // right face
    trian.push_back(3); trian.push_back(2); trian.push_back(6);
    trian.push_back(3); trian.push_back(6); trian.push_back(7);


    return trian;
}


int *Cube::getTriangles(){
    return &faces[0];
}

float *Cube::getVertices(){
    return &vertices[0];
}

int Cube::nbVertices(){
    return vertices.size()/3;
}

int Cube::nbFaces(){
    return faces.size()/3;
}

glm::mat4 Cube::getTransform(){
    return glm::mat4(1.0f);
}

void Cube::draw(glm::mat4 viewMat, glm::mat4 projectionMat){

    glUseProgram(shader->id());

    setUniform(viewMat, projectionMat);

    glBindVertexArray(vertexArrayID);
    glDrawElements(GL_TRIANGLES,3*nbFaces(),GL_UNSIGNED_INT,(void *)0);
    glBindVertexArray(0);

    glUseProgram(0);
}

void Cube::createVAO(){

    buffers = new GLuint[2];

    glGenBuffers(2, buffers);
    glGenVertexArrays(1,&vertexArrayID);

    // create the VBO associated with the grid (the terrain)
    glBindVertexArray(vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]); // vertices
    glBufferData(GL_ARRAY_BUFFER,nbVertices()*3*sizeof(float),getVertices(),GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[1]); // indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,nbFaces()*3*sizeof(int),getTriangles(),GL_STATIC_DRAW);
}

void Cube::deleteVAO(){
    glDeleteBuffers(2,buffers);
    glDeleteVertexArrays(1,&vertexArrayID);
}

void Cube::setUniform(glm::mat4 viewMat, glm::mat4 projectionMat){

    glm::mat4 modelMat = glm::mat4(1.0f);

    // send the transformation matrix
    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"projMat"),1,GL_FALSE,&(projectionMat[0][0]));
}

void Cube::createShader(){
    shader = new Shader();
    shader->load("shaders/example.vert","shaders/example.frag");
}

void Cube::deleteShader(){
    delete shader; shader = NULL;
}

void Cube::debugFaces(){
    std::cout << "Faces:\n";
    for(int i=0; i<faces.size(); i+=3){
        std::cout << "(" << faces[i] << ", " << faces[i+1] << ", " << faces[i+2] << ")\n";
    }
}

void Cube::debugVertices(){
    std::cout << "Vertices:\n";
    for(int i=0; i<vertices.size(); i+=3){
        std::cout << "(" << vertices[i] << ", " << vertices[i+1] << ", " << vertices[i+2] << ")\n";
    }
}
