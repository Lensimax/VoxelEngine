#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>

class GameObject;


class Component {
public:


    virtual void start(){};

    virtual void update(){};

    virtual void createUI(){};


    bool getActive(){return m_active;}
    void setActive(bool active){m_active = active;}

    void setGameObject(GameObject * obj){m_gameobject = obj;}

protected:

    GameObject *m_gameobject;

    // TODO use it
    bool m_active = true;

};

#endif