#ifndef SHADER_H
#define SHADER_H

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include <string>

class Shader {
    public:

    Shader();
    ~Shader();

    void load(const char *vertex_file_path, const char *fragment_file_path);

    void reload(const char *vertex_file_path, const char *fragment_file_path);

    inline GLuint id() {return _programId;}

    private:

    GLuint _programId;

    // string containing the source code of the input file
    std::string getCode(const char *file_path);

    // call it after each shader compilation
    void checkCompilation(GLuint shaderId);

    // call it after linking the program
    void checkLinks(GLuint programId);
};

#endif // SHADER_H
