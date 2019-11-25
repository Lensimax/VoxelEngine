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

////// FACES
/// 1 FRONT
/// 2 BACK
/// 3 LEFT
/// 4 RIGHT
/// 5 TOP
/// 6 BOTTOM

void MeshCube::createPositions(float w){

    glm::vec3 normal;

    // vertices[0] = g_vertex_buffer_data;
    nb_vertices = 36;
    vertices.resize(nb_vertices);
    normals.resize(nb_vertices);

    // FRONT
    vertices[0] = glm::vec3(-1.0f, 1.0f, 1.0f);
    vertices[1] = glm::vec3(-1.0f,-1.0f, 1.0f);
    vertices[2] = glm::vec3(1.0f,-1.0f, 1.0f);
    normal = glm::vec3(0,0,1);
    normals[0] = normal;
    normals[1] = normal;
    normals[2] = normal;

    vertices[3] = glm::vec3(1.0f, 1.0f, 1.0f);
    vertices[4] = glm::vec3(-1.0f, 1.0f, 1.0f);
    vertices[5] = glm::vec3(1.0f,-1.0f, 1.0);
    normals[3] = normal;
    normals[4] = normal;
    normals[5] = normal;

    // BACK
    normal = glm::vec3(0,0,-1);
    vertices[6] = glm::vec3(1.0f, 1.0f,-1.0f);
    vertices[7] = glm::vec3(-1.0f,-1.0f,-1.0f);
    vertices[8] = glm::vec3(-1.0f, 1.0f,-1.0f);
    normals[6] = normal;
    normals[7] = normal;
    normals[8] = normal;

    vertices[9] = glm::vec3(1.0f, 1.0f,-1.0f);
    vertices[10] = glm::vec3(1.0f,-1.0f,-1.0f);
    vertices[11] = glm::vec3(-1.0f,-1.0f,-1.0f);
    normals[9] = normal;
    normals[10] = normal;
    normals[11] = normal;

    // LEFT
    normal = glm::vec3(-1,0,0);
    vertices[12] = glm::vec3(-1.0f,-1.0f,-1.0f);
    vertices[13] = glm::vec3(-1.0f, 1.0f, 1.0f);
    vertices[14] = glm::vec3(-1.0f, 1.0f,-1.0f);
    normals[12] = normal;
    normals[13] = normal;
    normals[14] = normal;

    vertices[15] = glm::vec3(-1.0f,-1.0f,-1.0f);
    vertices[16] = glm::vec3(-1.0f,-1.0f, 1.0f);
    vertices[17] = glm::vec3(-1.0f, 1.0f, 1.0f);
    normals[15] = normal;
    normals[16] = normal;
    normals[17] = normal;
    
    // RIGHT
    normal = glm::vec3(1,0,0);
    vertices[18] = glm::vec3(1.0f, 1.0f, 1.0f);
    vertices[19] = glm::vec3(1.0f,-1.0f,-1.0f);
    vertices[20] = glm::vec3(1.0f, 1.0f,-1.0f);
    normals[18] = normal;
    normals[19] = normal;
    normals[20] = normal;

    vertices[21] = glm::vec3(1.0f,-1.0f,-1.0f);
    vertices[22] = glm::vec3(1.0f, 1.0f, 1.0f);
    vertices[23] = glm::vec3(1.0f,-1.0f, 1.0f);
    normals[21] = normal;
    normals[22] = normal;
    normals[23] = normal;

    // TOP
    normal = glm::vec3(0,1,0);
    vertices[24] = glm::vec3(1.0f, 1.0f, 1.0f);
    vertices[25] = glm::vec3(1.0f, 1.0f,-1.0f);
    vertices[26] = glm::vec3(-1.0f, 1.0f,-1.0f);
    normals[24] = normal;
    normals[25] = normal;
    normals[26] = normal;

    vertices[27] = glm::vec3(1.0f, 1.0f, 1.0f);
    vertices[28] = glm::vec3(-1.0f, 1.0f,-1.0f);
    vertices[29] = glm::vec3(-1.0f, 1.0f, 1.0f);
    normals[27] = normal;
    normals[28] = normal;
    normals[29] = normal;

    // BOTTOM
    normal = glm::vec3(0,-1,0);
    vertices[30] = glm::vec3(1.0f,-1.0f, 1.0f);
    vertices[31] = glm::vec3(-1.0f,-1.0f,-1.0f);
    vertices[32] = glm::vec3(1.0f,-1.0f,-1.0f);
    normals[30] = normal;
    normals[31] = normal;
    normals[32] = normal;

    vertices[33] = glm::vec3(1.0f,-1.0f, 1.0f);
    vertices[34] = glm::vec3(-1.0f,-1.0f, 1.0f);
    vertices[35] = glm::vec3(-1.0f,-1.0f,-1.0f);
    normals[33] = normal;
    normals[34] = normal;
    normals[35] = normal;

    





    
    
    
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
