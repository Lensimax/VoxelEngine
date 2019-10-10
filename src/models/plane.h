#ifndef PLANE_H
#define PLANE_H


#include "../material/lambertian.h"

#include "meshGrid.h"
#include "drawableObject.h"


class Plane : public DrawableObject {

public:

    Plane(std::string n = "Plane", unsigned int size = 16, float width = 1, float gridZ = 0, Transform *t = new Transform(), Material *m = new Lambertian());
    ~Plane();

    virtual void createUI(char *ID);

    virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat, Light *light);

    virtual float *getVertices();
    virtual unsigned int *getTriangles();
    virtual int nbVertices();
    virtual int nbTriangles();

private:
    void createVAO();
    void deleteVAO();

    void setUniform(glm::mat4 viewMat, glm::mat4 projectionMat, Light* light);


    GLuint vertexArrayID;
    GLuint *buffers;

    Material *material;

    Mesh *mesh;

};


#endif
