#ifndef CAMERA_H
#define CAMERA_H



#include <glm/mat4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>



#include "../engineObject.h"

class Camera : public EngineObject {


    public:
        virtual glm::mat4 getProj() = 0;

        glm::mat4 getView();

    protected:
        void setAxis(glm::vec3 pos, glm::vec3 u, glm::vec3 dir);

        glm::vec3 position, up, directionOfView;


};

#endif
