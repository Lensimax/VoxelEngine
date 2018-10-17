#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


class DrawableObject {
    public:


        virtual float *getVertices() = 0;
        virtual int *getTriangles() = 0;

        virtual int nbVertices() = 0;
        virtual int nbFaces() = 0;

        virtual glm::mat4 getTransform() = 0;

        virtual GLuint shaderID() = 0;

};

#endif
