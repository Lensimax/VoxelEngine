#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H


#ifndef GLM_H
#define GLM_H
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#endif


#include "transform.h"


class DrawableObject {
    public:

        virtual ~DrawableObject() = default;

        /* get vertices array of this object */
        virtual float *getVertices() = 0;
        /* get faces/triangle array of this object */
        virtual int *getTriangles() = 0;

        /* get number of vertices */
        virtual int nbVertices() = 0;
        /* get number of triangles */
        virtual int nbTriangles() = 0;

        /* draw the object in the screen */
        virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat) = 0;

        /* create the buffers and the vertex array on the GPU */
        virtual void createVAO() = 0;
        /* delete it */
        virtual void deleteVAO() = 0;

        /* DEBUG */
        virtual void debugTrianglesAndTriangles() = 0;

        Transform *getTransform();

        virtual void createUI() = 0;


    protected:
        Transform *transform;
};

#endif
