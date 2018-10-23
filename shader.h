#ifndef SHADER_H
#define SHADER_H

#ifndef _GLEW_H_
#define _GLEW_H_
#include <GL/glew.h>
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
