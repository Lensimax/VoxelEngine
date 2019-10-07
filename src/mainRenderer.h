#ifndef MAINRENDERER_H
#define MAINRENDERER_H

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#endif

#include "tools/lights/light.h"
#include "scene.h"

#include "models/drawableObject.h"
#include "models/cube.h"
#include "tools/cameraProj.h"

#include <vector>
#include <string>

class MainRenderer {

    public:
        MainRenderer();
        ~MainRenderer();


        void paintGL(Scene *scene, int width, int height);
        void initializeGL();
        void displaySceneOnTheScreen(int width, int height);

        GLuint getTextureID();

    private:

        void renderTheScene(Scene *scene, int width, int height);

        Camera *getCamera();
        Light *getLight();

        glm::mat4 viewMat;
        glm::mat4 projectionMat;

        /* FBO */

        GLuint fboRenderScene;

        void createFBOSceneRender();
        void initFBOSceneRender(int width, int height);
        void deleteFBOSceneRender();

        GLuint renderedSceneTextureID;
        GLuint renderedDepth;

        /* final rendering */


        void createVAOQuad();
        void deleteVAOQuad();
        void drawQuad();

        Shader *postProcessShader;


        GLuint _vaoQuad;
        GLuint _quad;

};

#endif
