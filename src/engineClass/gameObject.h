#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H


#include <string>
#include <vector>
#include "../models/transform.h"
#include "component.h"



class GameObject {


public:
    GameObject(int id = -1, std::string n = "GameObject", Transform *t = new Transform());
    virtual ~GameObject();
    virtual void createUI(char *ID);

    virtual void update();

    // ID + NAME
    void setName(std::string n);
    std::string getName();
    int getID();
    void setID(int i);

    /// GRAPHE SCENE
    void addChild(GameObject *obj);
    void removeChild(int id);
    void deleteAllChildren();
    std::vector<GameObject*> m_listOfChildren;

    // COMPONENT
    template< class ComponentType>
    ComponentType & getComponent();

    // TRANSFORM
    Transform *getTransform();
    Transform *m_transform;

protected:
    std::vector<Component*> m_components;

    std::string m_name;
    int m_id;


};

#endif
