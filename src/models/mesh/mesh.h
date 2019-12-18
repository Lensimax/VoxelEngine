
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

#include "../../components/component.h"

#define POSITION_ATTRIB 0
#define VERTEX_NORMAL_ATTRIB 1
#define VERTEX_UV_ATTRIB 2
#define VERTEX_COLOR_ATTRIB 3
#define INDICES_ATTRIB 4


class Mesh : public Component {

public:

     virtual ~Mesh() = default;

     

     virtual void createUI();
     virtual void recreate() = 0;


     glm::vec3 getMin();
     glm::vec3 getMax();

     void update() override;

     virtual void createVAO();

     virtual void drawVAO();

     virtual void deleteVAO();

     

     inline void *getVertices(){ return &(m_vertices[0]);}
     inline void *getNormals(){ return &(m_normals[0]);}
     inline void *getUVs(){ return &(m_coords[0]);}
     inline void *getColors(){ return &(m_colors[0]);}

     unsigned int getNBVertices(){ return m_vertices.size();}

     virtual unsigned int getNBFaces(){ return getNBVertices()/3; }

     inline glm::vec3 get_vertex(unsigned int i) { return m_vertices[i];}
     inline glm::vec3 get_normal(unsigned int i) { return m_normals[i];}
     inline glm::vec3 get_color(unsigned int i) { return m_colors[i];}
     inline glm::vec2 get_coord(unsigned int i) { return m_coords[i];}

     inline glm::vec3 get_tangent(unsigned int i) { return m_tangents[i];}

     // -- Modificators --
     
     void addTriangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3,
                      const glm::vec3& normal, const glm::vec3& color);

     void addQuad    (const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4,
                      const glm::vec3& normal, const glm::vec3& color);

     virtual void clear();

    protected:


     float m_maxX, m_maxY, m_maxZ;
     float m_minX, m_minY, m_minZ;

     // data
     std::vector<glm::vec3> m_vertices;
     std::vector<glm::vec3> m_normals;
     std::vector<glm::vec3> m_colors;

     std::vector<glm::vec2> m_coords; // ne sert pas pour l'instant

     std::vector<glm::vec3> m_tangents;
     std::vector<glm::vec3> m_backupVertices;

   
     float          m_radius;

 

     void computeBoundingBox();
     void inflateBoundingBox();

     GLuint m_vertexArrayID;
     GLuint *m_buffers;


};



#endif
