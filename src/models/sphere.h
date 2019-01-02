#ifndef SPHERE_H
#define SPHERE_H

#include "drawableObject.h"

#include "../material/lambertian.h"
#include "../models/mesh.h"
#include "../models/meshObject.h"

#include <vector>

class Sphere : public MeshObject {
    public:
        Sphere(std::string n = "Sphere", float radius = 1.0f, unsigned int rings = 12, unsigned int sectors = 24,
            Transform *t = new Transform(), Material *m = new Lambertian());

        ~Sphere();

        void createUI(char *ID) override;


};


#endif
