#ifndef CAMERA_PROJECTIVE_H
#define CAMERA_PROJECTIVE_H

#include "camera.h"


#include <string>


class CameraProj : public Camera {

    public:
        CameraProj(int id, std::string name = "Camera Projective", glm::vec3 pos = glm::vec3(0.0,0.0,5.0), glm::vec3 u = glm::vec3(0.0,1.0,0.0), glm::vec3 direction = glm::vec3(0.0,0.0,0.0), float fov = 45.f, float aspectP = 16.f/9.f, float n = 0.1f, float f = 100.f);


        virtual glm::mat4 getProj();

        virtual void createUI(char *ID);

    protected:

        float fovy;
        float aspect;
        float near;
        float far;

};

#endif
