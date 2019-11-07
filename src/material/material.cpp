#include "material.h"





void Material::sendUniform(GLuint shaderID, glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projMat){
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shaderID,"projMat"),1,GL_FALSE,&(projMat[0][0]));
}
