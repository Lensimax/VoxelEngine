#include <imgui.h>

#include "mesh.h"

#include <math.h>

#include <iostream>

#ifndef M_PI
#define M_PI 3.1415926
#endif




// calcul le 1-voisinage des sommets
void Mesh::collect_one_ring (std::vector<std::vector<unsigned int> > & one_ring, std::vector<std::vector<unsigned int> > triangles, unsigned int nbVertices) {
    one_ring = std::vector<std::vector<unsigned int>>(nbVertices);

    for(unsigned int i=0; i<triangles.size(); i++){ // pour chaque triangle

        for(unsigned int j=0; j<triangles[i].size(); j++){ // pour chaque sommet dans le triangle

            unsigned int currentV = triangles[i][j];
            one_ring[currentV].push_back(i);
        }
    }

}

bool Mesh::alreadyExist(unsigned int num, std::vector<unsigned int> vec){
    for(unsigned int i=0; i<vec.size(); i++){
        if(vec[i] == num){
            return true;
        }
    }
    return false;
}


void Mesh::compute_vertex_valences (std::vector<int> & valences, std::vector<std::vector<unsigned int>> one_ring, std::vector<std::vector<unsigned int> > triangles) {
    valences = std::vector<int>(one_ring.size());

    std::vector<unsigned int> vecVertex;

    for(unsigned int i=0; i<one_ring.size(); i++){ // pour chaque sommet

        unsigned int current = i;

        vecVertex = std::vector<unsigned int>();
        valences[i] = 0;

        for(unsigned int j=0; j<one_ring[i].size(); j++){ // pour chaque triangle adjacent
            for(unsigned int k=0; k<triangles[one_ring[i][j]].size(); k++){
                unsigned int vert = triangles[one_ring[i][j]][k];
                if(vert != current && !alreadyExist(vert, vecVertex)){
                    vecVertex.push_back(vert);
                    valences[i]++;
                }
            }
        }
    }

}

int Mesh::maxValue(std::vector<int> vec){
    int max = 0;

    for(unsigned int i=0; i<vec.size(); i++){
        if(max < vec[i]){
            max = vec[i];
        }
    }
    return max;
}


std::vector<unsigned int> Mesh::get_face(unsigned int i) {
    std::vector<unsigned int> face = std::vector<unsigned int>(3);
    face[0] = faces[i*3]; face[1] = faces[i*3 +1]; face[2] = faces[i*3+2];
    return face;
}

glm::vec3 Mesh::get_vertex(unsigned int i) {
  return vertices[i];
}

glm::vec3 Mesh::get_normal(unsigned int i) {
  return normals[i];
}

glm::vec3 Mesh::get_tangent(unsigned int i) {
  return tangents[i];
}

glm::vec2 Mesh::get_coord(unsigned int i) {
  return coords[i];
}

glm::vec3 Mesh::get_color(unsigned int i) {
  return colors[i];
}

void *Mesh::getVertices(){
    return &(vertices[0]);
}

void *Mesh::getFaces(){
    return &(faces[0]);
}

void *Mesh::getNormals(){
    return &(normals[0]);
}

unsigned int Mesh::getNBVertices(){
    return vertices.size();
}

unsigned int Mesh::getNBFaces(){
    return faces.size()/3;
}


void Mesh::createUI(){
    ImGui::Text("Number vertices: %d", getNBVertices());
    ImGui::Text("Number faces: %d", getNBFaces());
    ImGui::Text("Smooth Normal "); ImGui::SameLine();
    ImGui::Checkbox("smoothNormal",&smoothNormals);


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
}


glm::vec3 Mesh::getCenter(){
    return center;
}


///////////////////// COMPUTE NORMAL !!!! /////////////////////

void Mesh::computeNormals(){
    if(smoothNormals){
        computeSmoothNormals();
    } else {
        computeNormalsWithAngles();
    }
}


void Mesh::computeSmoothNormals(){
    std::vector<std::vector<unsigned int>> one_ring;
    std::vector<glm::vec3> triangle_normals;
    std::vector<int> valences;

    std::vector<std::vector<unsigned int>> triangles;
    triangles.resize(getNBFaces());
    for(unsigned int i=0; i<triangles.size(); i++){
        triangles[i] = get_face(i);
    }

    compute_triangle_normals(triangle_normals, triangles, vertices);
    collect_one_ring(one_ring,triangles, vertices.size());
    compute_vertex_valences (valences, one_ring, triangles);

    normals.resize(vertices.size());

    unsigned int i0, i1, i2;
    glm::vec3 p0,p1,p2;

    for(unsigned int i=0; i<normals.size(); i++){ // pour chaque sommet
        glm::vec3 n = glm::vec3(0.);
        float sumalpha = 0;
        for(unsigned int j=0; j<one_ring[i].size(); j++){ // pour chaque triangle dans le voisinage

            // calcul angle
            i0 = triangles[one_ring[i][j]][0]; i1 = triangles[one_ring[i][j]][1]; i2 = triangles[one_ring[i][j]][2];
            p0 = vertices[i0]; p1 = vertices[i1]; p2 = vertices[i2];

            if(i == i1){
                p1 = vertices[i0];
                p0 = vertices[i1];
            } else if(i == i2) {
                p2 = vertices[i0];
                p0 = vertices[i2];
            }

            float alpha = glm::acos(glm::dot(p1-p0, p2-p0)/(glm::length(p1-p0)*glm::length(p2-p0)));

            n += alpha*triangle_normals[one_ring[i][j]];
            sumalpha += alpha;
        }


        n /= sumalpha;
        n /= one_ring[i].size();
        normals[i] = glm::normalize(n);

    }


}

