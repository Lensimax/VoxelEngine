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

        virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat) = 0;

        virtual void createVAO() = 0;
        virtual void deleteVAO() = 0;

        virtual void debugFaces() = 0;
        virtual void debugVertices() = 0;

};

#endif
