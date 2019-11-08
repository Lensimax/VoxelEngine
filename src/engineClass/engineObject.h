#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H


#include <string>
#include <vector>
#include "../models/transform.h"

class EngineObject {


    public:
    	EngineObject(int id = -1, std::string n = "EngineObject", Transform *t = new Transform());
        virtual ~EngineObject();
        virtual void createUI(char *ID);

        virtual void update();

        void setName(std::string n);
        std::string getName();
        int getID();
        void setID(int i);

        void addChild(EngineObject *obj);
        void removeChild(int id);
        void deleteAllChildren();


        Transform *getTransform();

        std::vector<EngineObject*> listOfChildren;

    protected:
        Transform *transform;

        std::string name;
        int ID;


};

#endif
