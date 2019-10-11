
#ifndef MESH_H
#define MESH_H

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include <vector>


class Mesh {

public:

     virtual ~Mesh() = default;

     float *getVertices();
     unsigned int *getFaces();
     float *getNormals();

     unsigned int getNBVertices();
     unsigned int getNBFaces();

     virtual void createUI();
     virtual void recreate() = 0;

     glm::vec3 getCenter();


     // length


    protected:
     std::vector<unsigned int> get_face(unsigned int i);
     glm::vec3        get_vertex(unsigned int i);
     glm::vec3        get_normal(unsigned int i);
     glm::vec3        get_tangent(unsigned int i);
     glm::vec2        get_coord(unsigned int i);
     glm::vec3        get_color(unsigned int i);

     unsigned int  nb_vertices;
     unsigned int  nb_faces;

     // data
     std::vector<glm::vec3> vertices;
     std::vector<glm::vec3> normals;
     std::vector<glm::vec3> tangents;
     std::vector<glm::vec3> colors;
     std::vector<glm::vec2> coords;
     std::vector<unsigned int> faces;

     // info
     glm::vec3 center[3];
     float         radius;

     void computeNormals();
     void computeTangents();
     void computeCenter();
     void computeRadius();
     void computeUVCoord();

};



#endif
