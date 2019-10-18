#ifndef DIRECTIONNAL_LIGHT_H
#define DIRECTIONNAL_LIGHT_H

#include "light.h"
#include <string>

class DirectionnalLight : public Light {
    public:
        DirectionnalLight(int id, std::string name = "Directionnal Light", glm::vec3 l = glm::vec3(0.f,-1.0f,0.0f));

        virtual glm::vec3 getLight();

        void createUI(char *ID) override;

    private:
        glm::vec3 light;
};

#endif
