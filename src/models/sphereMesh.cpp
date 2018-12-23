
#include "sphereMesh.h"

#include <vector>

SphereMesh::SphereMesh(float radius, unsigned int rings, unsigned int sectors){

    createMesh(radius, rings, sectors);

    computeCenter();

    // computing radius
    computeRadius();

    computeNormals();

    // computing colors as normals
    for(int i=0;i<3*nb_vertices;++i) {
      colors[i] = (normals[i]+1.0)/2.0;
    }

    computeUVCoord();

    computeTangents();
}



SphereMesh::~SphereMesh(){
    free(vertices);
    free(faces);
}

void SphereMesh::createMesh(float radius, unsigned int rings, unsigned int sectors){

    std::vector<float> vecVertices =  std::vector<float>();
    std::vector<unsigned int> vecFaces = std::vector<unsigned int>();
    std::vector<float> vecNormals = std::vector<float>();
    std::vector<float> vecTexCoords = std::vector<float>();


    float const R = 1./(float)(rings-1);
    float const S = 1./(float)(sectors-1);

    vecVertices.resize(rings * sectors * 3);
    vecNormals.resize(rings * sectors * 3);
    vecTexCoords.resize(rings * sectors * 2);
    std::vector<float>::iterator v = vecVertices.begin();
    std::vector<float>::iterator n = vecNormals.begin();
    std::vector<float>::iterator t = vecTexCoords.begin();
    for(unsigned int r = 0; r < rings; r++){
        for(unsigned int s = 0; s < sectors; s++) {
            float const y = sin( -M_PI_2 + M_PI * r * R );
            float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
            float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

            *t++ = s*S;
            *t++ = r*R;

            *v++ = x * radius;
            *v++ = y * radius;
            *v++ = z * radius;

            *n++ = x;
            *n++ = y;
            *n++ = z;
        }
    }

    vecFaces.resize(rings * sectors * 4);
    std::vector<unsigned int>::iterator i = vecFaces.begin();
    for(unsigned int r = 0; r < rings; r++) {
        for(unsigned int s = 0; s < sectors; s++) {
            *i++ = r * sectors + s;
            *i++ = r * sectors + (s+1);
            *i++ = (r+1) * sectors + (s+1);
            *i++ = (r+1) * sectors + s;
        }
    }

    nb_vertices = vecVertices.size()/3;
    nb_faces = vecFaces.size()/3;

    vertices = (float *)malloc(3*nb_vertices*sizeof(float));
    faces = (unsigned int *)malloc(3*nb_faces*sizeof(unsigned int));



}
