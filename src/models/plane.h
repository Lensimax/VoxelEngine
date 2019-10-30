#ifndef PLANE_H
#define PLANE_H


#include "../material/lambertian.h"

#include "meshGrid.h"
#include "meshObject.h"


class Plane : public MeshObject {
public:

    Plane(int id,std::string n = "Plane", unsigned int size = 16, float width = 1, float gridZ = 0, Transform *t = new Transform(), Material *m = new Lambertian());
    ~Plane();


private:


};


#endif
