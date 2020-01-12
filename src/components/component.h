#ifndef COMPONENT_H
#define COMPONENT_H

#include <cstring>
#include <vector>

class GameObject;


class Component {
public:
    virtual ~Component() = default;

    virtual void start(){}

    virtual void update(){}
    virtual void inputUpdate(){}
    virtual void physicsUpdate(){}

    virtual void createUI(){}


    bool getActive(){return m_active;}
    void setActive(bool active){m_active = active;}
    const char* getName(){return m_name;}
    void setName(const char* name){strncpy(m_name, name, 2048);};


    void setGameObject(GameObject * obj){m_gameobject = obj;}
    GameObject* getGameObject(){return m_gameobject;}

    bool m_active = true;


protected:

    GameObject *m_gameobject;
    char m_name[2048] = "Untitled Component";


};

#endif