// a partir d'un triangle calcul la normales du triangle puis la renvoie sous forme de vec3
glm::vec3 Mesh::computeNormalOfOneTriangle(std::vector<unsigned int> triangle, std::vector<glm::vec3> indexed_vertices){

    unsigned int i0,i1,i2;
    glm::vec3 p0, p1, p2;

    i0 = triangle[0]; i1 = triangle[1]; i2=triangle[2];

    p0 = indexed_vertices[i0]; p1 = indexed_vertices[i1]; p2 = indexed_vertices[i2];

    glm::vec3 normal = glm::cross(p1-p0, p2-p0)/glm::length(glm::cross(p1-p0, p2-p0));

    return normal;
}

void Mesh::compute_triangle_normals (std::vector<glm::vec3> & triangle_normals, std::vector<std::vector<unsigned int> > triangles, std::vector<glm::vec3> indexed_vertices){

    triangle_normals = std::vector<glm::vec3>(triangles.size());

    for(unsigned int i=0; i<triangles.size(); i++){
        glm::vec3 n = computeNormalOfOneTriangle(triangles[i], indexed_vertices);
        triangle_normals[i] = n;
    }

}





void Mesh::computeNormalsWithAngles(){
    std::vector<glm::vec3> nf;

    normals.resize(nb_vertices);

    glm::vec3 v1, v2, v3;
    glm::vec3 v12;
    glm::vec3 v13;
    std::vector<unsigned int> f;

    std::vector<float> nv;

    // computing normals per faces
    nf.resize(3*nb_faces);
    for(unsigned int i=0;i<nb_faces;i++) {
        f = get_face(i);

        // the three vertices of the current face
        v1 = get_vertex(f[0]);
        v2 = get_vertex(f[1]);
        v3 = get_vertex(f[2]);

        // the two vectors of the current face
        v12 = v2-v1;
        v13 = v3-v1;

        // cross product
        nf[3*i] = glm::cross(v12, v13);
        nf[3*i] = glm::normalize(nf[3*i]);
    }

    // computing normals per vertex
    nv.resize(nb_vertices);
    for(unsigned int i=0;i<nb_vertices;i++) {
        // initialization
        normals[i] = glm::vec3(0);
        nv[i] = 0.0;
    }

    for(unsigned int i=0;i<nb_faces;i++) {
        // face normals average
        f = get_face(i);
        //n = &(nf[3*i]);

        normals[f[0]] += nf[3*i];
        normals[f[1]] += nf[3*i];
        normals[f[2]] += nf[3*i];
        nv[f[0]] ++;
        nv[f[1]] ++;
        nv[f[2]] ++;

    }

    for(unsigned int i=0;i<nb_vertices;i++) {
        // normalization
        if(nv[i] != 0.0){
            normals[i] /= -nv[i];
        }
        normals[i] = glm::normalize(normals[i]);
    }


}



////////////////// COMPUTE TEXTURE COORDINATE ///////////////

void Mesh::computeUVCoord(){
    // computing spherical uv coordinates

    coords.resize(nb_vertices);

    glm::vec3 v1;
    glm::vec3 c;
    float r;


    for(unsigned int i=0;i<nb_vertices;i++) {
      v1 = get_vertex(i);

      // direction between center and current point
      c = v1-center;

      // normalization
      c = glm::normalize(c);

      glm::vec2 coord;
      // elevation & azimuth remapped between 0 and 1
      r = c.z/sqrt(c.x*c.x+c.z*c.z);
      if(r>=1.0f) r = 1.0f;
      if(r<=-1.0f) r = -1.0f;
      coord.x = asin(r);
      if(c.x<0.0) coord.x = M_PI-coord.x;
      coord.x = (coord.x+(M_PI/2.0))/(2.0*M_PI);
      coord.y = acos(c.y)/M_PI;
      coords[i] = coord;
    }
}


////////////////// COMPUTE TANGENTS  ///////////////////////


void Mesh::computeTangents(){

    // TODO

    tangents.resize(nb_vertices);

    for(unsigned int i=0; i<nb_vertices; i++){
        tangents[i] = glm::vec3(0);
    }

}

////////////////// COMPUTE CENTER  ///////////////////////

void Mesh::computeCenter(){
    // computing center
    glm::vec3 c = glm::vec3(0);
    for(unsigned int i=0;i<nb_vertices;i++) {
        c = vertices[i];
    }
    center = c/(float)nb_vertices;

}

////////////////// COMPUTE RADIUS  ///////////////////////

void Mesh::computeRadius(){

    radius = 0.0;
    glm::vec3 c;
    float r;
    for(unsigned int i=0;i<nb_vertices;i++) {
      c = vertices[i]-center;

      r = sqrt(c.x*c.x+c.y*c.y+c.z*c.z);
      radius = r>radius ? r : radius;
    }

}

void Mesh::computeColor(){
    colors.resize(nb_vertices);

    for(unsigned int i=0; i<nb_vertices; i++){
        colors[i] = glm::vec3(1,0,0);
    }
}
