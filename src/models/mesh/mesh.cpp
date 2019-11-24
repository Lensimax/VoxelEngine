#include <imgui.h>

#include "mesh.h"

#include "../../material/shader.h"

#include <math.h>

#include <iostream>
#include <unordered_map>

#ifndef M_PI
#define M_PI 3.1415926
#endif



std::vector<unsigned int> Mesh::get_face(unsigned int i) {
    std::vector<unsigned int> face = std::vector<unsigned int>(3);
    face[0] = faces[i*3]; face[1] = faces[i*3 +1]; face[2] = faces[i*3+2];
    return face;
}

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

void *Mesh::getFaces(){
    return &(faces[0]);
}

void *Mesh::getNormals(){
    return &(normals[0]);
}

void *Mesh::getUVs(){
    return &(coords[0]);
}

unsigned int Mesh::getNBVertices(){
    return vertices.size();
}

unsigned int Mesh::getNBFaces(){
    return faces.size()/3;
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
        for(unsigned int i=0; i<nb_vertices; i++){
            ImGui::Text("%4f",vertices[i].x); ImGui::NextColumn();
            ImGui::Text("%4f",vertices[i].y); ImGui::NextColumn();
            ImGui::Text("%4f", vertices[i].z); ImGui::NextColumn();
        }

        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::TreePop();

    }

    if (ImGui::TreeNode("Faces")){

        ImGui::Columns(3, "Face"); // 4-ways, with border
        ImGui::Separator();
        ImGui::Text("V1"); ImGui::NextColumn();
        ImGui::Text("V2"); ImGui::NextColumn();
        ImGui::Text("V3"); ImGui::NextColumn();
        ImGui::Separator();
        for(unsigned int i=0; i<nb_faces; i++){
            ImGui::Text("%d",faces[3*i]); ImGui::NextColumn();
            ImGui::Text("%d",faces[3*i+1]); ImGui::NextColumn();
            ImGui::Text("%d", faces[3*i+2]); ImGui::NextColumn();
        }

        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::TreePop();
    }

    ImGui::Text("Bounding Box");
    ImGui::Text("min: %f, %f, %f", minX, minY, minZ);
    ImGui::Text("max: %f, %f, %f", maxX, maxY, maxZ);


    ImGui::Text("center: %f, %f, %f", center.x, center.y,center.z);
    ImGui::Text("radius: %f", radius);

}


glm::vec3 Mesh::getCenter(){
    return center;
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
