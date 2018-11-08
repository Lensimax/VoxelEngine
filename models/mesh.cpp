#include "../imgui/imgui.h"

#include "mesh.h"


unsigned int *Mesh::get_face(unsigned int i) {
  return &(faces[3*i]);
}

float *Mesh::get_vertex(unsigned int i) {
  return &(vertices[3*i]);
}

float *Mesh::get_normal(unsigned int i) {
  return &(normals[3*i]);
}

float *Mesh::get_tangent(unsigned int i) {
  return &(tangents[3*i]);
}

float *Mesh::get_coord(unsigned int i) {
  return &(coords[2*i]);
}

float *Mesh::get_color(unsigned int i) {
  return &(colors[3*i]);
}

float *Mesh::getVertices(){
    return &(vertices[0]);
}

unsigned int *Mesh::getFaces(){
    return &(faces[0]);
}

unsigned int Mesh::getNBVertices(){
    return nb_vertices;
}

unsigned int Mesh::getNBFaces(){
    return nb_faces;
}

void Mesh::createUI(){
    ImGui::Text("Mesh");
    ImGui::Text("Number vertices: %d", nb_vertices/3);
    ImGui::Text("Number faces: %d", nb_faces/3);
}

void Mesh::recreate(){

}
