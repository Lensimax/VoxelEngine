#include "scene.h"

#include "../tools/lights/directionnalLight.h"
#include "../tools/cameraProj.h"

#include "../models/fileMeshObject.h"

#include "../models/plane.h"

#include "../material/simpleMat.h"


Scene::Scene(){

    pause = false;

    IDObject = 0;


    objectsEngine = std::vector<EngineObject*>();

    Transform *EarthTransform =  new Transform(glm::vec3(0),glm::vec3(-2.5,0,0), glm::vec3(0.5), glm::vec3(0));
    Transform *MoonTransform = new Transform(glm::vec3(0),glm::vec3(0.9,0,0), glm::vec3(0.2), glm::vec3(0));

    FileMeshObject *Sun = new FileMeshObject(addNewId(),"Sun", (char*)"../data/models/sphere.off", new Transform(), new SimpleMat());
    FileMeshObject *Earth = new FileMeshObject(addNewId(),"Earth", (char*)"../data/models/sphere.off", EarthTransform, new Lambertian(glm::vec4(0.,0.,1.,1.)));
    FileMeshObject *Moon = new FileMeshObject(addNewId(),"Moon", (char*)"../data/models/sphere.off", MoonTransform , new Lambertian(glm::vec4(0.1,0.1,0.1,1.0)));

    Sun->addChild(Earth);
    Earth->addChild(Moon);

    objectsEngine.push_back(Sun);


    //// SET ANIMATION OF SOLAR SYSTEM
    Sun->getTransform()->setSameMatrixAsParent(false);
    Earth->getTransform()->setSameMatrixAsParent(false);
    Earth->getTransform()->setChildAnimation(false,true,false, 0.,-0.05,0.);
    Sun->getTransform()->setChildAnimation(false, true, false);



    // FileMeshObject *obj2 = new FileMeshObject(addNewId(),"Object Loaded", (char*)"../data/models/sphere.off", new Transform());
    // obj2->addChild(new FileMeshObject(addNewId(),"Sphere", (char*)"../data/models/sphere.off", new Transform(glm::vec3(0),glm::vec3(-2.5,0,0))));
    // objectsEngine.push_back(obj2);

    // objectsEngine.push_back(new Sphere());

    // objectsEngine.push_back(new Cube());

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
        } else {
            drawUIAtID(objectsEngine[i]->listOfChildren, indexItem, ID);
        }
    }
}

void Scene::drawUIAtID(std::vector<EngineObject*> objs, int indexItem, char *ID){
    for(unsigned int i=0; i<objs.size(); i++){
        if(objs[i]->getID() == indexItem){
            objs[i]->createUI(ID);
            return;
        } else {
            drawUIAtID(objs[i]->listOfChildren, indexItem, ID);
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
    objectsEngine.push_back(new FileMeshObject(addNewId()));
}

void Scene::addPlane(){
    objectsEngine.push_back(new Plane(addNewId()));
}

void Scene::addEngineObject(){
    objectsEngine.push_back(new EngineObject(addNewId()));
}

void Scene::addSphere(){
    objectsEngine.push_back(new FileMeshObject(addNewId(), "Sphere", (char*)"../data/models/sphere.off"));
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

void Scene::updateObj(EngineObject *obj){
    obj->update();
    for(unsigned int i=0; i<obj->listOfChildren.size(); i++){
        updateObj(obj->listOfChildren[i]);
    }
}

void Scene::update(){
    if(!pause){
        for(unsigned int i=0; i<objectsEngine.size(); i++){
            updateObj(objectsEngine[i]);
        }
    }
}


void Scene::togglePause(){
    pause = !pause;
}
