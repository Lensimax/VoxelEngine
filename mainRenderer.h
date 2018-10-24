#ifndef MAINRENDERER_H
#define MAINRENDERER_H

#ifndef GLM_H
#define GLM_H
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#endif

#include "models/drawableObject.h"
#include "models/cube.h"

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

        DrawableObject* object;

};

#endif
