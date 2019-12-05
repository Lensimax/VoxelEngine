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




        void update();
        void createUI();



        inline void toggleWire(){
            m_wireActivated = !m_wireActivated;
        }

        inline void toggleCullface(){
            m_cullface = !m_cullface;
        }

        GLuint getTextureID(){
            return m_renderedSceneTextureID;
        }

        inline unsigned int width(){
            return m_widthScreen;
        }

        inline unsigned int height(){
            return m_heightScreen;
        }

        inline GLuint getRenderSceneID(){
            return m_renderedSceneTextureID;
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

        glm::mat4 m_viewMat;
        glm::mat4 m_projectionMat;

        // FBO

        GLuint m_fboRenderScene;
        GLuint m_renderedSceneTextureID;
        GLuint m_testID;
        GLuint m_renderedDepth;

        void createFBOSceneRender();
        void initFBOSceneRender(int width, int height);
        void deleteFBOSceneRender();

        // FBO Editeur
        GLuint m_fboEditor;
        GLuint m_editorTextureID;
        GLuint m_editorDepth;

        void createFBOEditorRender();
        void initFBOEditorRender(int width, int height);
        void deleteFBOEditorRender();

        /* final rendering */
        
        void createVAOQuad();
        void deleteVAOQuad();
        void drawQuad();

        Shader *m_postProcessShader;


        GLuint m_vaoQuad;
        GLuint m_quad;

        bool m_wireActivated;
        bool m_cullface;

        unsigned int m_widthScreen, m_heightScreen;

        Camera *m_camera;
        Transform *m_transformEditor;

};

#endif
