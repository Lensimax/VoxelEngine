#ifndef ENGINE_OBJECT_H
#define ENGINE_OBJECT_H


#include <string>
#include <vector>
#include "../models/transform.h"

#include "../components/component.h"



class GameObject {


public:
    GameObject(int id = -1, std::string n = "GameObject", Transform *t = new Transform());
    virtual ~GameObject();
    virtual void createUI(char *ID);

    void update();
    void inputUpdate();
    void physicsUpdate();

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
    template< class ComponentType> ComponentType  getComponent();
    template< class ComponentType> std::vector<ComponentType> getComponents();
    template< class ComponentType> void addComponent(Component * component);
    template< class ComponentType> void addComponent();
    template< class ComponentType > bool removeComponent();


    std::vector<Component*> m_toRemove;
    // TRANSFORM
    Transform *getTransform();
    Transform *m_transform;

protected:
    std::vector<Component*> m_components;


    void removeComponentToBeDestroyed();

    std::string m_name;
    int m_id;


};

#include "gameObject.inl"

#endif
