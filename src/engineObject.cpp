

#include "engineObject.h"

#include <stdio.h>


void EngineObject::setName(std::string n){
    name = n;
}

std::string EngineObject::getName(){
    return name;
}
