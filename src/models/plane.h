#ifndef PLANE_H
#define PLANE_H


#include "../material/lambertian.h"

#include "meshGrid.h"
#include "meshObject.h"


class Plane : public MeshObject {
public:

    Plane(int id,std::string n = "Plane", Transform *t = new Transform(), Material *m = new Lambertian(), MeshGrid *meshG = new MeshGrid());
    ~Plane();


private:


};


#endif
