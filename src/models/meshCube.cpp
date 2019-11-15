#include "meshCube.h"

MeshCube::MeshCube(float w = 1.0f){
    width = w;

    createMesh(width);

}


MeshCube::~MeshCube(){

}


void MeshCube::recreate(){
    createMesh(width);
}
/*
void MeshCube::createUI(){

}*/


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
    vertices.resize(nb_vertices);

    vertices[0] = glm::vec3(0,0,1);
    vertices[1] = glm::vec3(1,0,1);
    vertices[2] = glm::vec3(0,1,1);
    vertices[3] = glm::vec3(1,1,1);
    vertices[4] = glm::vec3(0,0,0);
    vertices[5] = glm::vec3(1,0,0);
    vertices[6] = glm::vec3(0,1,0);
    vertices[7] = glm::vec3(1,1,0);
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
