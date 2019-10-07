#include "cubeMesh.h"


CubeMesh::CubeMesh(){
    nb_vertices = 8;
    nb_faces = 12;

    vertices = (float *)malloc(3*nb_vertices*sizeof(float));
    normals  = (float *)malloc(3*nb_vertices*sizeof(float));
    tangents = (float *)malloc(3*nb_vertices*sizeof(float));
    colors   = (float *)malloc(3*nb_vertices*sizeof(float));
    coords   = (float *)malloc(2*nb_vertices*sizeof(float));
    faces    = (unsigned int *)malloc(3*nb_faces*sizeof(unsigned int));

    createVertices();
    createFaces();

    computeCenter();
    computeRadius();
    computeNormals();

}

CubeMesh::~CubeMesh(){
    if(normals!=NULL){
        free(normals);
        normals = NULL;
    }
    if(tangents!=NULL){
        free(tangents);
        tangents = NULL;
    }
    if(colors!=NULL){
        free(colors);
        colors = NULL;
    }
    if(vertices!=NULL){
        free(vertices);
        vertices = NULL;
    }
    if(faces!=NULL){
        free(faces);
        faces = NULL;
    }
    if(coords!=NULL){
        free(coords);
        coords = NULL;
    }

}

void CubeMesh::computeCenter(){
    center[0] = 0.0;
    center[1] = 0.0;
    center[2] = 0.0;
}

void CubeMesh::computeRadius(){
    radius = 2.0;
}

void CubeMesh::computeNormals(){
    for(unsigned int i=0; i<3*nb_vertices; i++){
        normals[i] = 0.0;
    }
}

void CubeMesh::createVertices(){

    addVertex(0, glm::vec3(-1.0, -1.0, 1.0));
    // 1
    addVertex(1, glm::vec3(-1.0, 1.0, 1.0));
    // 2
    addVertex(2, glm::vec3(1.0, 1.0, 1.0));
    // 3
    addVertex(3, glm::vec3(1.0, -1.0, 1.0));
    // 4
    addVertex(4, glm::vec3(-1.0, -1.0, -1.0));
    // 5
    addVertex(5, glm::vec3(-1.0, 1.0, -1.0));
    // 6
    addVertex(6, glm::vec3(1.0, 1.0, -1.0));
    // 7
    addVertex(7, glm::vec3(1.0, -1.0, -1.0));


}


void CubeMesh::createFaces(){

        // front face
    faces[0] = 0; faces[1] = 1; faces[2] = 2;
    faces[3] = 0; faces[4] = 2; faces[5] = 3;
        // back face
    faces[6] = 7; faces[7] = 6; faces[8] = 5;
    faces[9] = 7; faces[10] = 5; faces[11] = 4;
        // upper face
    faces[12] = 1; faces[13] = 5; faces[14] = 6;
    faces[15] = 1; faces[16] = 6; faces[17] = 2;
        // bottom face
    faces[18] = 4; faces[19] = 0; faces[20] = 3;
    faces[21] = 4; faces[22] = 3; faces[23] = 7;
        // left face
    faces[24] = 4; faces[25] = 5; faces[26] = 1;
    faces[27] = 4; faces[28] = 1; faces[29] = 0;
        // right face
    faces[30] = 3; faces[31] = 2; faces[32] = 6;
    faces[33] = 3; faces[34] = 6; faces[35] = 7;

}


void CubeMesh::addVertex(int i, glm::vec3 v){
    vertices[i*3] = v[0];
    vertices[i*3+1] = v[1];
    vertices[i*3+2] = v[2];
}
