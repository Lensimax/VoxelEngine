#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H


#include <glm/mat4.hpp>
#include <glm/gtc/matrix_transform.hpp>



#include "transform.h"
#include "../tools/lights/light.h"
#include "../engineObject.h"

#include <string>


class DrawableObject : public EngineObject {
    public:


        /* get vertices array of this object */
        virtual float *getVertices() = 0;
        /* get faces/triangle array of this object */
        virtual unsigned int *getTriangles() = 0;

        /* get number of vertices */
        virtual int nbVertices() = 0;
        /* get number of triangles */
        virtual int nbTriangles() = 0;

        /* draw the object in the screen */
        virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat, Light *light) = 0;

        /* create the buffers and the vertex array on the GPU */
        virtual void createVAO() = 0;
        /* delete it */
        virtual void deleteVAO() = 0;



        Transform *getTransform();



    protected:
        Transform *transform;
};

#endif
