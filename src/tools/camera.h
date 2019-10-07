#ifndef CAMERA_H
#define CAMERA_H


#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#endif


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
