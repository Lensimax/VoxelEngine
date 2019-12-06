#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H


#include <string>
#include <vector>
#include "../models/transform.h"

class GameObject {


    public:
    	GameObject(int id = -1, std::string n = "GameObject", Transform *t = new Transform());
        virtual ~GameObject();
        virtual void createUI(char *ID);

        virtual void update();

        void setName(std::string n);
        std::string getName();
        int getID();
        void setID(int i);

        void addChild(GameObject *obj);
        void removeChild(int id);
        void deleteAllChildren();


        Transform *getTransform();

        std::vector<GameObject*> m_listOfChildren;

    protected:
        Transform *m_transform;

        std::string m_name;
        int m_id;


};

#endif
