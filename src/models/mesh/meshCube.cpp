#include "meshCube.h"

#include <imgui.h>

MeshCube::MeshCube(float w = 1.0f){
    width = w;

    // createMesh(width);

    createPositions(3);
    createVAO();

}


MeshCube::~MeshCube(){
    deleteVAO();
}


void MeshCube::recreate(){
    createMesh(width);
}

void MeshCube::createUI(){
    Mesh::createUI();

    ImGui::Text("Width : ");
    ImGui::DragFloat("##width", &width, 0.01f);  
}


void MeshCube::createMesh(float w){

    nb_faces = 12*3;
    nb_vertices = 8;

    createPositions(w);
    createTriangles();
    
    createInfo();

    backupFaces = faces;
    backupVertices = vertices;

}

void MeshCube::createPositions(float w){


    static const float g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end

    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end

    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,

    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,

    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,

    // A FAIRE
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,

    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,

    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,

    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,

    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
    };

    // vertices[0] = g_vertex_buffer_data;
    nb_vertices = 18;
    vertices.resize(nb_vertices);
    normals.resize(nb_vertices);

    vertices[0] = glm::vec3(-1.0f,-1.0f,-1.0f); // triangle 1 : begin
    vertices[1] = glm::vec3(-1.0f,-1.0f, 1.0f);
    vertices[2] = glm::vec3(-1.0f, 1.0f, 1.0f);
    normals[0] = glm::vec3(-1.0f,0.0f,0.0f);
    normals[1] = glm::vec3(-1.0f,0.0f, 0.0f);
    normals[2] = glm::vec3(-1.0f, 0.0f, 0.0f);
    

    vertices[3] = glm::vec3(1.0f, 1.0f,-1.0f);
    vertices[4] = glm::vec3(-1.0f,-1.0f,-1.0f);
    vertices[5] = glm::vec3(-1.0f, 1.0f,-1.0f);
    normals[3] = glm::vec3(0.0f,0.0f,-1.0f);
    normals[4] = glm::vec3(0.0f,0.0f, -1.0f);
    normals[5] = glm::vec3(0.0f, 0.0f, -1.0f);

    vertices[6] = glm::vec3(1.0f,-1.0f, 1.0f);
    vertices[7] = glm::vec3(-1.0f,-1.0f,-1.0f);
    vertices[8] = glm::vec3(1.0f,-1.0f,-1.0f);
    normals[6] = glm::vec3(0.0f,-1.0f,0.0f);
    normals[7] = glm::vec3(0.0f,-1.0f, 0.0f);
    normals[8] = glm::vec3(0.0f, -1.0f, 0.0f);

    vertices[9] = glm::vec3(1.0f, 1.0f,-1.0f);
    vertices[10] = glm::vec3(1.0f,-1.0f,-1.0f);
    vertices[11] = glm::vec3(-1.0f,-1.0f,-1.0f);
    normals[9] = glm::vec3(0.0f,0.0f,-1.0f);
    normals[10] = glm::vec3(0.0f,0.0f, -1.0f);
    normals[11] = glm::vec3(0.0f, 0.0f, -1.0f);

    vertices[12] = glm::vec3(-1.0f,-1.0f,-1.0f);
    vertices[13] = glm::vec3(-1.0f, 1.0f, 1.0f);
    vertices[14] = glm::vec3(-1.0f, 1.0f,-1.0f);
    normals[12] = glm::vec3(-1.0f,0.0f,0.0f);
    normals[13] = glm::vec3(-1.0f, 0.0f, 0.0f);
    normals[14] = glm::vec3(-1.0f, 0.0f,0.0f);

    vertices[15] = glm::vec3(1.0f,-1.0f, 1.0f);
    vertices[16] = glm::vec3(-1.0f,-1.0f, 1.0f);
    vertices[17] = glm::vec3(-1.0f,-1.0f,-1.0f);
    normals[15] = glm::vec3(0.0f,-1.0f, 0.0f);
    normals[16] = glm::vec3(0.0f,-1.0f, 0.0f);
    normals[17] = glm::vec3(0.0f,-1.0f,0.0f);
    
    
}

void MeshCube::createTriangles(){

    faces.resize(nb_faces);

    faces[0] = 0; faces[1] = 1; faces[2] = 2;
    faces[3] = 1; faces[4] = 3; faces[5] = 2;
    faces[6] = 2; faces[7] = 3; faces[8] = 7;
    faces[9] = 2; faces[10] = 7; faces[11] = 6;
    faces[12] = 1; faces[13] = 7; faces[14] = 3;
    faces[15] = 1; faces[16] = 5; faces[17] = 7;
    faces[18] = 6; faces[19] = 7; faces[20] = 4;
    faces[21] = 7; faces[22] = 5; faces[23] = 4;
    faces[24] = 0; faces[25] = 4; faces[26] = 1;
    faces[27] = 1; faces[28] = 4; faces[29] = 5;
    faces[30] = 2; faces[31] = 6; faces[32] = 4;
    faces[33] = 0; faces[34] = 2; faces[35] = 4;

}

void MeshCube::createInfo(){
    coords.resize(nb_vertices);
    tangents.resize(nb_vertices);
    normals.resize(nb_vertices);
    colors.resize(nb_vertices);

    for(unsigned int i=0; i<nb_vertices; i++){
        coords[i] = glm::vec2(0);
        normals[i] = glm::vec3(0,1,0);
        tangents[i] = glm::vec3(0,0,1);
        colors[i] = glm::vec3(1,1,0);
    }
}
