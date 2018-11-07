#include "meshLoader.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

unsigned int *Mesh::get_face(unsigned int i) {
  return &(faces[3*i]);
}

float *Mesh::get_vertex(unsigned int i) {
  return &(vertices[3*i]);
}

float *Mesh::get_normal(unsigned int i) {
  return &(normals[3*i]);
}

float *Mesh::get_tangent(unsigned int i) {
  return &(tangents[3*i]);
}

float *Mesh::get_coord(unsigned int i) {
  return &(coords[2*i]);
}

float *Mesh::get_color(unsigned int i) {
  return &(colors[3*i]);
}


Mesh::Mesh(char *filename) {
  unsigned int tmp;
  unsigned int i,j;
  unsigned int *f;
  float *nf;
  float norm;
  float *v1, *v2, *v3;
  float v12[3];
  float v13[3];
  float *nv;
  float *n;
  FILE *file;
  int   error;
  float c[3] = {0.0,0.0,0.0};
  float r;
  float *w1, *w2, *w3;
  float *t;
  float x1,x2,y1,y2,z1,z2;
  float s1,s2,t1,t2;

  if((file=fopen(filename,"r"))==NULL) {
    printf("Unable to read %s\n",filename);
  }

  // create mesh
  vertices = NULL;
  normals  = NULL;
  tangents = NULL;
  colors   = NULL;
  coords   = NULL;
  faces    = NULL;

  error = fscanf(file,"OFF\n%d %d %d\n",&(nb_vertices),&(nb_faces),&tmp);
  if(error==EOF) {
    printf("Unable to read %s\n",filename);
  }
  
  vertices = (float *)malloc(3*nb_vertices*sizeof(float));
  normals  = (float *)malloc(3*nb_vertices*sizeof(float));
  tangents = (float *)malloc(3*nb_vertices*sizeof(float));
  colors   = (float *)malloc(3*nb_vertices*sizeof(float));
  coords   = (float *)malloc(2*nb_vertices*sizeof(float));
  faces    = (unsigned int *)malloc(3*nb_faces*sizeof(unsigned int));

  // reading vertices
  j = 0;
  for(i=0;i<nb_vertices;++i) {
    error = fscanf(file,"%f %f %f\n",&(vertices[j]),&(vertices[j+1]),&(vertices[j+2]));
    if(error==EOF) {
      printf("Unable to read vertices of %s\n",filename);
      // mesh_delete(mesh);
      // return NULL;
    }

    j += 3;
  }

  // reading faces
  j = 0;
  for(i=0;i<nb_faces;++i) {
    error = fscanf(file,"%d %d %d %d\n",&tmp,&(faces[j]),&(faces[j+1]),&(faces[j+2]));
    if(error==EOF) {
      printf("Unable to read faces of %s\n",filename);
      // mesh_delete(mesh);
      // return NULL;
    }
    
    if(tmp!=3) {
      printf("Error : face %d is not a triangle (%d polygonal face!)\n",i/3,tmp);
      // mesh_delete(mesh);
      // return NULL;
    }
    j += 3;
  }
  
  fclose(file); 

  // computing center
  for(i=0;i<nb_vertices*3;i+=3) {
    c[0] += vertices[i  ];
    c[1] += vertices[i+1];
    c[2] += vertices[i+2];
  }
  center[0] = c[0]/(float)nb_vertices;
  center[1] = c[1]/(float)nb_vertices;
  center[2] = c[2]/(float)nb_vertices;

  // computing radius
  radius = 0.0;
  for(i=0;i<nb_vertices*3;i+=3) {
    c[0] = vertices[i  ]-center[0];
    c[1] = vertices[i+1]-center[1];
    c[2] = vertices[i+2]-center[2];
    
    r = sqrt(c[0]*c[0]+c[1]*c[1]+c[2]*c[2]);
    radius = r>radius ? r : radius;
  }

  // computing normals per faces
  nf = (float *)malloc(3*nb_faces*sizeof(float));
  for(i=0;i<nb_faces;++i) {
    f = get_face(i);
    
    // the three vertices of the current face
    v1 = get_vertex(f[0]);
    v2 = get_vertex(f[1]);
    v3 = get_vertex(f[2]);

    // the two vectors of the current face
    v12[0] = v2[0]-v1[0];
    v12[1] = v2[1]-v1[1];
    v12[2] = v2[2]-v1[2];

    v13[0] = v3[0]-v1[0];
    v13[1] = v3[1]-v1[1];
    v13[2] = v3[2]-v1[2];

    // cross product
    nf[3*i  ] = v12[1]*v13[2] - v12[2]*v13[1];
    nf[3*i+1] = v12[2]*v13[0] - v12[0]*v13[2];
    nf[3*i+2] = v12[0]*v13[1] - v12[1]*v13[0];

    // normalization
    norm = sqrt(nf[3*i]*nf[3*i]+nf[3*i+1]*nf[3*i+1]+nf[3*i+2]*nf[3*i+2]);
    nf[3*i  ] /= norm;
    nf[3*i+1] /= norm;
    nf[3*i+2] /= norm;
  }

  // computing normals per vertex
  nv = (float *)malloc(nb_vertices*sizeof(float));
  for(i=0;i<nb_vertices;++i) {
    // initialization
    normals[3*i  ] = 0.0;
    normals[3*i+1] = 0.0;
    normals[3*i+2] = 0.0;
    nv[i] = 0.0;
  }
  for(i=0;i<nb_faces;++i) {
    // face normals average  
    f = get_face(i);
    n = &(nf[3*i]);

    normals[3*f[0]  ] += nf[3*i  ];
    normals[3*f[0]+1] += nf[3*i+1];
    normals[3*f[0]+2] += nf[3*i+2];
    nv[f[0]] ++;

    normals[3*f[1]  ] += nf[3*i  ];
    normals[3*f[1]+1] += nf[3*i+1];
    normals[3*f[1]+2] += nf[3*i+2];
    nv[f[1]] ++;

    normals[3*f[2]  ] += nf[3*i  ];
    normals[3*f[2]+1] += nf[3*i+1];
    normals[3*f[2]+2] += nf[3*i+2];
    nv[f[2]] ++;
  }
  for(i=0;i<nb_vertices;++i) {
    // normalization
    normals[3*i  ] /= -nv[i];
    normals[3*i+1] /= -nv[i];
    normals[3*i+2] /= -nv[i];
  }

  free(nf);
  free(nv);

  // computing colors as normals 
  for(i=0;i<3*nb_vertices;++i) {
    colors[i] = (normals[i]+1.0)/2.0;
  }

  // computing spherical uv coordinates
  for(i=0;i<nb_vertices;++i) {
    v1 = get_vertex(i);
    
    // direction between center and current point
    c[0] = v1[0]-center[0];
    c[1] = v1[1]-center[1];
    c[2] = v1[2]-center[2];
    
    // normalization
    norm = sqrt(c[0]*c[0]+c[1]*c[1]+c[2]*c[2]);
    c[0] /= norm;
    c[1] /= norm;
    c[2] /= norm;

    // elevation & azimuth remapped between 0 and 1
    r = c[2]/sqrt(c[0]*c[0]+c[2]*c[2]);
    if(r>=1.0f) r = 1.0f;
    if(r<=-1.0f) r = -1.0f;
    coords[2*i  ] = asin(r);
    if(c[0]<0.0) coords[2*i] = M_PI-coords[2*i];
    coords[2*i] = (coords[2*i]+(M_PI/2.0))/(2.0*M_PI);
    coords[2*i+1] = acos(c[1])/M_PI;
  }

  // init tangents 
  for(i=0;i<3*nb_vertices;++i) {
    tangents[i] = 0.0f;
  }
  // iterate over faces 
  for(i=0;i<nb_faces;++i) {
    f = get_face(i);
    
    v1 = get_vertex(f[0]);
    v2 = get_vertex(f[1]);
    v3 = get_vertex(f[2]);

    w1 = get_coord(f[0]);
    w2 = get_coord(f[1]);
    w3 = get_coord(f[2]);

    x1 = v2[0] - v1[0];
    x2 = v3[0] - v1[0];
    y1 = v2[1] - v1[1];
    y2 = v3[1] - v1[1];
    z1 = v2[2] - v1[2];
    z2 = v3[2] - v1[2];
    
    s1 = w2[0] - w1[0];
    s2 = w3[0] - w1[0];
    t1 = w2[1] - w1[1];
    t2 = w3[1] - w1[1];

    r = 1.0f/(s1*t2 - s2*t1);
    
    for(j=0;j<3;++j) {
      t = get_tangent(f[j]);
      t[0] += (t2*x1-t1*x2)*r;
      t[1] += (t2*y1-t1*y2)*r;
      t[2] += (t2*z1-t1*z2)*r;
    }
  }

  // normalize and project tangents 
  for(i=0;i<nb_vertices;++i) {
    n = get_normal(i);
    t = get_tangent(i);

    // project
    r = n[0]*t[0]+n[1]*t[1]+n[2]*t[2];
    t[0] = t[0]-n[0]*r;
    t[1] = t[1]-n[1]*r;
    t[2] = t[2]-n[2]*r;
    

    // normalize
    norm = sqrt(t[0]*t[0]+t[1]*t[1]+t[2]*t[2]);
    t[0] /= norm;
    t[1] /= norm;
    t[2] /= norm;
  }

  //free(nf);
}

Mesh::~Mesh() {
  if(normals!=NULL)
    free(normals);

  if(tangents!=NULL)
    free(tangents);
  
  if(colors!=NULL)
    free(colors);
  
  if(vertices!=NULL)
    free(vertices);
  
  if(faces!=NULL)
    free(faces);

  if(coords!=NULL)
    free(coords);
}
