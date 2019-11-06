#ifndef FILEMESHOBJECT_H
#define FILEMESHOBJECT_H

#include "../material/lambertian.h"
#include "mesh.h"
#include "meshObject.h"
#include <string>

const std::string defaultFilename = "../data/models/monkey.off";

class FileMeshObject : public MeshObject {
public:
    FileMeshObject(int id, std::string n = "MeshObject", char *filename = (char*)"../data/models/suzanne.off", Transform *t = new Transform(), Material *m = new Lambertian());
    ~FileMeshObject();

};

#endif
