#include "meshCube.h"

#include <imgui.h>

MeshCube::MeshCube(float w, bool center) : m_width(w), m_centered(center){

    setName("Mesh Cube");

    createMesh(m_width);
    createVAO();

}


MeshCube::~MeshCube(){
    deleteVAO();
}


void MeshCube::recreate(){
    createMesh(m_width);
    createVAO();
}

void MeshCube::createUI(){

    ImGui::Text("Number vertices: %d", getNBVertices());
    ImGui::Text("Number faces: %d", getNBFaces());

    ImGui::Text("Width : ");
    ImGui::DragFloat("##width", &m_width, 0.01f); 

    ImGui::Text("Centered : "); ImGui::SameLine();
    ImGui::Checkbox("##centered", &m_centered);

    ImGui::Text("min: %f, %f, %f", m_minX, m_minY, m_minZ);
    ImGui::Text("max: %f, %f, %f", m_maxX, m_maxY, m_maxZ); 

    if(ImGui::Button("Recreate")){
        recreate();
    }
}


void MeshCube::createMesh(float w){


    createPositions(w);
    createNormals();
    createm_tangents();
    createUVs();
    createColors();
    
    // createInfo();

    computeBoundingBox();
    inflateBoundingBox();

    m_backupVertices = m_vertices;

}

////// FACES
/// 1 FRONT
/// 2 BACK
/// 3 LEFT
/// 4 RIGHT
/// 5 TOP
/// 6 BOTTOM

void MeshCube::createPositions(float w){

    float min = 0;
    float max = w;

    if(m_centered){
        min = -w/2.0f;
        max = w/2.0f;
    }

    const unsigned int nb_vertices = 36;

    m_vertices.resize(nb_vertices);

    // FRONT
    m_vertices[0] = glm::vec3(min, max, max);
    m_vertices[1] = glm::vec3(min,min, max);
    m_vertices[2] = glm::vec3(max,min, max);
    
    m_vertices[3] = glm::vec3(max, max, max);
    m_vertices[4] = glm::vec3(min, max, max);
    m_vertices[5] = glm::vec3(max,min, max);

    // BACK
    m_vertices[6] = glm::vec3(max, max,min);
    m_vertices[7] = glm::vec3(min,min,min);
    m_vertices[8] = glm::vec3(min, max,min);

    m_vertices[9] = glm::vec3(max, max,min);
    m_vertices[10] = glm::vec3(max,min,min);
    m_vertices[11] = glm::vec3(min,min,min);

    // LEFT
    m_vertices[12] = glm::vec3(min,min,min);
    m_vertices[13] = glm::vec3(min, max, max);
    m_vertices[14] = glm::vec3(min, max,min);

    m_vertices[15] = glm::vec3(min,min,min);
    m_vertices[16] = glm::vec3(min,min, max);
    m_vertices[17] = glm::vec3(min, max, max);
    
    // RIGHT
    m_vertices[18] = glm::vec3(max, max, max);
    m_vertices[19] = glm::vec3(max,min,min);
    m_vertices[20] = glm::vec3(max, max,min);

    m_vertices[21] = glm::vec3(max,min,min);
    m_vertices[22] = glm::vec3(max, max, max);
    m_vertices[23] = glm::vec3(max,min, max);

    // TOP
    m_vertices[24] = glm::vec3(max, max, max);
    m_vertices[25] = glm::vec3(max, max,min);
    m_vertices[26] = glm::vec3(min, max,min);

    m_vertices[27] = glm::vec3(max, max, max);
    m_vertices[28] = glm::vec3(min, max,min);
    m_vertices[29] = glm::vec3(min, max, max);

    // BOTTOM
    m_vertices[30] = glm::vec3(max,min, max);
    m_vertices[31] = glm::vec3(min,min,min);
    m_vertices[32] = glm::vec3(max,min,min);

    m_vertices[33] = glm::vec3(max,min, max);
    m_vertices[34] = glm::vec3(min,min, max);
    m_vertices[35] = glm::vec3(min,min,min);
    
    
}

void MeshCube::createNormals(){
    unsigned int i;
    glm::vec3 normal;
    m_normals.resize(getNBVertices());

    int index = 0;

    normal = glm::vec3(0,0,1);
    for(i=0; i<6; i++ ){
        m_normals[index+i] = normal;
    }
    index+=6;

    normal = glm::vec3(0,0,-1);
    for(i=0; i<6; i++ ){
        m_normals[index+i] = normal;
    }
    index+=6;

    normal = glm::vec3(-1,0,0);
    for(i=0; i<6; i++ ){
        m_normals[index+i] = normal;
    }
    index+=6;

    normal = glm::vec3(1,0,0);
    for(i=0; i<6; i++ ){
        m_normals[index+i] = normal;
    }
    index+=6;

    normal = glm::vec3(0,1,0);
    for(i=0; i<6; i++ ){
        m_normals[index+i] = normal;
    }
    index+=6;

    normal = glm::vec3(0,-1,0);
    for(i=0; i<6; i++ ){
        m_normals[index+i] = normal;
    }
    index+=6;
    

}

void MeshCube::createUVs(){

    // TODO ajouter les vrai UV
    glm::vec2 uv = glm::vec2(0.5f,0);
    m_coords.resize(getNBVertices());

    for(unsigned int i=0; i<getNBVertices(); i++){
        m_coords[i] = uv;
    }
}


void MeshCube::createm_tangents(){
    unsigned int i;
    glm::vec3 tangent;
    m_tangents.resize(getNBVertices());

    int index = 0;

    tangent = glm::vec3(1,0,0);
    for(i=0; i<6; i++ ){
        m_tangents[index+i] = tangent;
    }
    index+=6;

    tangent = glm::vec3(-1,0,0);
    for(i=0; i<6; i++ ){
        m_tangents[index+i] = tangent;
    }
    index+=6;

    tangent = glm::vec3(0,0,1);
    for(i=0; i<6; i++ ){
        m_tangents[index+i] = tangent;
    }
    index+=6;

    tangent = glm::vec3(0,0,-1);
    for(i=0; i<6; i++ ){
        m_tangents[index+i] = tangent;
    }
    index+=6;

    tangent = glm::vec3(1,0,0);
    for(i=0; i<6; i++ ){
        m_tangents[index+i] = tangent;
    }
    index+=6;

    tangent = glm::vec3(-1,0,0);
    for(i=0; i<6; i++ ){
        m_tangents[index+i] = tangent;
    }
    index+=6;
    

}

void MeshCube::createColors(){

    unsigned int i;

    glm::vec3 color;

    m_colors.resize(getNBVertices());


        int index = 0;

    color = glm::vec3(0,1,0);
    for(i=0; i<6; i++ ){
        m_colors[index+i] = color;
    }
    index+=6;

    color = glm::vec3(1,1,0);
    for(i=0; i<6; i++ ){
        m_colors[index+i] = color;
    }
    index+=6;

    color = glm::vec3(255.f/255.f,146.f/255.f,8.f/255.f);
    for(i=0; i<6; i++ ){
        m_colors[index+i] = color;
    }
    index+=6;

    color = glm::vec3(1,0,0);
    for(i=0; i<6; i++ ){
        m_colors[index+i] = color;
    }
    index+=6;

    color = glm::vec3(1,1,1);
    for(i=0; i<6; i++ ){
        m_colors[index+i] = color;
    }
    index+=6;

    color = glm::vec3(0,0,1);
    for(i=0; i<6; i++ ){
        m_colors[index+i] = color;
    }
    index+=6;

}




