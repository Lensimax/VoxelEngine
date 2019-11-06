#include "fileMeshObject.h"
#include "meshLoader.h"

FileMeshObject::FileMeshObject(int id, std::string n, char *filename, Transform *t, Material *m){
    transform = t;

    mesh = new MeshLoader(filename);

    glm::vec3 center = mesh->getCenter();
    t->setCenter(center);

    createVAO();

    material = m;

    setName(n);
    setID(id);

}


FileMeshObject::~FileMeshObject(){
    deleteVAO();
    delete transform;
    delete material;
    delete mesh;
}
