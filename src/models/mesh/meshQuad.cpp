#include "meshQuad.h"

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include <vector>

#include <stdio.h>

MeshQuad::MeshQuad(){

    createMesh();

}




MeshQuad::~MeshQuad(){

}

void MeshQuad::recreate(){

}

void MeshQuad::createMesh(){
    nb_vertices = 4;
    nb_faces = 2;

    vertices.resize(nb_vertices);
    vertices[0] = glm::vec3(-1,1,0);
    vertices[1] = glm::vec3(1,1,0);
    vertices[2] = glm::vec3(1,-1,0);
    vertices[3] = glm::vec3(-1,-1,0);

    faces.resize(nb_faces*3); // 2 faces * 3 sommets par triangle
    // faces[0].resize(3);
    // faces[1].resize(3);
    faces[0] = 0; faces[1] = 1; faces[2] = 2;
    faces[3] = 0; faces[4] = 2; faces[5] = 3;

    normals.resize(nb_vertices);
    coords.resize(nb_vertices);

    for(unsigned int i=0; i<nb_vertices; i++){
        normals[i] = glm::vec3(0,0,1);
        coords[i] = vertices[i]*0.5f + 0.5f;
    }

    computeTangents();

    center = glm::vec3(0,0,0);
    radius = 1;

    computeColor();

}
