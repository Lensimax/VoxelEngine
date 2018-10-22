#ifndef MAINRENDERER_H
#define MAINRENDERER_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

//#include "models/cube.h"

#include <vector>

class MainRenderer {

 public:
    MainRenderer();
    ~MainRenderer();


    virtual void paintGL(int width, int height);
    virtual void initializeGL();

    private:

        void makeScene();
        void deleteScene();


        glm::mat4 viewMat;
        glm::mat4 projectionMat;

        //std::vector<DrawableObject*> objectsToDraw;

        //DrawableObject* object;

        int width, height;
};

#endif
