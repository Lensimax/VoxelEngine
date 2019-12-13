
#ifndef SCENE_H
#define SCENE_H

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include <string>
#include <vector>

#include "../tools/lights/light.h"
#include "../tools/camera.h"

#include "gameObject.h"

struct CameraInfo {
    Camera *cam;
    glm::mat4 viewMat;
}; 


class Scene {

    public:
        Scene();
        ~Scene();

        void createUI();
        CameraInfo getCamera();
        Light *getLight();
        void createUIAtID(int indexItem, char *ID);
        void drawUIAtID(std::vector<GameObject*> objs, int indexItem, char *ID);
        void getAllObjects(std::vector<std::string> & names, std::vector<int> & ids);

        void update();
        void updateObj(GameObject *obj);


        void addGameObject();
        void addCube();
        void deleteObject(int id);

        void loadDefaultScene();


        std::vector<GameObject*> objectsEngine;
        int addNewId();

        void togglePause();


    private:
        void deleteScene();

        CameraInfo getCameraRecursive(GameObject *obj, glm::mat4 modelMat);
        Light *getLightRecursive(GameObject *obj);

        int m_idObject = 0;

        bool m_pause;

};

#endif
