
#include "../imgui/imgui.h"
#include "../impl/imgui_impl_glfw.h"
#include "../impl/imgui_impl_opengl3.h"


#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include "meshLoader.h"

#include "meshObject.h"
#include "meshLoader.h"
#include "sphereMesh.h"

#include <iostream>

#include "../material/lambertian.h"


MeshObject::MeshObject(std::string n, char *filename, vec3 position, vec3 scale, vec3 rotation){
    transform = new Transform(position, scale, rotation);

    // createMesh(filename);

    // mesh = new CubeMesh();
    mesh = new MeshLoader(filename);
    // mesh = new SphereMesh();

    // triangles;
    // normals;

    printf("creation done\n");

    createVAO();

    material = new Lambertian();

    name = n;

}


MeshObject::~MeshObject(){
    deleteVAO();
    delete transform;
    delete material;
    delete mesh;
}




int *MeshObject::getTriangles(){
    return &triangles[0];
}

float *MeshObject::getVertices(){
    return &vertices[0];
}

int MeshObject::nbVertices(){
    return vertices.size()/3;
}

int MeshObject::nbTriangles(){
    return triangles.size()/3;
}



void MeshObject::draw(glm::mat4 viewMat, glm::mat4 projectionMat, glm::vec3 light){

    glUseProgram(material->shaderID());

    setUniform(viewMat, projectionMat, light);

    glBindVertexArray(vertexArrayID);
    glDrawElements(GL_TRIANGLES,3*mesh->getNBFaces(),GL_UNSIGNED_INT,(void *)0);
    glBindVertexArray(0);

    glUseProgram(0);
}

void MeshObject::createVAO(){

    buffers = new GLuint[2];

    glGenBuffers(2, buffers);
    glGenVertexArrays(1,&vertexArrayID);

    // create the VBO associated with the grid (the terrain)
    glBindVertexArray(vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]); // vertices
    glBufferData(GL_ARRAY_BUFFER,mesh->getNBVertices()*3*sizeof(float),mesh->getVertices(),GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[1]); // indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,mesh->getNBFaces()*3*sizeof(unsigned int),mesh->getFaces(),GL_STATIC_DRAW);
}

void MeshObject::deleteVAO(){
    glDeleteBuffers(2,buffers);
    glDeleteVertexArrays(1,&vertexArrayID);
}

void MeshObject::setUniform(glm::mat4 viewMat, glm::mat4 projectionMat, glm::vec3 light){

    glm::mat4 modelMat = transform->getMat4();


    // send the transformation matrix
    material->callUniform(modelMat, viewMat, projectionMat, light);

}


void MeshObject::createUI(char *ID){
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
