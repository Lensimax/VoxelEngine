
#ifndef SCENE_H
#define SCENE_H


#include <string>
#include <vector>

#include "engineObject.h"


class Scene {

    public:
        Scene();
        ~Scene();

        void createUI();
        // Camera *getCamera();
        // Light *getLight();
        void createUIAtID(int indexItem, char *ID);
        std::vector<std::string> getNameOfAllObjects();


        std::vector<EngineObject*> objectsEngine;

    private:
        void deleteScene();

};

#endif
