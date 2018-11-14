#include "meshLoader.h"

#include <imgui.h>

#include <iostream>

#include <math.h>


MeshLoader::MeshLoader(char *filename) {

    sprintf(currentFilename, "%s", filename);
    createMesh(currentFilename);
  //free(nf);
}

void MeshLoader::recreate(){
    if(fopen(currentFilename,"r") == NULL) {
        return;
    }

    cleanup();
    createMesh(currentFilename);
}

void MeshLoader::createMesh(char *filename){
    unsigned int tmp;
    unsigned int i,j;
    FILE *file;
    int   error;

    if((file=fopen(filename,"r"))==NULL) {
      printf("Unable to read %s\n",filename);
    }

    // create MeshLoader
    vertices = NULL;
    normals  = NULL;
    tangents = NULL;
    colors   = NULL;
    coords   = NULL;
    faces    = NULL;

    error = fscanf(file,"OFF\n%d %d %d\n",&(nb_vertices),&(nb_faces),&tmp);
    if(error==EOF) {
      printf("Unable to read %s\n",filename);
    }

    vertices = (float *)malloc(3*nb_vertices*sizeof(float));
    normals  = (float *)malloc(3*nb_vertices*sizeof(float));
    tangents = (float *)malloc(3*nb_vertices*sizeof(float));
    colors   = (float *)malloc(3*nb_vertices*sizeof(float));
    coords   = (float *)malloc(2*nb_vertices*sizeof(float));
    faces    = (unsigned int *)malloc(3*nb_faces*sizeof(unsigned int));

    // reading vertices
    j = 0;
    for(i=0;i<nb_vertices;++i) {
      error = fscanf(file,"%f %f %f\n",&(vertices[j]),&(vertices[j+1]),&(vertices[j+2]));
      if(error==EOF) {
        printf("Unable to read vertices of %s\n",filename);
        // MeshLoader_delete(MeshLoader);
        // return NULL;
      }

      j += 3;
    }

    // reading faces
    j = 0;
    for(i=0;i<nb_faces;++i) {
      error = fscanf(file,"%d %d %d %d\n",&tmp,&(faces[j]),&(faces[j+1]),&(faces[j+2]));
      if(error==EOF) {
        printf("Unable to read faces of %s\n",filename);
        // MeshLoader_delete(MeshLoader);
        // return NULL;
      }

      if(tmp!=3) {
        printf("Error : face %d is not a triangle (%d polygonal face!)\n",i/3,tmp);
        // MeshLoader_delete(MeshLoader);
        // return NULL;
      }
      j += 3;
    }

    fclose(file);

    computeCenter();

    // computing radius
    computeRadius();

    computeNormals();

    // computing colors as normals
    for(i=0;i<3*nb_vertices;++i) {
      colors[i] = (normals[i]+1.0)/2.0;
    }

    computeUVCoord();

    computeTangents();
}

void MeshLoader::createUI(){
    ImGui::PushItemWidth(-1);

    ImGui::Text("Mesh Loader");
    ImGui::InputText("fileMeshLoader", currentFilename, IM_ARRAYSIZE(currentFilename));
    ImGui::Text("Number vertices: %d", getNBVertices());
    ImGui::Text("Number faces: %d", getNBFaces());

    ImGui::PopItemWidth();
}

void MeshLoader::cleanup(){
    if(normals!=NULL)
      free(normals);

    if(tangents!=NULL)
      free(tangents);

    if(colors!=NULL)
      free(colors);

    if(vertices!=NULL)
      free(vertices);

    if(faces!=NULL)
      free(faces);

    if(coords!=NULL)
      free(coords);
}

MeshLoader::~MeshLoader() {
    cleanup();
}
