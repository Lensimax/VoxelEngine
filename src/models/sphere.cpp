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


#include "sphere.h"


#include "../material/lambertian.h"



Sphere::Sphere(std::string n, float radius, unsigned int rings, unsigned int sectors, vec3 position, vec3 scale, vec3 rotation){
    setName(n);
    transform = new Transform(position, scale, rotation);

    createMesh(radius, rings, sectors);

    material = new Lambertian();

    createVAO();
}

void Sphere::draw(glm::mat4 viewMat, glm::mat4 projectionMat, glm::vec3 light){

    glUseProgram(material->shaderID());

    setUniform(viewMat, projectionMat, light);

    glBindVertexArray(vertexArrayID);
    glDrawElements(GL_TRIANGLES,3*nbTriangles(),GL_UNSIGNED_INT,(void *)0);
    glBindVertexArray(0);

    glUseProgram(0);
}

void Sphere::createVAO(){

    buffers = new GLuint[2];

    glGenBuffers(2, buffers);
    glGenVertexArrays(1,&vertexArrayID);

    // create the VBO associated with the grid (the terrain)
    glBindVertexArray(vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]); // vertices
    glBufferData(GL_ARRAY_BUFFER,nbVertices()*3*sizeof(float),getVertices(),GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[1]); // indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,nbTriangles()*3*sizeof(int),getTriangles(),GL_STATIC_DRAW);
}

void Sphere::deleteVAO(){
    glDeleteBuffers(2,buffers);
    glDeleteVertexArrays(1,&vertexArrayID);
}


void Sphere::createMesh(float radius, unsigned int rings, unsigned int sectors){

    vertices = std::vector<float>();
    triangles = std::vector<int>();
    normals = std::vector<float>();
    texCoords = std::vector<float>();

    float const R = 1./(float)(rings-1);
    float const S = 1./(float)(sectors-1);

    vertices.resize(rings * sectors * 3);
    normals.resize(rings * sectors * 3);
    texCoords.resize(rings * sectors * 2);
    std::vector<float>::iterator v = vertices.begin();
    std::vector<float>::iterator n = normals.begin();
    std::vector<float>::iterator t = texCoords.begin();
    for(unsigned int r = 0; r < rings; r++){
        for(unsigned int s = 0; s < sectors; s++) {
            float const y = sin( -M_PI_2 + M_PI * r * R );
            float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
            float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

            *t++ = s*S;
            *t++ = r*R;

            *v++ = x * radius;
            *v++ = y * radius;
            *v++ = z * radius;

            *n++ = x;
            *n++ = y;
            *n++ = z;
        }
    }

    triangles.resize(rings * sectors * 4);
    std::vector<int>::iterator i = triangles.begin();
    for(unsigned int r = 0; r < rings; r++) {
        for(unsigned int s = 0; s < sectors; s++) {
            *i++ = r * sectors + s;
            *i++ = r * sectors + (s+1);
            *i++ = (r+1) * sectors + (s+1);
            *i++ = (r+1) * sectors + s;
        }
    }
}



void Sphere::createUI(char *ID){
    ImGui::BeginChild(ID);
    ImGui::Text(name.c_str());
    ImGui::Separator();

    transform->createUI();
    ImGui::Separator();
    material->createUI();
    ImGui::Separator();

    ImGui::EndChild();
}

void Sphere::setUniform(glm::mat4 viewMat, glm::mat4 projectionMat, glm::vec3 light){

    glm::mat4 modelMat = transform->getMat4();


    // send the transformation matrix
    material->callUniform(modelMat, viewMat, projectionMat, light);

}

int *Sphere::getTriangles(){
    return &triangles[0];
}

float *Sphere::getVertices(){
    return &vertices[0];
}

int Sphere::nbVertices(){
    return vertices.size()/3;
}

int Sphere::nbTriangles(){
    return triangles.size()/3;
}

Sphere::~Sphere(){
    deleteVAO();
    delete transform;
    delete material;
}
