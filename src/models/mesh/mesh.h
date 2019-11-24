
#ifndef MESH_H
#define MESH_H

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include <string>
#include <vector>
#include <stdio.h>


class Mesh {

public:

     virtual ~Mesh() = default;

     void *getVertices();
     void *getFaces();
     void *getNormals();
     void *getUVs();

     unsigned int getNBVertices();
     unsigned int getNBFaces();

     virtual void createUI();
     virtual void recreate() = 0;

     glm::vec3 getCenter();

     glm::vec3 getMin();
     glm::vec3 getMax();


     virtual void update();

    protected:
     std::vector<unsigned int> get_face(unsigned int i);
     glm::vec3        get_vertex(unsigned int i);
     glm::vec3        get_normal(unsigned int i);
     glm::vec3        get_tangent(unsigned int i);
     glm::vec2        get_coord(unsigned int i);
     glm::vec3        get_color(unsigned int i);

     unsigned int  nb_vertices;
     unsigned int  nb_faces;

     float maxX, maxY, maxZ;
     float minX, minY, minZ;

     // data
     std::vector<glm::vec3> vertices;
     std::vector<glm::vec3> normals;
     std::vector<glm::vec3> tangents;
     std::vector<glm::vec3> colors;
     std::vector<glm::vec2> coords;
     std::vector<unsigned int> faces;

     std::vector<glm::vec3> backupVertices;
     std::vector<unsigned int> backupFaces;

   
     glm::vec3      center;
     float          radius;

 

     void computeBoundingBox();
     void inflateBoundingBox();




};



#endif
