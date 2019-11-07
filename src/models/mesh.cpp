#include <imgui.h>

#include "mesh.h"
#include "../material/shader.h"

#include <math.h>

#include <iostream>
#include <unordered_map>

#ifndef M_PI
#define M_PI 3.1415926
#endif

void Mesh::initialize(){
    smoothNormals = false;
    nbSmoothingIteration = 0;
    sprintf(type_smoothing, "%s",uniformSmoothingString);
    maxX = 0; maxY = 0; maxZ = 0;
    minX = 0; minY = 0; minZ = 0;
    resolution = 1;
}


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

void Mesh::computeAllInfo(){

    // pas opti !!!!
    std::vector<std::vector<unsigned int>> triangles;
    triangles.resize(faces.size()/3);
    for(unsigned int i=0; i<triangles.size(); i++){
        triangles[i].resize(3);
        for(unsigned int j=0; j<3; j++){
            triangles[i][j] = faces[3*i +j];
        }
    }

    collect_one_ring (oneRing, triangles, nb_vertices);
    compute_vertex_valences(valences, oneRing, triangles);

    computeCenter();
    computeRadius();

    computeBoundingBox();
    inflateBoundingBox();


    // vertices = smoothing(vertices, triangles,oneRing, nbSmoothingIteration, type_smoothing, curvature,trianglesQuality);

    computeNormals();

    // computing colors as normals
    colors.resize(nb_vertices);
    for(unsigned int i=0;i<nb_vertices;i++) {
        colors[i] = (normals[i]+1.0f)/2.0f;
    }

    computeUVCoord();


    computeTangents();



}

void Mesh::computeAllInfoWithoutNormals(){

        // pas opti !!!!
        std::vector<std::vector<unsigned int>> triangles;
        triangles.resize(faces.size()/3);
        for(unsigned int i=0; i<triangles.size(); i++){
            triangles[i].resize(3);
            for(unsigned int j=0; j<3; j++){
                triangles[i][j] = faces[3*i +j];
            }
        }

        collect_one_ring (oneRing, triangles, nb_vertices);
        compute_vertex_valences(valences, oneRing, triangles);

        computeCenter();
        computeRadius();

        computeBoundingBox();
        inflateBoundingBox();

        // vertices = smoothing(vertices, triangles,oneRing, nbSmoothingIteration, type_smoothing, curvature,trianglesQuality);

        // computing colors as normals
        colors.resize(nb_vertices);
        for(unsigned int i=0;i<nb_vertices;i++) {
            colors[i] = (normals[i]+1.0f)/2.0f;
        }

        computeUVCoord();
        computeTangents();
}


