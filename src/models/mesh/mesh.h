
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


      // DEBUG
      void drawDebug(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat);
      void drawGridForSimplification(glm::vec3 minimum, glm::vec3 maximum, glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat);


     void simplify();

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

     // voisinage
     std::vector<std::vector<unsigned int>> oneRing;
     // degree de chaque sommet
     std::vector<int> valences;

     std::vector<glm::vec3> curvature;
     std::vector<float> trianglesQuality;

     // info
     glm::vec3      center;
     float          radius;

     void initialize();

     void computeTangents();
     void computeCenter();
     void computeRadius();
     void computeUVCoord();
     void computeColor();
     void computeBoundingBox();
     void inflateBoundingBox();

     void computeAllInfo();



     /// COMPUTE VALENCE + ONE RING

     int maxValue(std::vector<int> vec);
     void compute_vertex_valences (std::vector<int> & valences, std::vector<std::vector<unsigned int>> one_ring, std::vector<std::vector<unsigned int> > triangles);
     bool alreadyExist(unsigned int num, std::vector<unsigned int> vec);
     void collect_one_ring (std::vector<std::vector<unsigned int> > & one_ring, std::vector<std::vector<unsigned int> > triangles, unsigned int nbVertices);

     ///// COMPUTE NORMALES

     void computeNormals();
     void computeSmoothNormals();
     void computeNormalsWithAngles();
     void compute_triangle_normals(std::vector<glm::vec3> & triangle_normals, std::vector<std::vector<unsigned int> > triangles, std::vector<glm::vec3> indexed_vertices);
     glm::vec3 computeNormalOfOneTriangle(std::vector<unsigned int> triangle, std::vector<glm::vec3> indexed_vertices);


     const char uniformSmoothingString[1024] = "Uniform";
     const char laplaceSmoothingString[1024] = "Bel Trami";


     char type_smoothing[1024] = "Uniform";
    bool smoothNormals = false;



     /////// SMOOTHING VERTICES ///////

     int nbSmoothingIteration = 0;


     std::vector<glm::vec3> smoothing(const std::vector<glm::vec3> & meshvertices, const std::vector<std::vector<unsigned int> > & triangles,
        std::vector<std::vector<unsigned int> > one_ring, unsigned int iterations, char type_smooth[],
        std::vector<glm::vec3> & meshcurvature,std::vector<float> & qualityVertex);

     std::vector<glm::vec3> calc_mean_curvature (const std::vector<glm::vec3> & vertices, const std::vector<std::vector<unsigned int>> & triangles, std::vector<std::vector<unsigned int>> one_ring);
     float calc_weights(const std::vector<glm::vec3> & vertices, std::vector<std::vector<unsigned int> > one_ring, unsigned int v, unsigned int vi);

     std::vector<float> calc_quality_mesh(const std::vector<glm::vec3> & vertices, const std::vector<std::vector<unsigned int> > & triangles);
     float calc_triangle_quality(const std::vector<glm::vec3> & vertices, std::vector<unsigned int> triangles);
     float max3v(float a, float b, float c);
     float cot(float theta);


     /// SIMPLIFICATION /////
     int resolution = 1;

     // renvoie dans quelle cellule le sommet se trouve
     std::vector<int> indexOffCell(glm::vec3 start, glm::vec3 offset, glm::vec3 vertex);
     void computeAllInfoWithoutNormals();
     void drawQuadWithTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 v4);
};



#endif
