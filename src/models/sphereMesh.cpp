
#include "sphereMesh.h"

#include <vector>

#include <stdio.h>

using namespace glm;

SphereMesh::SphereMesh(float radius, unsigned int rings, unsigned int sectors){

    createMesh(radius, rings);


}

void SphereMesh::createMesh(float radius, unsigned int divs){

    nb_vertices = 60;
    nb_faces = 10;


    vertices = (float *)malloc(3*nb_vertices*sizeof(float));
    normals  = (float *)malloc(3*nb_vertices*sizeof(float));
    tangents = (float *)malloc(3*nb_vertices*sizeof(float));
    colors   = (float *)malloc(3*nb_vertices*sizeof(float));
    coords   = (float *)malloc(2*nb_vertices*sizeof(float));
    faces    = (unsigned int *)malloc(3*nb_faces*sizeof(unsigned int));

    unsigned int triangles[] = {
      0,4,1, 0,9,4, 9,5,4, 4,5,8, 4,8,1,
      8,10,1, 8,3,10, 5,3,8, 5,2,3, 2,7,3,
      7,10,3, 7,6,10, 7,11,6, 11,0,6, 0,1,6,
      6,1,10, 9,0,11, 9,11,2, 9,2,5, 7,2,11
     };



}
/*
struct Triangle
{
  Index vertex[3];
};

using TriangleList=std::vector<Triangle>;
using VertexList=std::vector<v3>;

namespace icosahedron
{
const float X=.525731112119133606f;
const float Z=.850650808352039932f;
const float N=0.f;

static const VertexList vertices=
{
  {-X,N,Z}, {X,N,Z}, {-X,N,-Z}, {X,N,-Z},
  {N,Z,X}, {N,Z,-X}, {N,-Z,X}, {N,-Z,-X},
  {Z,X,N}, {-Z,X, N}, {Z,-X,N}, {-Z,-X, N}
};

static const TriangleList triangles=
{
  {0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
  {8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
  {7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
  {6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
};
}*/


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
