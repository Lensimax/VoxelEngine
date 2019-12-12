#ifndef DRAWDEBUG_H
#define DRAWDEBUG_H

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


class DrawDebug {

public:
    static inline void drawArrayPosition(unsigned int nbVertices, float *array, GLenum drawMode, GLenum primitiveDraw = GL_FILL){
        glPolygonMode(GL_FRONT_AND_BACK,primitiveDraw);
        GLuint buffer, vertexArray;

        glGenBuffers(1, &buffer);
        glGenVertexArrays(1,&vertexArray);

        // create the VBO associated with the grid (the terrain)
        glBindVertexArray(vertexArray);

        glBindBuffer(GL_ARRAY_BUFFER,buffer); // vertices
        glBufferData(GL_ARRAY_BUFFER,nbVertices*3*sizeof(float),array,GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);

        glDrawArrays(drawMode,0,nbVertices);

        glBindVertexArray(0);

        glDeleteBuffers(1,&buffer);
        glDeleteVertexArrays(1,&vertexArray);
        
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            
    };

};

#endif
