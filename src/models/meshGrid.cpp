#include "meshGrid.h"

#include <imgui.h>

#include <stdio.h>
#include <iostream>

using namespace glm;

MeshGrid::MeshGrid(unsigned int size, float w, float z){
	nbPointPerRowColumn = size;
	width = w;
	gridZ = z;

	nb_vertices = 0;
	nb_faces = 0;

	vertices = NULL;
    normals  = NULL;
    tangents = NULL;
    colors   = NULL;
    coords   = NULL;
    faces    = NULL;


    createMesh(nbPointPerRowColumn, width, gridZ);
}


MeshGrid::~MeshGrid(){
	std::cout << __LINE__ << " before cleanup" << std::endl;
	cleanup();
	std::cout << __LINE__ << " before cleanup" << std::endl;
}

void MeshGrid::recreate(){
	cleanup();
	createMesh(nbPointPerRowColumn, width, gridZ);
}



void MeshGrid::createMesh(unsigned int size, float w, float z){

	const float startingWidth = -(width/2.0f);
	const float offset = width/(size-1);

	nb_vertices = size*size;
	nb_faces = (size-1)*(size-1)*2;

	printf("nb_vertices %d\n", nb_vertices);
	printf("nb_faces %d\n", nb_faces);

	vertices = (float *)malloc(3*nb_vertices*sizeof(float));
    normals  = (float *)malloc(3*nb_vertices*sizeof(float));
    tangents = (float *)malloc(3*nb_vertices*sizeof(float));
    colors   = (float *)malloc(3*nb_vertices*sizeof(float));
    coords   = (float *)malloc(2*nb_vertices*sizeof(float));
    faces    = (unsigned int *)malloc(3*nb_faces*sizeof(unsigned int));


    // points creation
    for(unsigned int i=0; i<size; i++){
    	for(unsigned int j=0; j<size; j++){
    		int arrayPos = i*size + j;
    		vec3 pos = vec3(startingWidth + i*offset, startingWidth + j*offset, gridZ);
    		vec2 uv = vec2(i/size, j/size);
    		addVertex(arrayPos, pos, defaultNormal, defaultTangent, defaultColor, uv);
    	}
    }

    // creation faces

	unsigned int p1,p2,p3,p4;
	unsigned int numFace;

	for(unsigned int i=0; i<size-1; i++){
    	for(unsigned int j=0; j<size-1; j++){
			p1 = i*size + j;
			p2 = i*size + j+1;
			p3 = (i+1)*size + j+1;
			p4 = (i+1)*size + j;

			numFace = (i*size + j)*2*3;
			faces[numFace] = p1;
			faces[numFace+1] = p2;
			faces[numFace+2] = p4;

			faces[numFace+3] = p4;
			faces[numFace+4] = p2;
			faces[numFace+5] = p3;
    	}
    }


	center[0] = 0;
	center[1] = 0;
	center[2] = gridZ;

	radius = width/2;

}


void MeshGrid::addVertex(unsigned int arrayPos, vec3 pos, vec3 n, vec3 tangent, vec3 col, vec2 uv){
	// position
	vertices[3*arrayPos] = pos.x;
	vertices[3*arrayPos+1] = pos.y;
	vertices[3*arrayPos+2] = pos.z;
	// normal
	normals[3*arrayPos] = n.x;
	normals[3*arrayPos+1] = n.y;
	normals[3*arrayPos+2] = n.z;
	// tangent
	tangents[3*arrayPos] = tangent.x;
	tangents[3*arrayPos+1] = tangent.y;
	tangents[3*arrayPos+2] = tangent.z;
	// color
	colors[3*arrayPos] = col.x;
	colors[3*arrayPos+1] = col.y;
	colors[3*arrayPos+2] = col.z;
	// uv coordinates
	coords[2*arrayPos] = tangent.x;
	coords[2*arrayPos+1] = tangent.y;
}

void MeshGrid::createUI(){
	ImGui::PushItemWidth(-1);

    ImGui::Text("Mesh Grid");
    ImGui::Text("Number vertices: %d", getNBVertices());
    ImGui::Text("Number faces: %d", getNBFaces());


    ImGui::PopItemWidth();
}

void MeshGrid::cleanup(){
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
