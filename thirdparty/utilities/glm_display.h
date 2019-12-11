#ifndef VOXEL_ENGINE_GLM_DISPLAY_H
#define VOXEL_ENGINE_GLM_DISPLAY_H


#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include <iostream>


std::ostream & operator<<(std::ostream & out, const glm::vec3& v){
    out << "{" << v.x << ", " << v.y << ", " << v.z << "}";
    return out;
}

std::ostream & operator<<(std::ostream & out, const glm::vec4& v){
    out << "{" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "}";
    return out;
}

std::ostream & operator<<(std::ostream & out, const glm::vec2& v){
    out << "{" << v.x << ", " << v.y << "}";
    return out;
}


std::ostream & operator<<(std::ostream & out, const glm::mat4& matrix){

    for(unsigned int i=0; i<4; i++){
        out << "[" << matrix[i][0] << ", " << matrix[i][1] << ", " << matrix[i][2] << ", " << matrix[i][3] << "]\n";
    }

    return out;
}


std::ostream & operator<<(std::ostream & out, const glm::mat3& matrix){

    for(unsigned int i=0; i<3; i++){
        out << "[" << matrix[i][0] << ", " << matrix[i][1] << ", " << matrix[i][2] << "]\n";
    }

    return out;
}

#endif