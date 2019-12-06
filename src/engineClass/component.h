#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>
#include <vector>

//#include "gameObject.h"

class Component {
public:

    static const std::size_t m_type = 0;
    bool isClassType( const std::size_t classType ) const { return classType == m_type; };

    virtual void start(){};

    virtual void update(){};

    virtual void createUI(){};


    bool getActive(){return m_active;}
    void setActive(bool active){m_active = active;}

protected:

    //GameObject m_gameobject;

    // TODO use it
    bool m_active = true;

};

#endif