#ifndef MESH_LOADER_H
#define MESH_LOADER_H

class Mesh {
 public:
  Mesh(char *filename);
  ~Mesh();

  unsigned int *get_face(unsigned int i);
  float        *get_vertex(unsigned int i);
  float        *get_normal(unsigned int i);
  float        *get_tangent(unsigned int i);
  float        *get_coord(unsigned int i);
  float        *get_color(unsigned int i);

  // length
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
};

#endif // MESH_LOADER_H
