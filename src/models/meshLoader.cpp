#include "meshLoader.h"

#include <imgui.h>

#include <iostream>

#include <math.h>


MeshLoader::MeshLoader(char *filename) {

    sprintf(currentFilename, "%s", filename);
    createMesh(currentFilename);
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


    error = fscanf(file,"OFF\n%d %d %d\n",&(nb_vertices),&(nb_faces),&tmp);
    if(error==EOF) {
      printf("Unable to read %s\n",filename);
    }


    vertices.resize(nb_vertices);
    faces.resize(nb_faces*3);

    glm::vec3 vertex = glm::vec3(0);

    // reading vertices
    for(i=0;i<nb_vertices;i++) {

        error = fscanf(file,"%f %f %f\n",&(vertex.x),&(vertex.y),&(vertex.z));
        if(error==EOF) {
            printf("Unable to read vertices of %s\n",filename);
        // MeshLoader_delete(MeshLoader);
        // return NULL;
        }
        vertices[i] = vertex;
    }


    // reading faces
    j = 0;
    for(i=0;i<nb_faces;i++) {
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
    colors.resize(nb_vertices);
    for(i=0;i<nb_vertices;i++) {
      colors[i] = (normals[i]+1.0f)/2.0f;
    }

    computeUVCoord();


    computeTangents();


}

void MeshLoader::createUI(){
    ImGui::PushItemWidth(-1);

    ImGui::Text("Mesh Loader");
    ImGui::InputText("fileMeshLoader", currentFilename, IM_ARRAYSIZE(currentFilename));
    this->Mesh::createUI();

    ImGui::PopItemWidth();
}

void MeshLoader::cleanup(){

}

MeshLoader::~MeshLoader() {
    cleanup();
}
