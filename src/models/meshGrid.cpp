#include "meshGrid.h"

#include <imgui.h>

#include <stdio.h>
#include <iostream>

using namespace glm;

MeshGrid::MeshGrid(unsigned int size, float w, float y, float amp, float freq, float pers, int octaves){
	assert(size >= 1);
	nbPointPerRowColumn = size;

	width = w;
	gridY = y;

	amplitude = amp;
	frequency = freq;
	persistence = pers;
	nboctaves = octaves;

	nb_vertices = 0;
	nb_faces = 0;


	recreate();
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


// CREATION DU BRUIT DE PERLIN

glm::vec2 MeshGrid::hash(glm::vec2 p) {
    p = glm::vec2( dot(p,glm::vec2(127.1f,311.7f)),
        glm::dot(p,glm::vec2(269.5f,183.3f)) );

    return -1.0f + 2.0f*glm::fract(glm::sin(p)*43758.5453123f);
	

}

float MeshGrid::gnoise(glm::vec2 p) {
    glm::vec2 i = glm::floor( p );
    glm::vec2 f = glm::fract( p );

    glm::vec2 u = f*f*(3.0f-2.0f*f);

	

    return glm::mix( glm::mix( glm::dot( hash( i + glm::vec2(0.0f,0.0f) ), f - glm::vec2(0.0f,0.0f) ),
           glm::dot( hash( i + glm::vec2(1.0f,0.0f) ), f - glm::vec2(1.0f,0.0f) ), u.x),
          glm::mix( glm::dot( hash( i + glm::vec2(0.0f,1.0f) ), f - glm::vec2(0.0f,1.0f) ),
           glm::dot( hash( i + glm::vec2(1.0f,1.0f) ), f - glm::vec2(1.0f,1.0f) ), u.x), u.y);
}

float MeshGrid::pnoise(glm::vec2 p,float amplitude,float frequency,float persistence, int nboctaves) {
    float a = amplitude;
    float f = frequency;
    float n = 0.0;

    for(int i=0;i<nboctaves;++i) {
	    n = n+a*gnoise(p*f);
	    f = f*2.;
	    a = a*persistence;
    }

    return n;
}

/***** CALCUL NORMAL *****/
/*
float value(in vec4 c) {
	// gradient of what:

	return c.x;// the height is stored in all channels (take the first one)
}


// calcul de la normale a partir du bruit
vec4 normalPoint(vec3 point){


	// vec2 ps = 1./vec2(textureSize(heightmap,0));
	vec2 ps = vec2(0.01);

	vec2 g = vec2(pnoise(point.xy+vec2(ps.x,0.0),amplitude,frequency,persistence,nboctaves) - pnoise(point.xy-vec2(ps.x,0.0),amplitude,frequency,persistence,nboctaves),
		pnoise(point.xy+vec2(0.0,ps.y),amplitude,frequency,persistence,nboctaves) - pnoise(point.xy+vec2(0.0,ps.y),amplitude,frequency,persistence,nboctaves))/2.;

	float scale = 100.;

	vec3 n1 = vec3(1.,0.,g.x*scale);

	vec3 n2 = vec3(0.,1.,-g.y*scale);

	vec3 n = normalize(cross(n1,n2));


	return vec4(n,point.z);
}

*/