
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


#include "shader.h"


#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <string.h>

using namespace std;

Shader::Shader() : _programId(0) {

}

Shader::~Shader() {
    if(glIsProgram(_programId)) {
        glDeleteProgram(_programId);
    }
}

void Shader::load(const char *vertex_file_path, const char *fragment_file_path) {

    // create and compile vertex shader object
    std::string vertexCode   = getCode(vertex_file_path);
    const char * vertexCodeC = vertexCode.c_str();
    GLuint vertexId   = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexId,1,&(vertexCodeC),NULL);
    glCompileShader(vertexId);
    checkCompilation(vertexId);

    // create and compile fragment shader object
    std::string fragmentCode = getCode(fragment_file_path);
    const char * fragmentCodeC = fragmentCode.c_str();
    GLuint fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentId,1,&(fragmentCodeC),NULL);
    glCompileShader(fragmentId);
    checkCompilation(fragmentId);

    // create, attach and link program object
    _programId = glCreateProgram();
    glAttachShader(_programId,vertexId);
    glAttachShader(_programId,fragmentId);
    glLinkProgram(_programId);
    checkLinks(_programId);

    // delete vertex and fragment ids
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}


void Shader::reload(const char *vertex_file_path, const char *fragment_file_path) {

    // check if the program already contains a shader
    if(glIsProgram(_programId)) {
        // delete it...
        glDeleteProgram(_programId);
    }

    // ... and reload it
    load(vertex_file_path,fragment_file_path);
}




void Shader::checkCompilation(GLuint shaderId) {
    // check if the compilation was successfull (and display syntax errors)
    // call it after each shader compilation
    GLint result = GL_FALSE;
    int infoLogLength;

    glGetShaderiv(shaderId,GL_COMPILE_STATUS,&result);
    glGetShaderiv(shaderId,GL_INFO_LOG_LENGTH,&infoLogLength);

    if(infoLogLength>0) {
        std::vector<char> message(infoLogLength+1);
        glGetShaderInfoLog(shaderId,infoLogLength,NULL,&message[0]);
        printf("%s\n", &message[0]);
    }
}

void Shader::checkLinks(GLuint programId) {
    // check if links were successfull (and display errors)
    // call it after linking the program
    GLint result = GL_FALSE;
    int infoLogLength;

    glGetProgramiv(programId,GL_LINK_STATUS,&result);
    glGetProgramiv(programId,GL_INFO_LOG_LENGTH,&infoLogLength);

    if(infoLogLength>0) {
        std::vector<char> message(infoLogLength+1);
        glGetProgramInfoLog(programId,infoLogLength,NULL,&message[0]);
        printf("%s\n", &message[0]);
    }
}

std::string Shader::getCode(const char *file_path) {
    // return a string containing the source code of the input file
    std::string   shaderCode;
    std::ifstream shaderStream(file_path,std::ios::in);

    if(!shaderStream.is_open()) {
        cout << "Unable to open " << file_path << endl;
        return "";
    }

    std::string line = "";
    while(getline(shaderStream,line))
        shaderCode += "\n" + line;
    shaderStream.close();

    return shaderCode;
}
