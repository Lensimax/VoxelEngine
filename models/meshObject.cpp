
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

#include <iostream>

#include "../material/lambertian.h"


MeshObject::MeshObject(std::string n, const char *filename, vec3 position, vec3 scale, vec3 rotation){
    transform = new Transform(position, scale, rotation);

    createMesh(filename);
    computeCenter();
    printf("vert %i  triangle %i\n", vertices.size()/3, triangles.size()/3);
    computeNormals();



    createVAO();

    material = new Lambertian();

    name = n;
}


MeshObject::~MeshObject(){
    deleteVAO();
    delete transform;
    delete material;
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

glm::vec3 MeshObject::getVertex(int i){
    glm::vec3 r;
    if(i >= 0 && i < vertices.size()){

        r[0] = vertices[i*3];
        r[1] = vertices[(i*3)+1];
        r[2] = vertices[(i*3)+2];
    } else {
        exit(1);
    }
    return r;
}


void MeshObject::computeNormals(){
    unsigned int nb_vertices = vertices.size()/3;
    float norm;


    glm::vec3 v12,v13,v1,v2,v3;

    // computing normals per faces
    std::vector<float> nf = std::vector<float>();
    for(unsigned int i=0;i<triangles.size();i+=3) {

        // the three vertices of the current face
        v1 = getVertex(triangles[i]);
        v2 = getVertex(triangles[i+1]);
        v3 = getVertex(triangles[i+2]);

        // the two vectors of the current face
        v12[0] = v2[0]-v1[0];
        v12[1] = v2[1]-v1[1];
        v12[2] = v2[2]-v1[2];

        v13[0] = v3[0]-v1[0];
        v13[1] = v3[1]-v1[1];
        v13[2] = v3[2]-v1[2];

        // cross product
        nf.push_back(v12[1]*v13[2] - v12[2]*v13[1]);
        nf.push_back(v12[2]*v13[0] - v12[0]*v13[2]);
        nf.push_back(v12[0]*v13[1] - v12[1]*v13[0]);

        // normalization

        norm = sqrt(nf[3*i]*nf[3*i]+nf[3*i+1]*nf[3*i+1]+nf[3*i+2]*nf[3*i+2]);
        if(norm != 0.0){
            nf[3*i  ] /= norm;
            nf[3*i+1] /= norm;
            nf[3*i+2] /= norm;
        } else {
            printf("division by zero\n");
        }
    }

    // computing normals per vertex

    normals = std::vector<float>();
    std::vector<float> nv = std::vector<float>();

    for(unsigned int i=0;i<nb_vertices;++i) {
        // initialization
        normals.push_back(0.0);
        normals.push_back(0.0);
        normals.push_back(0.0);
        nv.push_back(0.0);
    }

    int f[3];
    for(unsigned int i=0;i<triangles.size();i+=3) {
        // face normals average
        // f = get_face(i);
        f[0] = triangles[i];
        f[1] = triangles[i+1];
        f[2] = triangles[i+2];

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

    for(unsigned int i=0;i<nb_vertices;++i) {
        // normalization
        if(-nv[i] != 0.0){
            normals[3*i  ] /= -nv[i];
            normals[3*i+1] /= -nv[i];
            normals[3*i+2] /= -nv[i];
        } else {
            printf("division by 0\n");
        }
    }

}

void MeshObject::computeCenter(){
    glm::vec3 c = glm::vec3(0.0,0.0,0.0);
    int nb_vertices = vertices.size();
    for(int i=0;i<nb_vertices*3;i+=3) {
        c[0] += vertices[i  ];
        c[1] += vertices[i+1];
        c[2] += vertices[i+2];
    }
    center[0] = c[0]/(float)nb_vertices;
    center[1] = c[1]/(float)nb_vertices;
    center[2] = c[2]/(float)nb_vertices;
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
    glDrawElements(GL_TRIANGLES,3*nbTriangles(),GL_UNSIGNED_INT,(void *)0);
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
    glBufferData(GL_ARRAY_BUFFER,nbVertices()*3*sizeof(float),getVertices(),GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void *)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[1]); // indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,nbTriangles()*3*sizeof(int),getTriangles(),GL_STATIC_DRAW);
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
