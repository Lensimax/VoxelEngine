
#include "sphereMesh.h"

#include <vector>

#include <stdio.h>

using namespace glm;

SphereMesh::SphereMesh(float radius, unsigned int rings, unsigned int sectors){

    createMesh(radius, rings);


}



SphereMesh::~SphereMesh(){
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

void SphereMesh::addVertex(int i, glm::vec3 v){
    vertices[i*3] = v[0];
    vertices[i*3+1] = v[1];
    vertices[i*3+2] = v[2];
}

void SphereMesh::createMesh(float radius, unsigned int divs){

    unsigned int nb_vertices = 1;
    unsigned int nb_faces = 1;

    vertices = (float *)malloc(3*nb_vertices*sizeof(float));
    normals  = (float *)malloc(3*nb_vertices*sizeof(float));
    tangents = (float *)malloc(3*nb_vertices*sizeof(float));
    colors   = (float *)malloc(3*nb_vertices*sizeof(float));
    coords   = (float *)malloc(2*nb_vertices*sizeof(float));
    faces    = (unsigned int *)malloc(3*nb_faces*sizeof(unsigned int));

    // 0
    // addVertex(0, glm::vec3(-1.0, -1.0, 0.0));
    vertices[0] = -1.0; vertices[1] = -1.0; vertices[2] = 0.0;
    // 1
    // addVertex(1, glm::vec3(-1.0, 1.0, 0.0));
    /*vertices[3] = -1.0; vertices[4] = 1.0; vertices[5] = 0.0;
    // 2
    // addVertex(2, glm::vec3(1.0, 1.0, 0.0));
    vertices[6] = 1.0; vertices[7] = 1.0; vertices[8] = 0.0;
    // 3
    // addVertex(3, glm::vec3(1.0, -1.0, 0.0));
    vertices[9] = 1.0; vertices[10] = -1.0; vertices[11] = 0.0;*/


    faces[0] = 0; faces[1] = 1; faces[2] = 2;
    // faces[3] = 0; faces[4] = 2; faces[5] = 3;

    printf("passe\n");

    computeCenter();

    // computing radius
    // computeRadius();

    // computeNormals();
    //
    // for(unsigned int i=0; i<nb_vertices; i+=3){
    //     normals[i] = 1.0;
    //     normals[i+1] = 1.0;
    //     normals[i+2] = 1.0;
    // }


    // computeUVCoord();

    // computeTangents();

}

/*
void SphereMesh::createMesh(float radius, unsigned int divs){

    unsigned int nb_vertices = (divs - 1) * divs + 2;
    unsigned int nb_faces = divs * divs;

    vertices = new float[3*nb_vertices];
    tangents = new float[3*nb_vertices];
    colors = new float[3*nb_vertices];
    coords = new float[3*nb_vertices];
    faces = new unsigned int[3*nb_faces];

    vertices = (float *)malloc(3*nb_vertices*sizeof(float));
    normals  = (float *)malloc(3*nb_vertices*sizeof(float));
    tangents = (float *)malloc(3*nb_vertices*sizeof(float));
    colors   = (float *)malloc(3*nb_vertices*sizeof(float));
    coords   = (float *)malloc(2*nb_vertices*sizeof(float));
    faces    = (unsigned int *)malloc(3*nb_faces*sizeof(unsigned int));


    float u = -M_PI_2;
    float v = -M_PI;
    float du = M_PI / divs;
    float dv = 2 * M_PI / divs;

    vec3 P[] = new vec3[nb_vertices];
    vec3 P[] = new vec3[nb_vertices];
    vec2 st(new vec2[nb_vertices]);

    P[0] = N[0] = (0, -radius, 0);
    unsigned int k = 1;
    for (unsigned int i = 0; i < divs - 1; i++) {
       u += du;
       v = -M_PI;
       for (unsigned int j = 0; j < divs; j++) {
           float x = rad * cos(u) * cos(v);
           float y = rad * sin(u);
           float z = rad * cos(u) * sin(v) ;
           P[k] = N[k] = vec3(x, y, z);
           st[k].x = u / M_PI + 0.5;
           st[k].y = v * 0.5 / M_PI + 0.5;
           v += dv, k++;
       }
    }
    P[k] = N[k] = vec3(0, rad, 0);


    std::unique_ptr faceIndex(new unsigned int[npolys]);
    std::unique_ptr vertsIndex(new unsigned int[(6 + (divs - 1) * 4) * divs]);

    // create the connectivity lists
    unsigned int vid = 1, numV = 0, l = 0;
    k = 0;
    for (unsigned int i = 0; i < divs; i++) {
       for (unsigned int j = 0; j < divs; j++) {
           if (i == 0) {
               faceIndex[k++] = 3;
               vertsIndex[l] = 0;
               vertsIndex[l + 1] = j + vid;
               vertsIndex[l + 2] = (j == (divs - 1)) ? vid : j + vid + 1;
               l += 3;
           }
           else if (i == (divs - 1)) {
               faceIndex[k++] = 3;
               vertsIndex[l] = j + vid + 1 - divs;
               vertsIndex[l + 1] = vid + 1;
               vertsIndex[l + 2] = (j == (divs - 1)) ? vid + 1 - divs : j + vid + 2 - divs;
               l += 3;
           }
           else {
               faceIndex[k++] = 4;
               vertsIndex[l] = j + vid + 1 - divs;
               vertsIndex[l + 1] = j + vid + 1;
               vertsIndex[l + 2] = (j == (divs - 1)) ? vid + 1 : j + vid + 2;
               vertsIndex[l + 3] = (j == (divs - 1)) ? vid + 1 - divs : j + vid + 2 - divs;
               l += 4;
           }
           numV++;
       }
       vid = numV;
    }

}*/
