#include "meshCube.h"

#include <imgui.h>

MeshCube::MeshCube(float w = 1.0f){
    width = w;

    // createMesh(width);

    createMesh(width);
    createVAO();

}


MeshCube::~MeshCube(){
    deleteVAO();
}


void MeshCube::recreate(){
    createMesh(width);
    createVAO();
}

void MeshCube::createUI(){
    Mesh::createUI();

    ImGui::Text("Width : ");
    ImGui::DragFloat("##width", &width, 0.01f);  
}


void MeshCube::createMesh(float w){


    createPositions(w);
    createNormals();
    createTangents();
    createUVs();
    
    // createInfo();

    backupVertices = vertices;

}

////// FACES
/// 1 FRONT
/// 2 BACK
/// 3 LEFT
/// 4 RIGHT
/// 5 TOP
/// 6 BOTTOM

void MeshCube::createPositions(float w){

    const unsigned int nb_vertices = 36;

    vertices.resize(nb_vertices);

    // FRONT
    vertices[0] = glm::vec3(-1.0f, 1.0f, 1.0f);
    vertices[1] = glm::vec3(-1.0f,-1.0f, 1.0f);
    vertices[2] = glm::vec3(1.0f,-1.0f, 1.0f);
    
    vertices[3] = glm::vec3(1.0f, 1.0f, 1.0f);
    vertices[4] = glm::vec3(-1.0f, 1.0f, 1.0f);
    vertices[5] = glm::vec3(1.0f,-1.0f, 1.0);

    // BACK
    vertices[6] = glm::vec3(1.0f, 1.0f,-1.0f);
    vertices[7] = glm::vec3(-1.0f,-1.0f,-1.0f);
    vertices[8] = glm::vec3(-1.0f, 1.0f,-1.0f);

    vertices[9] = glm::vec3(1.0f, 1.0f,-1.0f);
    vertices[10] = glm::vec3(1.0f,-1.0f,-1.0f);
    vertices[11] = glm::vec3(-1.0f,-1.0f,-1.0f);

    // LEFT
    vertices[12] = glm::vec3(-1.0f,-1.0f,-1.0f);
    vertices[13] = glm::vec3(-1.0f, 1.0f, 1.0f);
    vertices[14] = glm::vec3(-1.0f, 1.0f,-1.0f);

    vertices[15] = glm::vec3(-1.0f,-1.0f,-1.0f);
    vertices[16] = glm::vec3(-1.0f,-1.0f, 1.0f);
    vertices[17] = glm::vec3(-1.0f, 1.0f, 1.0f);
    
    // RIGHT
    vertices[18] = glm::vec3(1.0f, 1.0f, 1.0f);
    vertices[19] = glm::vec3(1.0f,-1.0f,-1.0f);
    vertices[20] = glm::vec3(1.0f, 1.0f,-1.0f);

    vertices[21] = glm::vec3(1.0f,-1.0f,-1.0f);
    vertices[22] = glm::vec3(1.0f, 1.0f, 1.0f);
    vertices[23] = glm::vec3(1.0f,-1.0f, 1.0f);

    // TOP
    vertices[24] = glm::vec3(1.0f, 1.0f, 1.0f);
    vertices[25] = glm::vec3(1.0f, 1.0f,-1.0f);
    vertices[26] = glm::vec3(-1.0f, 1.0f,-1.0f);

    vertices[27] = glm::vec3(1.0f, 1.0f, 1.0f);
    vertices[28] = glm::vec3(-1.0f, 1.0f,-1.0f);
    vertices[29] = glm::vec3(-1.0f, 1.0f, 1.0f);

    // BOTTOM
    vertices[30] = glm::vec3(1.0f,-1.0f, 1.0f);
    vertices[31] = glm::vec3(-1.0f,-1.0f,-1.0f);
    vertices[32] = glm::vec3(1.0f,-1.0f,-1.0f);

    vertices[33] = glm::vec3(1.0f,-1.0f, 1.0f);
    vertices[34] = glm::vec3(-1.0f,-1.0f, 1.0f);
    vertices[35] = glm::vec3(-1.0f,-1.0f,-1.0f);
    
    
}

void MeshCube::createNormals(){
    unsigned int i;
    glm::vec3 normal;
    normals.resize(getNBVertices());

    int index = 0;

    normal = glm::vec3(0,0,1);
    for(i=0; i<6; i++ ){
        normals[index+i] = normal;
    }
    index+=6;

    normal = glm::vec3(0,0,-1);
    for(i=0; i<6; i++ ){
        normals[index+i] = normal;
    }
    index+=6;

    normal = glm::vec3(-1,0,0);
    for(i=0; i<6; i++ ){
        normals[index+i] = normal;
    }
    index+=6;

    normal = glm::vec3(1,0,0);
    for(i=0; i<6; i++ ){
        normals[index+i] = normal;
    }
    index+=6;

    normal = glm::vec3(0,1,0);
    for(i=0; i<6; i++ ){
        normals[index+i] = normal;
    }
    index+=6;

    normal = glm::vec3(0,-1,0);
    for(i=0; i<6; i++ ){
        normals[index+i] = normal;
    }
    index+=6;
    

}

void MeshCube::createUVs(){

    glm::vec2 uv = glm::vec2(0,0);
    coords.resize(getNBVertices());

    for(unsigned int i=0; i<getNBVertices(); i++){
        coords[i] = uv;
    }
}


void MeshCube::createTangents(){
    unsigned int i;
    glm::vec3 tangent;
    tangents.resize(getNBVertices());

    int index = 0;

    tangent = glm::vec3(1,0,0);
    for(i=0; i<6; i++ ){
        tangents[index+i] = tangent;
    }
    index+=6;

    tangent = glm::vec3(-1,0,0);
    for(i=0; i<6; i++ ){
        tangents[index+i] = tangent;
    }
    index+=6;

    tangent = glm::vec3(0,0,1);
    for(i=0; i<6; i++ ){
        tangents[index+i] = tangent;
    }
    index+=6;

    tangent = glm::vec3(0,0,-1);
    for(i=0; i<6; i++ ){
        tangents[index+i] = tangent;
    }
    index+=6;

    tangent = glm::vec3(1,0,0);
    for(i=0; i<6; i++ ){
        tangents[index+i] = tangent;
    }
    index+=6;

    tangent = glm::vec3(-1,0,0);
    for(i=0; i<6; i++ ){
        tangents[index+i] = tangent;
    }
    index+=6;
    

}

void MeshCube::createColors(){

    unsigned int i;

    glm::vec3 color;

    colors.resize(getNBVertices());


        int index = 0;

    color = glm::vec3(0,1,0);
    for(i=0; i<6; i++ ){
        colors[index+i] = color;
    }
    index+=6;

    color = glm::vec3(1,1,0);
    for(i=0; i<6; i++ ){
        colors[index+i] = color;
    }
    index+=6;

    color = glm::vec3(255.f/255.f,146.f/255.f,8.f/255.f);
    for(i=0; i<6; i++ ){
        colors[index+i] = color;
    }
    index+=6;

    color = glm::vec3(1,0,0);
    for(i=0; i<6; i++ ){
        colors[index+i] = color;
    }
    index+=6;

    color = glm::vec3(1,1,1);
    for(i=0; i<6; i++ ){
        colors[index+i] = color;
    }
    index+=6;

    color = glm::vec3(0,0,1);
    for(i=0; i<6; i++ ){
        colors[index+i] = color;
    }
    index+=6;

}




