#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "drawableObject.h"

#include <vector>

class Cube : public DrawableObject {
    public:

        Cube();
        ~Cube();

        virtual void getVertices();
        virtual void getTriangles();

        virtual glm::mat4 getTransform();

        virtual void draw(glm::mat4 viewMat, glm::mat4 projectionMat);

    protected:
        virtual void createVAO();
        virtual void deleteVAO();
        virtual void setUniform();


};

#endif
