#ifndef COMPONENT_H
#define COMPONENT_H

#include "gameObject.h"

class Component {
public:

    virtual void start(){};

    virtual void update(){};

    virtual void createUI(){};

    template<class TYPE>
    TYPE* GetComponent();

    bool getActive(){return m_active;}
    void setActive(bool active){m_active = active;}

protected:

    GameObject m_gameobject;

    // TODO use it
    bool m_active = true;

};

#endif