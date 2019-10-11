#include "plane.h"

#define POSITION_ATTRIB 0
#define VERTEX_NORMAL_ATTRIB 1

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


#include <iostream>



Plane::Plane(std::string n, unsigned int size, float width, float gridZ, Transform *t, Material *m){
    transform = t;

    mesh = new MeshGrid(size, width, gridZ);


    glm::vec3 center = mesh->getCenter();
    t->setCenter(center);

    std::cout << __LINE__ << " Fin creation mesh" << std::endl;

    createVAO();

    std::cout << __LINE__ << " after create VAO" << std::endl;

    material = m;

    name = n;

}


Plane::~Plane(){
    deleteVAO();
    delete transform;
    delete material;
    delete mesh;
}



void Plane::draw(glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){

    glUseProgram(material->shaderID());

    setUniform(viewMat, projectionMat, light);

    glBindVertexArray(vertexArrayID);
    glDrawElements(GL_TRIANGLES,3*mesh->getNBFaces(),GL_UNSIGNED_INT,(void *)0);
    glBindVertexArray(0);

    glUseProgram(0);
}

void Plane::createVAO(){

    buffers = new GLuint[3];

    glGenBuffers(3, buffers);
    glGenVertexArrays(1,&vertexArrayID);

    // create the VBO associated with the grid (the terrain)
    glBindVertexArray(vertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]); // vertices
    glBufferData(GL_ARRAY_BUFFER,mesh->getNBVertices()*3*sizeof(float),mesh->getVertices(),GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_ATTRIB);
    glVertexAttribPointer(POSITION_ATTRIB,3,GL_FLOAT,GL_FALSE,0,(void *)0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[1]); // indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,mesh->getNBFaces()*3*sizeof(unsigned int),mesh->getFaces(),GL_STATIC_DRAW);

    /* normals */
    glEnableVertexAttribArray(VERTEX_NORMAL_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, mesh->getNBVertices()*3* sizeof(float), mesh->getNormals(), GL_STATIC_DRAW); //normals is std::vector<float>
    glEnableVertexAttribArray(VERTEX_NORMAL_ATTRIB);
    glVertexAttribPointer(VERTEX_NORMAL_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //indices
    glBindVertexArray(0);
}

void Plane::deleteVAO(){
    glDeleteBuffers(2,buffers);
    glDeleteVertexArrays(1,&vertexArrayID);
}

void Plane::setUniform(glm::mat4 viewMat, glm::mat4 projectionMat, Light* light){

    glm::mat4 modelMat = transform->getMat4();


    // send the transformation matrix
    material->callUniform(modelMat, viewMat, projectionMat, light);

}



int Plane::nbVertices(){
    return mesh->getNBVertices();
}

int Plane::nbTriangles(){
    return mesh->getNBFaces();
}



void Plane::createUI(char *ID){
    ImGui::BeginChild(ID);
    ImGui::Text(name.c_str());
    ImGui::Separator();
    mesh->createUI();
    if (ImGui::Button("Recreate")){
        mesh->recreate();
        createVAO();
    }
    ImGui::Separator();

    transform->createUI();
    ImGui::Separator();
    material->createUI();
    ImGui::Separator();

    ImGui::EndChild();
}
