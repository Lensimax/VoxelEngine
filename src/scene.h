
#ifndef SCENE_H
#define SCENE_H


#include "models/drawableObject.h"


#include "tools/cameraProj.h"
#include "tools/lights/light.h"

#include <vector>


class Scene {

    public:
        Scene();
        ~Scene();

        void createUI();
        Camera *getCamera();
        Light *getLight();
        void createUIAtID(int indexItem, char *ID);
        std::vector<std::string> getNameOfAllObjects();


        std::vector<EngineObject*> objectsEngine;

    private:
        void deleteScene();

};

#endif
