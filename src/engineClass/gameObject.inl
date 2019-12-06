#ifndef ENGINE_OBJECT_INL
#define ENGINE_OBJECT_INL

// #include "gameObject.h"

template< class ComponentType> Component * GameObject::getComponent(){
    for ( Component * component : m_components ) {
        if ( ComponentType* o = dynamic_cast<ComponentType*>(component) ){
            return component;
        }
    }

    return NULL;
}


template< class ComponentType > bool GameObject::removeComponent() {
    if(m_components.empty()){
        return false; 
    }

    
    for (unsigned int i=0; i<m_components.size(); i++ ) {
         
        if ( ComponentType* o = dynamic_cast<ComponentType*>(m_components[i]) ){
            m_components.erase(m_components.begin()+i);
            return true;
        }
    }

    return false;
}
 
#endif