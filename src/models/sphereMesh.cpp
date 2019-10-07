
#include "sphereMesh.h"

#include <vector>

#include <stdio.h>

using namespace glm;

SphereMesh::SphereMesh(float radius, unsigned int rings, unsigned int sectors){

    createMesh(radius, rings);


}

void SphereMesh::createMesh(float radius, unsigned int divs){

    nb_vertices = 12;
    nb_faces = 20;


    vertices = (float *)malloc(3*nb_vertices*sizeof(float));
    normals  = (float *)malloc(3*nb_vertices*sizeof(float));
    tangents = (float *)malloc(3*nb_vertices*sizeof(float));
    colors   = (float *)malloc(3*nb_vertices*sizeof(float));
    coords   = (float *)malloc(2*nb_vertices*sizeof(float));
    faces    = (unsigned int *)malloc(3*nb_faces*sizeof(unsigned int));

    const float X=.525731112119133606f;
    const float Z=.850650808352039932f;
    const float N=0.f;

    numVertex = 0;

    addVertex(-X,N,Z); addVertex(X,N,Z); addVertex(-X,N,-Z); addVertex(X,N,-Z);
    addVertex(N,Z,X); addVertex(N,Z,-X); addVertex(N,-Z,X); addVertex(N,-Z,-X);
    addVertex(Z,X,N); addVertex(-Z,X, N); addVertex(Z,-X,N); addVertex(-Z,-X, N);

    numFace = 0;

    addFace(0,4,1); addFace(0,9,4); addFace(9,5,4); addFace(4,5,8); addFace(4,8,1);
    addFace(8,10,1); addFace(8,3,10); addFace(5,3,8); addFace(5,2,3); addFace(2,7,3);
    addFace(7,10,3); addFace(7,6,10); addFace(7,11,6); addFace(11,0,6); addFace(0,1,6);
    addFace(6,1,10); addFace(9,0,11); addFace(9,11,2); addFace(9,2,5); addFace(7,2,11);

    computeCenter();
    computeRadius();

    computeNormals();
    computeTangents();
    computeUVCoord();

}


void SphereMesh::addVertex(float x, float y, float z){
    vertices[numVertex] = x;
    vertices[numVertex+1] = y;
    vertices[numVertex+2] = z;
    numVertex += 3;
}

void SphereMesh::addFace(unsigned int v1, unsigned int v2, unsigned int v3){
    faces[numFace] = v1;
    faces[numFace+1] = v2;
    faces[numFace+2] = v3;
    numFace += 3;
}



void SphereMesh::computeCenter(){
    center[0] = 0.0;
    center[1] = 0.0;
    center[2] = 0.0;
}

void SphereMesh::computeRadius(){
    radius = 2.0;
}

void SphereMesh::subdivide(){

    std::vector<unsigned int> newFaces = std::vector<unsigned int>();
    std::vector<float>newVertices = std::vector<float>();

    glm::vec3 v1,v2,v3;

    // for each face
    for(unsigned int i=0; i<3*nb_faces; i+=3){

        v1 = getVertex(i);
        v2 = getVertex(i+1);
        v3 = getVertex(i+2);


    }

    /*for (auto&& each:triangles)    {
        std::array<Index, 3> mid;
        for (int edge=0; edge<3; ++edge){
            mid[edge]=vertex_for_edge(lookup, vertices,
            each.vertex[edge], each.vertex[(edge+1)%3]);
        }

        result.push_back({each.vertex[0], mid[0], mid[2]});
        result.push_back({each.vertex[1], mid[1], mid[0]});
        result.push_back({each.vertex[2], mid[2], mid[1]});
        result.push_back({mid[0], mid[1], mid[2]});
    }*/


    nb_vertices = newVertices.size();
    vertices = &newVertices[0];

    nb_faces = newFaces.size();
    faces = &newFaces[0];

}

glm::vec3 SphereMesh::getVertex(int index){
    glm::vec3 vertex;
    vertex[0] = vertices[index];
    vertex[1] = vertices[index+1];
    vertex[2] = vertices[index+2];
    return vertex;
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
