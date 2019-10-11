#include "meshGrid.h"

#include <imgui.h>

#include <stdio.h>
#include <iostream>

using namespace glm;

MeshGrid::MeshGrid(unsigned int size, float w, float z){
	assert(size >= 1);
	nbPointPerRowColumn = size;

	width = w;
	gridZ = z;

	nb_vertices = 0;
	nb_faces = 0;


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



void MeshGrid::createMesh(int size, float w, float z){
	assert(size >= 1);

	const float startingWidth = -(width/2.0f);
	const float offset = width/(size-1);

	nb_vertices = size*size;
	nb_faces = (size-1)*(size-1)*2;

	printf("nb_vertices %d\n", nb_vertices);
	printf("nb_faces %d\n", nb_faces);

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
    		vec3 pos = vec3(startingWidth + i*offset, startingWidth + j*offset, gridZ);
    		vec2 uv = vec2(i/size, j/size);
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


	center = glm::vec3(0,0,gridZ);

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
    ImGui::Text("Mesh");

	// nbPointPerRowColumn, width, gridZ
	ImGui::Text("Size :"); ImGui::SameLine();
	ImGui::InputInt("size", &nbPointPerRowColumn, 1, 10);
	ImGui::Text("Width :"); ImGui::SameLine();
	ImGui::InputFloat("width", &width, 0.01f, 1.0f, "%.3f");
	ImGui::Text("Z plane :"); ImGui::SameLine();
	ImGui::InputFloat("gridZ", &gridZ, 0.01f, 1.0f, "%.3f");

    ImGui::Text("Number vertices: %d", getNBVertices());
    ImGui::Text("Number faces: %d", getNBFaces());

	if (ImGui::TreeNode("Vertices")){

		ImGui::Columns(3, "Vertices"); // 4-ways, with border
		ImGui::Separator();
        ImGui::Text("X"); ImGui::NextColumn();
        ImGui::Text("Y"); ImGui::NextColumn();
        ImGui::Text("Z"); ImGui::NextColumn();
		ImGui::Separator();
		for(unsigned int i=0; i<nb_vertices; i++){
			ImGui::Text("%4f",vertices[i].x); ImGui::NextColumn();
            ImGui::Text("%4f",vertices[i].y); ImGui::NextColumn();
            ImGui::Text("%4f", vertices[i].z); ImGui::NextColumn();
		}

		ImGui::Columns(1);
		ImGui::Separator();
        ImGui::TreePop();

	}

	if (ImGui::TreeNode("Faces")){

		ImGui::Columns(3, "Face"); // 4-ways, with border
		ImGui::Separator();
        ImGui::Text("V1"); ImGui::NextColumn();
        ImGui::Text("V2"); ImGui::NextColumn();
        ImGui::Text("V3"); ImGui::NextColumn();
		ImGui::Separator();
		for(unsigned int i=0; i<nb_faces; i++){
			ImGui::Text("%d",faces[3*i]); ImGui::NextColumn();
            ImGui::Text("%d",faces[3*i+1]); ImGui::NextColumn();
            ImGui::Text("%d", faces[3*i+2]); ImGui::NextColumn();
		}

		ImGui::Columns(1);
		ImGui::Separator();
        ImGui::TreePop();

	}

    ImGui::Text("Smooth Normal "); ImGui::SameLine();
    ImGui::Checkbox("smoothNormal",&smoothNormals);
}
