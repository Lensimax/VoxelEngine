#ifndef DRAWABLEOBJECT_H
#define DRAWABLEOBJECT_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>


class DrawableObject {
    public:
        virtual inline float *getVertices() = 0;
        virtual inline int *getTriangles() = 0;

        virtual glm::mat4 getTransform() = 0;

        virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat) = 0;

    protected:
        virtual void createVAO() = 0;
        virtual void deleteVAO() = 0;
};

#endif
