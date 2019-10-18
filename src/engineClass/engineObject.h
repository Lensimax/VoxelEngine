#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H


#include <string>
#include "../models/transform.h"

class EngineObject {


    public:
    	EngineObject(int id = -1, std::string n = "EngineObject", Transform *t = new Transform());
        virtual ~EngineObject() = default;
        virtual void createUI(char *ID);

        void setName(std::string n);
        std::string getName();
        int getID();
        void setID(int i);


        Transform *getTransform();

    protected:

        std::string name;
        int ID;
        Transform *transform;

};

#endif
