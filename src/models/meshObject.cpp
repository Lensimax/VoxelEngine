
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#define POSITION_ATTRIB 0
#define VERTEX_NORMAL_ATTRIB 1
#define VERTEX_UV_ATTRIB 2


#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include "meshObject.h"

#include <iostream>


MeshObject::MeshObject(){

}

MeshObject::MeshObject(int id, std::string n, Transform *t, Mesh *m, Material *mat){
    m_transform = t;


    mesh = m;

    t->setCenter(glm::vec3(0));

    material = mat;

    setName(n);
    setID(id);

}


MeshObject::~MeshObject(){
    delete material;
    delete mesh;
}



int MeshObject::nbVertices(){
    return mesh->getNBVertices();
}

int MeshObject::nbTriangles(){
    return mesh->getNBFaces();
}



void MeshObject::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light){

    glUseProgram(material->getShaderID());

    setUniform(modelMat, viewMat, projectionMat, light);

    mesh->drawVAO();

    glUseProgram(0);

    // mesh->drawDebug(transform->getModelMat(),viewMat, projectionMat);

    if(showboundingbox){
        drawBoxWithMatricess(mesh->getMin(), mesh->getMax(),modelMat, viewMat, projectionMat);
    }


}



void MeshObject::setUniform(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light* light){

    // glm::mat4 model = transform->getMat4(modelMat);



    // send the transformation matrix
    material->callUniform(modelMat, viewMat, projectionMat, light);

}

void MeshObject::update(){
    EngineObject::update();
    mesh->update();
}


void MeshObject::createUI(char *ID){
    const int node_flags = 0;

    ImGui::BeginChild(ID);
    ImGui::Text(m_name.c_str());

    ImGui::Separator();
    m_transform->createUI();

    ImGui::Separator();
    bool node_mesh = ImGui::TreeNodeEx("Mesh", node_flags);
    if(node_mesh){
        mesh->createUI();
        if (ImGui::Button("Recreate")){
            mesh->recreate();
            
        }
        ImGui::Text("Show bounding box "); ImGui::SameLine();
        ImGui::Checkbox("##showboundingbox"+getID(),&showboundingbox);

        ImGui::TreePop();
    }

    ImGui::Separator();
    bool node_material = ImGui::TreeNodeEx("Material", node_flags);
    if(node_material){
        material->createUI();
        ImGui::TreePop();
    }
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



}