void Mesh::createUI(){
    ImGui::Text("Number vertices: %d", getNBVertices());
    ImGui::Text("Number faces: %d", getNBFaces());
    ImGui::Text("Smooth Normal "); ImGui::SameLine();
    ImGui::Checkbox("smoothNormal",&smoothNormals);



    ////// SIMPLIFICATION DE SOMMETS ///
    ImGui::Text("vertices simplification");
    ImGui::Text("resolution : "); ImGui::SameLine();
    ImGui::InputInt("##resolution", &resolution, 1, 100);


    ImGui::Separator();
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

    ImGui::Text("Bounding Box");
    ImGui::Text("min: %f, %f, %f", minX, minY, minZ);
    ImGui::Text("max: %f, %f, %f", maxX, maxY, maxZ);


    ImGui::Text("center: %f, %f, %f", center.x, center.y,center.z);
    ImGui::Text("radius: %f", radius);

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


//////////////////// SMOOTHING VERTICES ///////////////////



// calcul de la curvature uniform pour un sommet
glm::vec3 vunicurvature(glm::vec3 vertex, std::vector<unsigned int> one_ring, const std::vector<glm::vec3> & vertices){

    glm::vec3 curvature = glm::vec3(0.0);


    for(unsigned int i=0; i<one_ring.size(); i++){
        curvature += vertices[one_ring[i]];
    }
    if(one_ring.size() != 0){
        curvature /= one_ring.size();
    }
    curvature -= vertex;



    return curvature;
}

// calcul de la curvature pour le maillage
std::vector<glm::vec3> calc_uniform_curvature(const std::vector<glm::vec3> & vertices, const std::vector<std::vector<unsigned int> > & triangles, std::vector<std::vector<unsigned int> > one_ring){



    std::vector<glm::vec3> curvature = std::vector<glm::vec3>(vertices.size());

    for(unsigned int i=0; i<vertices.size(); i++){

        curvature[i] = vunicurvature(vertices[i], one_ring[i], vertices);

    }

    return curvature;
}



//////////////////
//// QUESTION 2 //
//////////////////


// maximum de 3 valeurs
float Mesh::max3v(float a, float b, float c){
    if(a > b){
        if(a > c){
            return a;
        } else {
            return c;
        }
    } else {
        if(b > c){
            return b;
        } else {
            return c;
        }
    }
}

// cotangents calcul
float Mesh::cot(float theta){
    return cos(theta)/sin(theta);
}


// calcul de la qualité des triangles en fonction du plus petit angle
float Mesh::calc_triangle_quality(const std::vector<glm::vec3> & vertices, std::vector<unsigned int> triangles){

    assert(triangles.size() == 3);

    glm::vec3 p1 = vertices[triangles[0]];
    glm::vec3 p2 = vertices[triangles[1]];
    glm::vec3 p3 = vertices[triangles[2]];

    glm::vec3 a = p2-p1;
    glm::vec3 b = p3-p1;
    glm::vec3 c = p3-p2;

    float r = (2*length(a)*length(b)*length(c))/(4*length(cross(a,b)));


    float maxSide = max3v(length(a),length(b),length(c));

    assert(maxSide != 0.0f);
    return r/maxSide;
}


// calcul de la qualité du maillage
std::vector<float> Mesh::calc_quality_mesh(const std::vector<glm::vec3> & vertices, const std::vector<std::vector<unsigned int> > & triangles){

    std::vector<float> quality = std::vector<float>(triangles.size());

    for(unsigned int i=0; i<triangles.size(); i++){
        quality[i] = calc_triangle_quality(vertices, triangles[i]);
    }

    return quality;
}



// calcul des poids avec les cotangents
float Mesh::calc_weights(const std::vector<glm::vec3> & vertices, std::vector<std::vector<unsigned int> > one_ring, unsigned int v, unsigned int vi){

    // on récupère les deux sommets communs avec les deux sommets courants
    std::vector<unsigned int> same_vertices = std::vector<unsigned int>();

    for(unsigned int i=0; i<one_ring[v].size(); i++){
        for(unsigned int j=0; j<one_ring[vi].size(); j++){
            if(one_ring[v][i] == one_ring[vi][j]){
                same_vertices.push_back(one_ring[vi][j]);
            }
        }
    }

    // si le il n'y a pas de voisins on renvoie 1
    if(same_vertices.size() != 2){
        //fprintf(stderr, "Error mesh invalid\n");
        return 1;
    }
    assert(same_vertices.size() == 2);

    // calcul des angles
    unsigned int p0 = same_vertices[0];
    unsigned int p1 = same_vertices[1];

    float alpha = glm::dot(glm::normalize(vertices[v] - vertices[p0]), glm::normalize(vertices[vi] - vertices[p0]));
    float beta = glm::dot(glm::normalize(vertices[v] - vertices[p1]), glm::normalize(vertices[vi] - vertices[p1]));

    alpha = cos(alpha);
    beta = cos(beta);

    assert(alpha >= 0 && beta >= 0);

    float ret = 0.5f*(cot(alpha)+cot(beta));

    return ret;

}


// calcul la curvature pour tous les sommets
std::vector<glm::vec3> Mesh::calc_mean_curvature (const std::vector<glm::vec3> & vertices, const std::vector<std::vector<unsigned int> > & triangles, std::vector<std::vector<unsigned int> > one_ring) {

    std::vector<glm::vec3> curvature = std::vector<glm::vec3>(vertices.size());
    glm::vec3 tmp;
    float sum, w;

    for(unsigned int i=0; i<vertices.size(); i++) { // pour chaque sommets

        sum = 0;
        tmp = glm::vec3(0);

        // pour chacun de ses voisins
        for(unsigned int j=0; j<one_ring[i].size(); j++){
            // on calcul le poids avec les cotangents
            w = calc_weights(vertices, one_ring, i, one_ring[i][j]);
            tmp += w * (vertices[one_ring[i][j]] - vertices[i]);
            sum += w;
        }

        // on moyenne
        curvature[i] = tmp/sum;

    }
    return curvature;

}





// applique le smoothing un nombre "itération" fois
std::vector<glm::vec3> Mesh::smoothing(const std::vector<glm::vec3> & meshvertices, const std::vector<std::vector<unsigned int> > & triangles,
        std::vector<std::vector<unsigned int> > one_ring, unsigned int iterations, char type_smooth[],
        std::vector<glm::vec3> & meshcurvature,std::vector<float> & qualityVertex){

    std::vector<glm::vec3> changedVertices = meshvertices;
    std::vector<glm::vec3> curvature;


    // SMOOTHING
    for(unsigned int i=0; i<iterations; i++){ // pour chaque itération

        std::vector<glm::vec3> currentVertices = std::vector<glm::vec3>(meshvertices.size());

        // on calcule la curvature en fonction du type de smoothing
        if(strcmp(type_smooth, uniformSmoothingString) == 0){
            curvature = calc_uniform_curvature(changedVertices, triangles, one_ring);
        } else if(strcmp(type_smooth, laplaceSmoothingString) == 0){
            curvature = calc_mean_curvature(changedVertices, triangles, one_ring);
        } else {
            return meshvertices;
        }

        // on met à jour les sommets
        for(unsigned int j=0; j<changedVertices.size(); j++){
            currentVertices[j] = changedVertices[j] + 0.5f * curvature[j];
        }

        changedVertices = currentVertices;

    }

    qualityVertex.resize(meshvertices.size());
    qualityVertex = calc_quality_mesh(changedVertices, triangles);

    meshcurvature = curvature;

    return changedVertices;

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


////// COMPUTE BOUNDING BOX /////

void Mesh::computeBoundingBox(){
    assert(vertices.size() > 0);

    maxX = vertices[0].x; maxY = vertices[0].y; maxZ = vertices[0].z;
    minX = vertices[0].x; minY = vertices[0].y; minZ = vertices[0].z;

    for(unsigned int i=0; i<vertices.size(); i++){
        if(vertices[i].x > maxX){
            maxX = vertices[i].x;
        } else if(vertices[i].x < minX){
            minX = vertices[i].x;
        }
        if(vertices[i].y > maxY){
            maxY = vertices[i].y;
        } else if(vertices[i].y < minY){
            minY = vertices[i].y;
        }
        if(vertices[i].z > maxZ){
            maxZ = vertices[i].z;
        } else if(vertices[i].z < minZ){
            minZ = vertices[i].z;
        }
    }



}

void Mesh::inflateBoundingBox(){
    const float percent = 0.1f;
    maxX += percent*radius; maxY += percent*radius; maxZ += percent*radius;
    minX -= percent*radius; minY -= percent*radius; minZ -= percent*radius;
}


glm::vec3 Mesh::getMin(){
    return glm::vec3(minX, minY, minZ);
}


glm::vec3 Mesh::getMax(){
    return glm::vec3(maxX, maxY, maxZ);
}


///////// SIMPLIFICATION //////////


void Mesh::drawDebug(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat){

    glm::vec3 minGrid = getMin();
    glm::vec3 maxGrid = getMax();

    if(resolution <= 1){
        drawGridForSimplification(minGrid, maxGrid,modelMat, viewMat, projectionMat);
    } else {
        glm::vec3 offset;
        offset.x = (maxGrid.x - minGrid.x)/(float)resolution;
        offset.y = (maxGrid.y - minGrid.y)/(float)resolution;
        offset.z = ((maxGrid.z - minGrid.z)/(float)resolution);

        for(int i=0; i<resolution; i++){
            for(int j=0; j<resolution; j++){
                for(int k=0; k<resolution; k++){
                    // glm::vec3 start = glm::vec3(minGrid.)
                    glm::vec3 mi = minGrid + glm::vec3(i*offset.x, j*offset.y, k*(offset.z));
                    glm::vec3 ma = minGrid + glm::vec3((i+1)*offset.x, (j+1)*offset.y, (k+1)*(offset.z));

                    drawGridForSimplification(mi, ma, modelMat, viewMat, projectionMat);
                }
            }
        }
    }


}

void Mesh::drawQuadWithTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4){
    glVertex3f(v1.x, v1.y, v1.z);
    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v4.x, v4.y, v4.z);

    glVertex3f(v2.x, v2.y, v2.z);
    glVertex3f(v3.x, v3.y, v3.z);
    glVertex3f(v4.x, v4.y, v4.z);
}


