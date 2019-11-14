#include "meshGrid.h"

#include <imgui.h>

#include <stdio.h>
#include <iostream>

using namespace glm;

MeshGrid::MeshGrid(unsigned int size, float w, float y){
	assert(size >= 1);
	nbPointPerRowColumn = size;

	width = w;
	gridY = y;

	nb_vertices = 0;
	nb_faces = 0;


    createMesh(nbPointPerRowColumn, width, gridY);
}


MeshGrid::~MeshGrid(){
	cleanup();
}

void MeshGrid::recreate(){
	cleanup();
	createMesh(nbPointPerRowColumn, width, gridY);
}



void MeshGrid::createMesh(int size, float w, float y){
	assert(size >= 1);

	const float startingWidth = -(width/2.0f);
	const float offset = width/(size-1);

	nb_vertices = size*size;
	nb_faces = (size-1)*(size-1)*2;


	vertices.resize(nb_vertices);
    normals.resize(nb_vertices);
    tangents.resize(nb_vertices);
    colors.resize(nb_vertices);
    coords.resize(nb_vertices);
    faces.resize(3*nb_faces);


    // points creation
    for(unsigned int i=0; i<size; i++){
    	for(unsigned int j=0; j<size; j++){
    		int arrayPos = i*size + j;
    		vec3 pos = vec3(startingWidth + i*offset, y, startingWidth + j*offset);
    		vec2 uv = vec2((float)i/(float)size, (float)j/(float)size);
    		addVertex(arrayPos, pos, defaultNormal, defaultTangent, defaultColor, uv);
    	}
    }

    // creation faces

	unsigned int p1,p2,p3,p4;
	unsigned int numFace;


	numFace = 0;

	for(unsigned int i=0; i<size-1; i++){
    	for(unsigned int j=0; j<size-1; j++){
			p1 = i*size + j;
			p2 = i*size + j+1;
			p3 = (i+1)*size + j+1;
			p4 = (i+1)*size + j;

			faces[numFace] = p1;
			faces[numFace+1] = p2;
			faces[numFace+2] = p4;

			faces[numFace+3] = p4;
			faces[numFace+4] = p2;
			faces[numFace+5] = p3;

			numFace += 6;
		}
    }


	center = vec3(0,y,0);

	radius = width/2;

}


void MeshGrid::addVertex(unsigned int arrayPos, vec3 pos, vec3 n, vec3 tangent, vec3 col, vec2 uv){
	// position
	vertices[arrayPos] = pos;
	// normal
	normals[arrayPos] = n;
	// tangent
	tangents[arrayPos] = tangent;
	// color
	colors[arrayPos] = col;
	// uv coordinates
	coords[arrayPos] = uv;
}


void MeshGrid::cleanup(){

}


void MeshGrid::createUI(){
	ImGui::TextColored(ImVec4(1.0f,1.0f,0.0f,1.0f), "Mesh Grid");

	// nbPointPerRowColumn, width, gridY
	ImGui::Text("Size :"); ImGui::SameLine();
	ImGui::InputInt("size", &nbPointPerRowColumn, 1, 10);
	ImGui::Text("Width :"); ImGui::SameLine();
	ImGui::InputFloat("width", &width, 0.01f, 1.0f, "%.3f");
	ImGui::Text("Z plane :"); ImGui::SameLine();
	ImGui::InputFloat("gridY", &gridY, 0.01f, 1.0f, "%.3f");

	this->Mesh::createUI();
}
