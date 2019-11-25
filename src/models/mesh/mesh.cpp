#include <imgui.h>





#define POSITION_ATTRIB 0
#define VERTEX_NORMAL_ATTRIB 1
#define VERTEX_UV_ATTRIB 2

#include "mesh.h"

#include "../../material/shader.h"

#include <math.h>

#include <iostream>
#include <unordered_map>

#ifndef M_PI
#define M_PI 3.1415926
#endif



glm::vec3 Mesh::get_vertex(unsigned int i) {
  return vertices[i];
}

glm::vec3 Mesh::get_normal(unsigned int i) {
  return normals[i];
}

glm::vec3 Mesh::get_tangent(unsigned int i) {
  return tangents[i];
}

glm::vec2 Mesh::get_coord(unsigned int i) {
  return coords[i];
}

glm::vec3 Mesh::get_color(unsigned int i) {
  return colors[i];
}

void *Mesh::getVertices(){
    return &(vertices[0]);
}


void *Mesh::getNormals(){
    return &(normals[0]);
}

void *Mesh::getUVs(){
    return &(coords[0]);
}



void Mesh::createUI(){
    ImGui::Text("Number vertices: %d", getNBVertices());
    ImGui::Text("Number faces: %d", getNBFaces());


    ImGui::Separator();
    if (ImGui::TreeNode("Vertices")){

        ImGui::Columns(3, "Vertices"); // 4-ways, with border
        ImGui::Separator();
        ImGui::Text("X"); ImGui::NextColumn();
        ImGui::Text("Y"); ImGui::NextColumn();
        ImGui::Text("Z"); ImGui::NextColumn();
        ImGui::Separator();
        for(unsigned int i=0; i<getNBVertices(); i++){
            ImGui::Text("%4f",vertices[i].x); ImGui::NextColumn();
            ImGui::Text("%4f",vertices[i].y); ImGui::NextColumn();
            ImGui::Text("%4f", vertices[i].z); ImGui::NextColumn();
        }

        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::TreePop();

    }

    ImGui::Text("Bounding Box");
    ImGui::Text("min: %f, %f, %f", minX, minY, minZ);
    ImGui::Text("max: %f, %f, %f", maxX, maxY, maxZ);


    ImGui::Text("radius: %f", radius);

}



////// COMPUTE BOUNDING BOX /////

void Mesh::computeBoundingBox(){
    assert(vertices.size() > 0);

    maxX = vertices[0].x; maxY = vertices[0].y; maxZ = vertices[0].z;
    minX = vertices[0].x; minY = vertices[0].y; minZ = vertices[0].z;

    for(unsigned int i=0; i<vertices.size(); i++){
        if(vertices[i].x > maxX){
            maxX = vertices[i].x;
        } else if(vertices[i].x < minX){
            minX = vertices[i].x;
        }
        if(vertices[i].y > maxY){
            maxY = vertices[i].y;
        } else if(vertices[i].y < minY){
            minY = vertices[i].y;
        }
        if(vertices[i].z > maxZ){
            maxZ = vertices[i].z;
        } else if(vertices[i].z < minZ){
            minZ = vertices[i].z;
        }
    }



}

void Mesh::update(){

}

void Mesh::inflateBoundingBox(){
    const float percent = 0.1f;
    maxX += percent*radius; maxY += percent*radius; maxZ += percent*radius;
    minX -= percent*radius; minY -= percent*radius; minZ -= percent*radius;
}


glm::vec3 Mesh::getMin(){
    return glm::vec3(minX, minY, minZ);
}


glm::vec3 Mesh::getMax(){
    return glm::vec3(maxX, maxY, maxZ);
}


void Mesh::createVAO(){

    buffers = new GLuint[2];

    glGenBuffers(2, buffers);
    glGenVertexArrays(1,&vertexArrayID);

    // create the VBO associated with the grid (the terrain)
    glBindVertexArray(vertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]); // vertices
    glBufferData(GL_ARRAY_BUFFER,getNBVertices()*3*sizeof(float),getVertices(),GL_STATIC_DRAW);
    glEnableVertexAttribArray(POSITION_ATTRIB);
    glVertexAttribPointer(POSITION_ATTRIB,3,GL_FLOAT,GL_FALSE,0,(void *)0);


    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[1]); // indices
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER,mesh->getNBFaces()*3*sizeof(unsigned int),mesh->getFaces(),GL_STATIC_DRAW);

    // normals
    glEnableVertexAttribArray(VERTEX_NORMAL_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, getNBVertices()*3* sizeof(float), getNormals(), GL_STATIC_DRAW); //normals is std::vector<float>
    glVertexAttribPointer(VERTEX_NORMAL_ATTRIB, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // texture coordinates
    // glEnableVertexAttribArray(VERTEX_UV_ATTRIB);
    // glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
    // glBufferData(GL_ARRAY_BUFFER, mesh->getNBVertices()*2* sizeof(float), mesh->getUVs(), GL_STATIC_DRAW); //normals is std::vector<float>
    // glVertexAttribPointer(VERTEX_UV_ATTRIB, 2, GL_FLOAT, GL_FALSE, 0, 0);
    //indices
    glBindVertexArray(0);
}


void Mesh::drawVAO(){

    glBindVertexArray(vertexArrayID);
    glDrawArrays(GL_TRIANGLES,0,getNBVertices());
    glBindVertexArray(0);

}

void Mesh::deleteVAO(){
    glDeleteBuffers(2,buffers);
    glDeleteVertexArrays(1,&vertexArrayID);
    delete buffers;
}