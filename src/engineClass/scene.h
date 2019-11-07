
#ifndef SCENE_H
#define SCENE_H

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include <string>
#include <vector>

#include "../tools/lights/light.h"
#include "../tools/camera.h"

#include "engineObject.h"


class Scene {

    public:
        Scene();
        ~Scene();

        void createUI();
        Camera *getCamera();
        Light *getLight();
        void createUIAtID(int indexItem, char *ID);
        void drawUIAtID(std::vector<EngineObject*> objs, int indexItem, char *ID);
        void getAllObjects(std::vector<std::string> & names, std::vector<int> & ids);

        void update();
        void updateObj(EngineObject *obj);


        void addMeshObject();
        void addPlane();
        void addEngineObject();
        void addSphere();
        void deleteObject(int id);


        std::vector<EngineObject*> objectsEngine;
        int addNewId();

    private:
        void deleteScene();

        int IDObject = 0;


};

#endif