void Mesh::drawGridForSimplification(glm::vec3 minimum, glm::vec3 maximum, glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat){
    Shader *shader = new Shader();
    shader->load("../data/shaders/displayBoundingBox.vert","../data/shaders/displayBoundingBox.frag");

    glUseProgram(shader->id());


    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader->id(),"projMat"),1,GL_FALSE,&(projectionMat[0][0]));

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    glBegin(GL_TRIANGLES);

    // front face
    drawQuadWithTriangle(glm::vec3(minimum.x,maximum.y,maximum.z), glm::vec3(maximum.x,maximum.y,maximum.z), glm::vec3(maximum.x,minimum.y,maximum.z), glm::vec3(minimum.x,minimum.y,maximum.z));
    // back face
    drawQuadWithTriangle(glm::vec3(maximum.x,maximum.y,minimum.z), glm::vec3(minimum.x,maximum.y,minimum.z), glm::vec3(minimum.x,minimum.y,minimum.z), glm::vec3(maximum.x,minimum.y,minimum.z));
    // left face
    drawQuadWithTriangle(glm::vec3(minimum.x,maximum.y,minimum.z), glm::vec3(minimum.x,minimum.y,maximum.z), glm::vec3(minimum.x,minimum.y,maximum.z), glm::vec3(minimum.x,minimum.y,minimum.z));
    // right face
    drawQuadWithTriangle(glm::vec3(maximum.x,maximum.y,maximum.z), glm::vec3(maximum.x,maximum.y,minimum.z), glm::vec3(maximum.x,minimum.y,minimum.z), glm::vec3(maximum.x,minimum.y,maximum.z));
    // bottom face
    drawQuadWithTriangle(glm::vec3(minimum.x,minimum.y,maximum.z), glm::vec3(maximum.x,minimum.y,maximum.z), glm::vec3(maximum.x,minimum.y,minimum.z), glm::vec3(minimum.x,minimum.y,minimum.z));
    // top face
    drawQuadWithTriangle(glm::vec3(minimum.x,maximum.y,minimum.z), glm::vec3(maximum.x,maximum.y,minimum.z), glm::vec3(maximum.x,maximum.y,maximum.z), glm::vec3(minimum.x,maximum.y,maximum.z));

    glEnd();

    glUseProgram(0);

    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}


