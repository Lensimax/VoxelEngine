#ifndef ENGINE_OBJECT_INL
#define ENGINE_OBJECT_INL

// #include "gameObject.h"

template< class ComponentType> ComponentType  GameObject::getComponent(){
    for ( Component * component : m_components ) {
        if ( ComponentType o = dynamic_cast<ComponentType>(component) ){
            return o;
        }
    }

    return NULL;
}


template< class ComponentType > bool GameObject::removeComponent() {
    if(m_components.empty()){
        return false; 
    }

    
    for (unsigned int i=0; i<m_components.size(); i++ ) {
         
        if ( ComponentType o = dynamic_cast<ComponentType>(m_components[i]) ){
            m_components.erase(m_components.begin()+i);
            return true;
        }
    }

    return false;
}

template< class ComponentType > void GameObject::addComponent(Component * component) {
    if(!getComponent<ComponentType>()){
        m_components.push_back(component);
        component->setGameObject(this);
    }
}


template< class ComponentType> void GameObject::addComponent(){
    if(!getComponent<ComponentType>()){
        Component * comp = new ComponentType();
        m_components.push_back(comp);
        comp->setGameObject(this);
    }
}
 
#endif