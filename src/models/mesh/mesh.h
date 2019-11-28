
#ifndef MESH_H
#define MESH_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

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
     void *getNormals();
     void *getUVs();
     void *getColors();

     unsigned int getNBVertices(){
          return vertices.size();
     }

     inline unsigned int getNBFaces(){
          return getNBVertices()/3;
     }

     virtual void createUI();
     virtual void recreate() = 0;


     glm::vec3 getMin();
     glm::vec3 getMax();


     virtual void update();

     void createVAO();

     void drawVAO();

     void deleteVAO();

    protected:
     glm::vec3        get_vertex(unsigned int i);
     glm::vec3        get_normal(unsigned int i);
     glm::vec3        get_tangent(unsigned int i);
     glm::vec2        get_coord(unsigned int i);
     glm::vec3        get_color(unsigned int i);


     float maxX, maxY, maxZ;
     float minX, minY, minZ;

     // data
     std::vector<glm::vec3> vertices;
     std::vector<glm::vec3> normals;
     std::vector<glm::vec3> tangents;
     std::vector<glm::vec3> colors;
     std::vector<glm::vec2> coords;

     std::vector<glm::vec3> backupVertices;

   
     float          radius;

 

     void computeBoundingBox();
     void inflateBoundingBox();

     GLuint vertexArrayID;
     GLuint *buffers;


};



#endif
