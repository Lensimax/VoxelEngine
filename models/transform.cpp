#include "transform.h"


Transform::Transform(){
    this->vecPosition = vec3(0.0,0.0,0.0);
    this->vecScale = vec3(1.0,1.0,1.0);
}

Transform::Transform(vec3 position){
    this->vecPosition = position;
    this->vecScale = vec3(1.0,1.0,1.0);
}

Transform::Transform(vec3 position, vec3 scale){
    this->vecPosition = position;
    this->vecScale = scale;
}


Transform::~Transform(){

}

void Transform::setPosition(vec3 position){
    this->vecPosition = position;
}
void Transform::rotate(vec3 axis, float angle){

}
void Transform::scale(vec3 scale){
    this->vecScale = scale;
}

mat4 Transform::getMat4(){
    mat4 model = mat4(1.0f);
    model = translate(model, vecPosition);
    model = glm::scale(model, vecScale);
    return model;
}
