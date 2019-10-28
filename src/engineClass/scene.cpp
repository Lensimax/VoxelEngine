#include "scene.h"

#include "../tools/lights/directionnalLight.h"
#include "../tools/cameraProj.h"

#include "../models/meshObject.h"

#include "../models/plane.h"


Scene::Scene(){

    IDObject = 0;


    objectsEngine = std::vector<EngineObject*>();

    //
    // objectsEngine.push_back(new MeshObject("Object Loaded", (char*)"../data/models/suzanne.off", new Transform()));

    objectsEngine.push_back(new MeshObject("Object Loaded", (char*)"../data/models/suzanne.off", new Transform()));
    // objectsEngine.push_back(new Sphere());

    // objectsEngine.push_back(new Cube());

    objectsEngine.push_back(new Plane());



    Camera *cam = new CameraProj(addNewId());

    objectsEngine.push_back(cam);

    objectsEngine.push_back(new DirectionnalLight(addNewId(), "Light", glm::vec3(8, 0.0, 1)));

}

Scene::~Scene(){
    deleteScene();
}

void Scene::deleteScene(){
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        delete objectsEngine[i];
    }
}

Camera *Scene::getCamera(){
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        if(Camera* c = dynamic_cast<Camera*>(objectsEngine[i])) {
            return c;
        }
    }
    return NULL;
}

Light *Scene::getLight(){
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        if(Light* l = dynamic_cast<Light*>(objectsEngine[i])) {
            return l;
        }
    }
    return NULL;
}

void Scene::createUIAtID(int indexItem, char *ID){

    for(unsigned int i=0; i<objectsEngine.size(); i++){
        if(objectsEngine[i]->getID() == indexItem){
            objectsEngine[i]->createUI(ID);
            return;
        }
    }
}

void Scene::getAllObjects(std::vector<std::string> & names, std::vector<int> & ids){
    names.resize(objectsEngine.size());
    ids.resize(objectsEngine.size());


    for(unsigned int i=0; i<objectsEngine.size(); i++){
        names[i] = objectsEngine[i]->getName();
        ids[i] = objectsEngine[i]->getID();
    }

}


void Scene::addMeshObject(){
    objectsEngine.push_back(new MeshObject(addNewId()));
}

void Scene::addPlane(){
    objectsEngine.push_back(new Plane(addNewId()));
}

void Scene::addEngineObject(){
    objectsEngine.push_back(new EngineObject(addNewId()));
}



void Scene::deleteObject(int id){

    for(unsigned int i=0; i<objectsEngine.size(); i++){
        if(objectsEngine[i]->getID() == id){
            delete(objectsEngine[i]);
            objectsEngine.erase(objectsEngine.begin()+i);
            return;
        }
    }
}


int Scene::addNewId(){
    IDObject++;
    return IDObject-1;
}
