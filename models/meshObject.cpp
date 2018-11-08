
#include "../imgui/imgui.h"
#include "../impl/imgui_impl_glfw.h"
#include "../impl/imgui_impl_opengl3.h"


#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif


#include "meshObject.h"
#include "meshLoader.h"

#include <iostream>

#include "../material/lambertian.h"


MeshObject::MeshObject(std::string n, const char *filename, vec3 position, vec3 scale, vec3 rotation){
    transform = new Transform(position, scale, rotation);

    // createMesh(filename);

    // mesh = new CubeMesh();
    mesh = new MeshLoader(filename);


    createVAO();

    material = new Lambertian();

    name = n;
}


MeshObject::~MeshObject(){
    deleteVAO();
    delete transform;
    delete material;
    delete mesh;
}



void MeshObject::createMesh(const char *filename){
    FILE *file;
    int error, nb_vertices, nb_faces;
    unsigned int tmp;

    float x, y, z;
    int face1, face2, face3;

    vertices = std::vector<float>();
    triangles = std::vector<int>();

    if((file=fopen(filename,"r"))==NULL) {
        printf("Unable to read %s\n",filename);
    }

    error = fscanf(file,"OFF\n%d %d %d\n",&(nb_vertices),&(nb_faces),&tmp);
    if(error==EOF) {
        printf("Unable to read %s\n",filename);
    }

    for(int i=0;i<nb_vertices;i++) {
        error = fscanf(file,"%f %f %f\n",&x,&y,&z);
        if(error==EOF) {
            printf("Unable to read vertices of %s\n",filename);
            exit(1);
        }

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
    }

    for(int i=0;i<nb_faces;i++) {
    error = fscanf(file,"%d %d %d %d\n",&tmp, &face1, &face2, &face3);
    if(error==EOF) {
      printf("Unable to read faces of %s\n",filename);
        exit(1);
    }

    if(tmp!=3) {
      printf("Error : face %d is not a triangle (%d polygonal face!)\n",i/3,tmp);
      exit(1);
    }
    triangles.push_back(face1);
    triangles.push_back(face2);
    triangles.push_back(face3);
  }
  fclose(file);
}





int *MeshObject::getTriangles(){
    return &triangles[0];
}

float *MeshObject::getVertices(){
    return &vertices[0];
}

int MeshObject::nbVertices(){
    return vertices.size()/3;
}

int MeshObject::nbTriangles(){
    return triangles.size()/3;
}



void MeshObject::draw(glm::mat4 viewMat, glm::mat4 projectionMat, glm::vec3 light){

    glUseProgram(material->shaderID());

    setUniform(viewMat, projectionMat, light);

    glBindVertexArray(vertexArrayID);
    glDrawElements(GL_TRIANGLES,3*mesh->getNBFaces(),GL_UNSIGNED_INT,(void *)0);
    glBindVertexArray(0);

    glUseProgram(0);
}

void MeshObject::createVAO(){

    buffers = new GLuint[2];

    glGenBuffers(2, buffers);
    glGenVertexArrays(1,&vertexArrayID);

    // create the VBO associated with the grid (the terrain)
    glBindVertexArray(vertexArrayID);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]); // vertices
    glBufferData(GL_ARRAY_BUFFER,mesh->getNBVertices()*3*sizeof(float),mesh->getVertices(),GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[1]); // indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,mesh->getNBFaces()*3*sizeof(unsigned int),mesh->getFaces(),GL_STATIC_DRAW);
}

void MeshObject::deleteVAO(){
    glDeleteBuffers(2,buffers);
    glDeleteVertexArrays(1,&vertexArrayID);
}

void MeshObject::setUniform(glm::mat4 viewMat, glm::mat4 projectionMat, glm::vec3 light){

    glm::mat4 modelMat = transform->getMat4();


    // send the transformation matrix
    material->callUniform(modelMat, viewMat, projectionMat, light);

}


void MeshObject::createUI(char *ID){
    ImGui::BeginChild(ID);
    ImGui::Text(name.c_str());
    ImGui::Separator();

    transform->createUI();
    ImGui::Separator();
    material->createUI();
    ImGui::Separator();

    ImGui::EndChild();
}
