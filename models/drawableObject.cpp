#include "drawableObject.h"

#include <stdio.h>

Transform *DrawableObject::getTransform(){
    return transform;
}

void DrawableObject::setName(std::string n){
    name = n;
}
