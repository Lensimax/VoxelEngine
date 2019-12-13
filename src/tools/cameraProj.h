#ifndef CAMERA_PROJECTIVE_H
#define CAMERA_PROJECTIVE_H

#include "camera.h"


#include <string>


class CameraProj : public Camera {

    public:
        CameraProj(int id, std::string name = "Camera Projective", Transform *transform = new Transform(glm::vec3(0), glm::vec3(0,1,3), glm::vec3(1), glm::vec3()), float fov = 45.f, float n = 0.1f, float f = 1000.f);


        virtual glm::mat4 getProj(float aspect = 16./9.);

        void createUI(char *ID) override final;

    protected:

        float m_fovy;
        float m_near;
        float m_far;

};

#endif