// calcul le numero de la cellule en fonction de la resolution
int cellToIndex(int resolution, int i, int j, int k){
    return i + j*resolution + k*resolution*resolution;
}

std::vector<int> indexToCell(int resolution, int index){
    std::vector<int> v;
    v.resize(3);


}

// modifie "vertices" et "faces"
// simplification du maillage
void Mesh::simplify(){

    if(resolution < 1){
        return;
    }

    computeBoundingBox();
    inflateBoundingBox();

    // pour avoir les bonnes normales même après modification
    // computeNormals();

    glm::vec3 minGrid = getMin();
    glm::vec3 maxGrid = getMax();

    glm::vec3 offset;
    offset.x = (maxGrid.x - minGrid.x)/(float)resolution;
    offset.y = (maxGrid.y - minGrid.y)/(float)resolution;
    offset.z = ((maxGrid.z - minGrid.z)/(float)resolution);

    std::vector<int> cell1, cell2, cell3;

    // calcul du correspondant
    std::vector<std::vector<glm::vec3>> listOfCell;
    listOfCell.resize(resolution*resolution*resolution);

    for(unsigned int i=0; i<backupVertices.size(); i++){
        cell1 = indexOffCell(minGrid, offset, backupVertices[i]);
        int index = cellToIndex(resolution, cell1[0], cell1[1], cell1[2]);
        assert(index < resolution*resolution*resolution);
        if(listOfCell[index].empty()){
            listOfCell[index] = std::vector<glm::vec3>();
        }
        listOfCell[index].push_back(backupVertices[i]);
        listOfCell[index].push_back(normals[i]);
        listOfCell[index].push_back(glm::vec3(cell1[0], cell1[1], cell1[2]));
    }

    // debug
    /*for(unsigned int i=0; i<listOfCell.size(); i++){
        if(!listOfCell[i].empty()){
            printf("cell : %i\n", i);
            for(unsigned int j=0; j<listOfCell[i].size(); j+=3){
                printf("pos : %f, %f, %f normal : %f, %f, %f\n", listOfCell[i][j].x, listOfCell[i][j].y ,listOfCell[i][j].z, listOfCell[i][j+1].x, listOfCell[i][j+1].y, listOfCell[i][j+1].z);
            }
            printf("\n\n\n");
        }
    }*/


    // calcul moyenne
    unsigned int newIndex = 0;
    for(unsigned int i=0; i<listOfCell.size(); i++){
        if(!listOfCell[i].empty()){
            glm::vec3 pos = glm::vec3(0);
            glm::vec3 norm = glm::vec3(0);

            for(unsigned int j=0; j<listOfCell[i].size(); j+=3){
                pos += listOfCell[i][j];
                norm += listOfCell[i][j+1];
            }

            pos /= listOfCell[i].size()/3;
            norm /= listOfCell[i].size()/3;
            norm = glm::normalize(norm);
            listOfCell[i] = std::vector<glm::vec3>();
            listOfCell[i].push_back(pos);
            listOfCell[i].push_back(norm);
            listOfCell[i].push_back(glm::vec3((float)newIndex));

            newIndex++;
        }
    }


    /// SUPPRESSION DES TRIANGLES ////

    std::vector<unsigned int> newTriangles = std::vector<unsigned int>();

    unsigned int i1, i2, i3;
    for(unsigned int i=0; i<backupFaces.size(); i+=3){ // pour chaque triangles
        cell1 = indexOffCell(minGrid, offset, backupVertices[backupFaces[i]]);
        cell2 = indexOffCell(minGrid, offset, backupVertices[backupFaces[i+1]]);
        cell3 = indexOffCell(minGrid, offset, backupVertices[backupFaces[i+2]]);

        if(cell1 == cell2 || cell2 == cell3 || cell3 == cell1){
            // le triangle est supprimé
        } else {
            /// pas très propre
            assert(listOfCell[cellToIndex(resolution, cell1[0], cell1[1], cell1[2])].size() == 3);
            i1 = (unsigned int)listOfCell[cellToIndex(resolution, cell1[0], cell1[1], cell1[2])][2].x;
            assert(listOfCell[cellToIndex(resolution, cell2[0], cell2[1], cell2[2])].size() == 3);
            i2 = (unsigned int)listOfCell[cellToIndex(resolution, cell2[0], cell2[1], cell2[2])][2].x;
            assert(listOfCell[cellToIndex(resolution, cell3[0], cell3[1], cell3[2])].size() == 3);
            i3 = (unsigned int)listOfCell[cellToIndex(resolution, cell3[0], cell3[1], cell3[2])][2].x;
            newTriangles.push_back(i1);
            newTriangles.push_back(i2);
            newTriangles.push_back(i3);
        }
    }

    // creation des tableau de postion et normales des sommets
    std::vector<glm::vec3> newVertices = std::vector<glm::vec3>();
    std::vector<glm::vec3> newNormals = std::vector<glm::vec3>();

    for(unsigned int i=0; i<listOfCell.size(); i++){
        if(!listOfCell[i].empty()){
            assert(listOfCell[i].size() == 3);
            newVertices.push_back(listOfCell[i][0]);
            newNormals.push_back(listOfCell[i][1]);
        }
    }

    vertices = newVertices;
    normals = newNormals;
    faces = newTriangles;

    nb_vertices = vertices.size();
    nb_faces = faces.size()/3;

    computeAllInfoWithoutNormals();
/*
    for(unsigned int i=0; i<faces.size(); i+=3){ // pour chaque triangles
        cell1 = indexOffCell(minGrid, offset, vertices[faces[i]]);
        cell2 = indexOffCell(minGrid, offset, vertices[faces[i+1]]);
        cell3 = indexOffCell(minGrid, offset, vertices[faces[i+2]]);


    }
*/

}


// renvoie dans quelle cellule le sommet se trouve
std::vector<int> Mesh::indexOffCell(glm::vec3 start, glm::vec3 offset, glm::vec3 vertex){
    std::vector<int> indexCell;
    indexCell.resize(3);

    glm::vec3 distanceFromStart = vertex - start;

    indexCell[0] = distanceFromStart.x / offset.x;
    indexCell[1] = distanceFromStart.y / offset.y;
    indexCell[2] = distanceFromStart.z / offset.z;

    return indexCell;
}
