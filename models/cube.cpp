#include "cube.h"

#include <iostream>

Cube::Cube(){


    vertices = createVertices();
    faces = createTriangles();

    //createShader();

    // debugVertices();


}

Cube::~Cube(){
    //deleteShader();
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


void Cube::setUniform(glm::mat4 viewMat, glm::mat4 projectionMat){


}

void Cube::createShader(){
    shader = new Shader();
    shader->load("shaders/example.vert","shaders/example.frag");
}

void Cube::deleteShader(){
    delete shader; shader = NULL;
}

GLuint Cube::shaderID(){
    return shader->id();
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
