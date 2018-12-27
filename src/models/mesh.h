
#ifndef MESH_H
#define MESH_H


class Mesh {

public:

     virtual ~Mesh() = default;

     float *getVertices();
     unsigned int *getFaces();
     float *getNormals();

     unsigned int getNBVertices();
     unsigned int getNBFaces();

     virtual void createUI();
     virtual void recreate();

     float *getCenter();


     // length


    protected:
     unsigned int *get_face(unsigned int i);
     float        *get_vertex(unsigned int i);
     float        *get_normal(unsigned int i);
     float        *get_tangent(unsigned int i);
     float        *get_coord(unsigned int i);
     float        *get_color(unsigned int i);

     unsigned int  nb_vertices;
     unsigned int  nb_faces;

     // data
     float        *vertices;
     float        *normals;
     float        *tangents;
     float        *colors;
     float        *coords;
     unsigned int *faces;

     // info
     float         center[3];
     float         radius;

     virtual void computeNormals();
     virtual void computeTangents();
     virtual void computeCenter();
     virtual void computeRadius();
     virtual void computeUVCoord();

};



#endif
