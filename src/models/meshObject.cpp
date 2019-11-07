
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#define POSITION_ATTRIB 0
#define VERTEX_NORMAL_ATTRIB 1


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

#include <iostream>






int MeshObject::nbVertices(){
    return mesh->getNBVertices();
}

int MeshObject::nbTriangles(){
    return mesh->getNBFaces();
}



void MeshObject::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){

    glUseProgram(material->getShaderID());

    setUniform(modelMat, viewMat, projectionMat, light);

    glBindVertexArray(vertexArrayID);
    glDrawElements(GL_TRIANGLES,3*mesh->getNBFaces(),GL_UNSIGNED_INT,(void *)0);
    glBindVertexArray(0);

    glUseProgram(0);

    // mesh->drawDebug(transform->getModelMat(),viewMat, projectionMat);

    if(showboundingbox){
        drawBoxWithMatricess(mesh->getMin(), mesh->getMax(),modelMat, viewMat, projectionMat);
    }


}

void MeshObject::createVAO(){

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

void MeshObject::deleteVAO(){
    glDeleteBuffers(2,buffers);
    glDeleteVertexArrays(1,&vertexArrayID);
}

void MeshObject::setUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light* light){

    // glm::mat4 model = transform->getMat4(modelMat);



    // send the transformation matrix
    material->callUniform(modelMat, viewMat, projectionMat, light);

}


void MeshObject::createUI(char *ID){
    ImGui::BeginChild(ID);
    ImGui::Text(name.c_str());

    ImGui::Separator();
    transform->createUI();

    ImGui::Separator();
    mesh->createUI();
    if (ImGui::Button("Simplify")){
        mesh->simplify();
        createVAO();
    }
    if (ImGui::Button("Recreate")){
        mesh->recreate();
        createVAO();
    }
    ImGui::Text("Show bounding box "); ImGui::SameLine();
    ImGui::Checkbox("##showboundingbox"+getID(),&showboundingbox);
    ImGui::Separator();
    material->createUI();
    ImGui::Separator();

    ImGui::EndChild();
}

void drawQuadWithTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4){
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v4.x, v4.y, v4.z);

    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glVertex3f(v4.x, v4.y, v4.z);
}

// draw box that move with the object
void MeshObject::drawBoxWithMatricess(glm::vec3 min, glm::vec3 max, glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat){

    Shader *shader = new Shader();
    shader->load("../data/shaders/displayBoundingBox.vert","../data/shaders/displayBoundingBox.frag");

    glUseProgram(shader->id());



    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"projMat"),1,GL_FALSE,&(projectionMat[0][0]));

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glBegin(GL_TRIANGLES);

    // front face
    drawQuadWithTriangle(glm::vec3(min.x,max.y,max.z), glm::vec3(max.x,max.y,max.z), glm::vec3(max.x,min.y,max.z), glm::vec3(min.x,min.y,max.z));
    // back face
    drawQuadWithTriangle(glm::vec3(max.x,max.y,min.z), glm::vec3(min.x,max.y,min.z), glm::vec3(min.x,min.y,min.z), glm::vec3(max.x,min.y,min.z));
    // left face
    drawQuadWithTriangle(glm::vec3(min.x,max.y,min.z), glm::vec3(min.x,min.y,max.z), glm::vec3(min.x,min.y,max.z), glm::vec3(min.x,min.y,min.z));
    // right face
    drawQuadWithTriangle(glm::vec3(max.x,max.y,max.z), glm::vec3(max.x,max.y,min.z), glm::vec3(max.x,min.y,min.z), glm::vec3(max.x,min.y,max.z));
    // bottom face
    drawQuadWithTriangle(glm::vec3(min.x,min.y,max.z), glm::vec3(max.x,min.y,max.z), glm::vec3(max.x,min.y,min.z), glm::vec3(min.x,min.y,min.z));
    // top face
    drawQuadWithTriangle(glm::vec3(min.x,max.y,min.z), glm::vec3(max.x,max.y,min.z), glm::vec3(max.x,max.y,max.z), glm::vec3(min.x,max.y,max.z));


    glEnd();

    glUseProgram(0);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


}
