#ifndef GLMCOUT_H
#define GLMCOUT_H

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

#include <iostream>

class GLMCOUT {
public:  
    static void printMat(glm::mat4 matrix){
        for(unsigned int i=0; i<4; i++){
            std::cout << "[" << matrix[i][0] << ", " << matrix[i][1] << ", " << matrix[i][2] << ", " << matrix[i][3] << "]\n";
        }
    }

    static void printVec(glm::vec3 v){
        std::cout << "{" << v.x << ", " << v.y << ", " << v.z << "}";
    }

    static void printVec(glm::vec4 v){
        std::cout << "{" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "}";
    }
};

#endif