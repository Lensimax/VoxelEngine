#ifndef CUBE_H
#define CUBE_H



#include "../material/lambertian.h"

#include "meshObject.h"

#include <string>

class Cube : public MeshObject {
    public:

        Cube(std::string n = "Cube", Transform *t = new Transform(), Material *m = new Lambertian());
        ~Cube();

        void createUI(char *ID) override;

};

#endif
