#ifndef CAMERA_H
#define CAMERA_H


#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif


#include "../engineClass/engineObject.h"

class Camera : public EngineObject {


    public:
        virtual glm::mat4 getProj(float aspect = 16./9.) = 0;

        glm::mat4 getView();

        void update() override;
        
        virtual void createUI(char *ID) = 0;

    protected:
        void setAxis(glm::vec3 pos, glm::vec3 u, glm::vec3 dir);

        glm::vec3 getLeftDir();
        glm::vec3 getRightDir();
        void rotateAroundPoint(glm::vec2 v);

        glm::vec3 position, up, directionOfView;
        


};

#endif
