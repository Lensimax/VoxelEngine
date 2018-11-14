
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


#include "cube.h"

#include <iostream>

#include "../material/lambertian.h"


Cube::Cube(std::string n, vec3 position, vec3 scale, vec3 rotation){
    transform = new Transform(position, scale, rotation);

    createVertices();
    triangles = createTriangles();

    createVAO();

    material = new Lambertian();

    name = n;
}


Cube::~Cube(){
    deleteVAO();
    delete transform;
    delete material;
}

void Cube::addVertex(glm::vec3 v){
    vertices.push_back(v[0]);
    vertices.push_back(v[1]);
    vertices.push_back(v[2]);
}

/*
*   update std::vector<float> vertices;
*/
void Cube::createVertices(){
    vertices = std::vector<float>();

    // 0
    addVertex(glm::vec3(-1.0, -1.0, 1.0));
    // 1
    addVertex(glm::vec3(-1.0, 1.0, 1.0));
    // 2
    addVertex(glm::vec3(1.0, 1.0, 1.0));
    // 3
    addVertex(glm::vec3(1.0, -1.0, 1.0));
    // 4
    addVertex(glm::vec3(-1.0, -1.0, -1.0));
    // 5
    addVertex(glm::vec3(-1.0, 1.0, -1.0));
    // 6
    addVertex(glm::vec3(1.0, 1.0, -1.0));
    // 7
    addVertex(glm::vec3(1.0, -1.0, -1.0));

}

void Cube::createUI(char *ID){
    ImGui::BeginChild(ID);
    ImGui::Text(name.c_str());
    ImGui::Separator();

    transform->createUI();
    ImGui::Separator();
    material->createUI();
    ImGui::Separator();

    ImGui::EndChild();
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
    return &triangles[0];
}

float *Cube::getVertices(){
    return &vertices[0];
}

int Cube::nbVertices(){
    return vertices.size()/3;
}

int Cube::nbTriangles(){
    return triangles.size()/3;
}



void Cube::draw(glm::mat4 viewMat, glm::mat4 projectionMat, glm::vec3 light){

    glUseProgram(material->shaderID());

    setUniform(viewMat, projectionMat, light);

    glBindVertexArray(vertexArrayID);
    glDrawElements(GL_TRIANGLES,3*nbTriangles(),GL_UNSIGNED_INT,(void *)0);
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,nbTriangles()*3*sizeof(int),getTriangles(),GL_STATIC_DRAW);
}

void Cube::deleteVAO(){
    glDeleteBuffers(2,buffers);
    glDeleteVertexArrays(1,&vertexArrayID);
}

void Cube::setUniform(glm::mat4 viewMat, glm::mat4 projectionMat, glm::vec3 light){

    glm::mat4 modelMat = transform->getMat4();


    // send the transformation matrix
    material->callUniform(modelMat, viewMat, projectionMat, light);

}
