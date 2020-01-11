#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
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
    char* getName(){return m_name;}
    void setName(char name[2048]){sprintf(m_name, name);};


    void setGameObject(GameObject * obj){m_gameobject = obj;}

    bool m_active = true;


protected:

    GameObject *m_gameobject;
    char m_name[2048] = "Untitled Component";


};

#endif