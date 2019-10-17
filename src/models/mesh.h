
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

     void *getVertices();
     void *getFaces();
     void *getNormals();

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

     // voisinage
     std::vector<std::vector<unsigned int>> oneRing;
     // degree de chaque sommet
     std::vector<int> valences;

     // info
     glm::vec3      center;
     float          radius;

     void computeNormals();
     void computeTangents();
     void computeCenter();
     void computeRadius();
     void computeUVCoord();
     void computeColor();

     void computeSmoothNormals();
     void computeNormalsWithAngles();

     int maxValue(std::vector<int> vec);
     void compute_vertex_valences (std::vector<int> & valences, std::vector<std::vector<unsigned int>> one_ring, std::vector<std::vector<unsigned int> > triangles);
     bool alreadyExist(unsigned int num, std::vector<unsigned int> vec);
     void collect_one_ring (std::vector<std::vector<unsigned int> > & one_ring, std::vector<std::vector<unsigned int> > triangles, unsigned int nbVertices);

     void compute_triangle_normals(std::vector<glm::vec3> & triangle_normals, std::vector<std::vector<unsigned int> > triangles, std::vector<glm::vec3> indexed_vertices);
     glm::vec3 computeNormalOfOneTriangle(std::vector<unsigned int> triangle, std::vector<glm::vec3> indexed_vertices);

     bool smoothNormals = false;

};



#endif
