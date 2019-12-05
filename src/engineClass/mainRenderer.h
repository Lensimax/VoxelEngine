#ifndef MAINRENDERER_H
#define MAINRENDERER_H

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include "../tools/lights/light.h"
#include "scene.h"
#include "../tools/lights/directionnalLight.h"
#include "../material/shader.h"

#include "../models/drawableObject.h"
#include "../tools/camera.h"
#include "../tools/cameraProj.h"

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



        void update();
        void createUI();



        inline void toggleWire(){
            m_wireActivated = !m_wireActivated;
        }

        inline void toggleCullFace(){
            cullface = !cullface;
        }

        inline unsigned int width(){
            return widthScreen;
        }

        inline unsigned int height(){
            return heightScreen;
        }

        inline GLuint getRenderSceneID(){
            return renderedSceneTextureID;
        }

        inline Transform *getTransformEditor(){
            return m_transformEditor;
        }



    private:

        void renderTheScene(Scene *scene, int width, int height);
        void renderTheSceneEditor(Scene *scene, int width, int height);
        void drawRecursive(glm::mat4 modelMat, EngineObject *obj, Camera *c, Light *l, float screenAspectRatio);

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

        bool m_wireActivated;
        bool cullface;

        unsigned int widthScreen, heightScreen;

        Camera *m_camera;
        Transform *m_transformEditor;

};

#endif
