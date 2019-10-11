#include <imgui.h>

#include "mesh.h"

#include <math.h>

#include <iostream>

#define M_PI 3.1415926

// a partir d'un triangle calcul la normales du triangle puis la renvoie sous forme de vec3
glm::vec3 computeNormalOfOneTriangle(vector<unsigned short> triangle, vector<glm::vec3> indexed_vertices){

    unsigned short i0,i1,i2;
    glm::vec3 p0, p1, p2;

    i0 = triangle[0]; i1 = triangle[1]; i2=triangle[2];

    p0 = indexed_vertices[i0]; p1 = indexed_vertices[i1]; p2 = indexed_vertices[i2];

    glm::vec3 normal = glm::cross(p1-p0, p2-p0)/glm::length(glm::cross(p1-p0, p2-p0));

    return normal;
}

void compute_triangle_normals (std::vector<glm::vec3> & triangle_normals, vector<vector<unsigned short> > triangles, vector<glm::vec3> indexed_vertices){

    triangle_normals = std::vector<glm::vec3>(triangles.size());

    for(unsigned int i=0; i<triangles.size(); i++){
        glm::vec3 n = computeNormalOfOneTriangle(triangles[i], indexed_vertices);
        triangle_normals[i] = n;
    }

}



// calcul le 1-voisinage des sommets
void collect_one_ring (std::vector<std::vector<unsigned short> > & one_ring, vector<vector<unsigned short> > triangles, unsigned int nbVertices) {
    one_ring = vector<vector<unsigned short>>(nbVertices);

    for(unsigned int i=0; i<triangles.size(); i++){ // pour chaque triangle

        for(unsigned int j=0; j<triangles[i].size(); j++){ // pour chaque sommet dans le triangle

            unsigned short currentV = triangles[i][j];
            one_ring[currentV].push_back(i);
        }
    }

}

bool alreadyExist(unsigned short num, vector<unsigned short> vec){
    for(unsigned int i=0; i<vec.size(); i++){
        if(vec[i] == num){
            return true;
        }
    }
    return false;
}


void compute_vertex_valences (vector<int> & valences, vector<vector<unsigned short>> one_ring, vector<vector<unsigned short> > triangles) {
    valences = vector<int>(one_ring.size());

    vector<unsigned short> vecVertex;

    for(unsigned int i=0; i<one_ring.size(); i++){ // pour chaque sommet

        unsigned short current = i;

        vecVertex = vector<unsigned short>();
        valences[i] = 0;

        for(unsigned int j=0; j<one_ring[i].size(); j++){ // pour chaque triangle adjacent
            for(unsigned int k=0; k<triangles[one_ring[i][j]].size(); k++){
                unsigned short vert = triangles[one_ring[i][j]][k];
                if(vert != current && !alreadyExist(vert, vecVertex)){
                    vecVertex.push_back(vert);
                    valences[i]++;
                }
            }
        }
    }

}

int maxValue(vector<int> vec){
    int max = 0;

    for(unsigned int i=0; i<vec.size(); i++){
        if(max < vec[i]){
            max = vec[i];
        }
    }
    return max;
}


std::vector<unsigned int> Mesh::get_face(unsigned int i) {
    std::vector<unsigned int> face = std::vector<unsigned int>();
    face[0] = faces[3*i];
    face[1] = faces[3*i +1];
    face[2] = faces[3*i +2];
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

float *Mesh::getVertices(){
    return &(vertices[0]);
}

unsigned int *Mesh::getFaces(){
    return &(faces[0]);
}

float *Mesh::getNormals(){
    return &(normals[0]);
}

unsigned int Mesh::getNBVertices(){
    return vertices.size();
}

unsigned int Mesh::getNBFaces(){
    return faces.size()/3;
}


void Mesh::createUI(){
    ImGui::Text("Mesh");
    ImGui::Text("Number vertices: %d", getNBVertices());
    ImGui::Text("Number faces: %d", getNBFaces());
}


glm::vec3 Mesh::getCenter(){
    return center;
}


void compute_smooth_vertex_normals (){
    float w = 1.0; // default: uniform weights

    vector<vector<unsigned short>> one_ring;
    vector<glm::vec3> triangle_normals;
    vector<int> valences;

    compute_triangle_normals(triangle_normals, triangles, indexed_vertices);
    collect_one_ring(one_ring,triangles, indexed_vertices.size());
    compute_vertex_valences (valences, one_ring, triangles);

    vertex_normals = vector<glm::vec3>(indexed_vertices.size());

    if (weight_type == 1) { // area weight

        for(unsigned int i=0; i<vertex_normals.size(); i++){ // pour chaque sommet
            glm::vec3 n = glm::vec3(0.);
            for(unsigned int j=0; j<one_ring[i].size(); j++){ // pour chaque triangle dans le voisinage
                n += triangle_normals[one_ring[i][j]];
            }
            n /= one_ring[i].size();
            vertex_normals[i] = n;
        }

    } else if (weight_type == 2) { // angle weight




    }

    // return valences;
}


void Mesh::computeNormals(){

    vector<vector<unsigned short>> one_ring;
    vector<glm::vec3> triangle_normals;
    vector<int> valences;

    compute_triangle_normals(triangle_normals, faces, vertices);
    collect_one_ring(one_ring,faces, vertices.size());
    compute_vertex_valences (valences, one_ring, faces);

    normals.resize(vertices.size());

    unsigned short i0, i1, i2;
    glm::vec3 p0,p1,p2;

    for(unsigned int i=0; i<normals.size(); i++){ // pour chaque sommet
        glm::vec3 n = glm::vec3(0.);
        float sumalpha = 0;
        for(unsigned int j=0; j<one_ring[i].size(); j++){ // pour chaque triangle dans le voisinage

            // calcul angle
            i0 = faces[one_ring[i][j]][0]; i1 = faces[one_ring[i][j]][1]; i2 = faces[one_ring[i][j]][2];
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
        normals[i] = n;

    }


}

void Mesh::computeUVCoord(){
    // computing spherical uv coordinates

    glm::vec3 v1;
    glm::vec3 c;
    float norm, r;


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

void Mesh::computeTangents(){

    // TODO

    tangents.resize(nb_vertices);

    for(unsigned int i=0; i<nb_vertices; i++){
        tangents[i] = glm::vec3(0);
    }

}

void Mesh::computeCenter(){
    // computing center
    glm::vec3 c = glm::vec3(0);
    for(unsigned int i=0;i<nb_vertices;i++) {
        c = vertices[i];
    }
    center = c/(float)nb_vertices;

}

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
