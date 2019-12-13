#include "scene.h"
#include "../engineClass/gameObject.h"

#include "../tools/lights/directionnalLight.h"
#include "../tools/cameraProj.h"

#include "../models/mesh/meshCube.h"

#include "../material/simpleMat.h"

#include "../material/textureMaterial.h"
#include "../components/meshRenderer.h"

#include "../components/component.h"
#include "../components/chunkRenderer.h"
#include "../components/cameraRenderer.h"

#include "../components/controller.h"

#include <iostream>


Scene::Scene(){

    loadDefaultScene();

    GameObject *obj = new GameObject(addNewId());

    // std::cerr << "ajout composent\n";
    obj->addComponent<ChunkRenderer*>(new ChunkRenderer());
    // std::cerr << "fin ajout composent\n";
    obj->addComponent<MeshRenderer*>(new MeshRenderer());
    obj->addComponent<Mesh*>(new MeshCube());
    obj->addComponent<Material*>(new Lambertian());
    obj->addComponent<Controller*>(new Controller());
 
    //MeshObject *obj = new MeshObject(addNewId(), "Cube", new Transform(), new MeshCube(0.5f), new Lambertian(glm::vec4(1,1,0,1)));
    objectsEngine.push_back(obj);

}

Scene::~Scene(){
    deleteScene();
}

void Scene::deleteScene(){
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        delete objectsEngine[i];
    }
}


Camera *Scene::getCameraRecursive(GameObject *obj){
    Camera *tmp = NULL;
    if(Camera* c = dynamic_cast<Camera*>(obj)) {
        return c;
    } else {
        if(obj->m_listOfChildren.size() == 0){
            return NULL;
        } else {
            for(unsigned int i=0; i<obj->m_listOfChildren.size(); i++){
                tmp = getCameraRecursive(obj->m_listOfChildren[i]);
                if(tmp != NULL){ return tmp;}
            }
        }
        return NULL;
    }
}

Camera *Scene::getCamera(){
    Camera *tmp = NULL;
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        tmp = getCameraRecursive(objectsEngine[i]);
        if(tmp != NULL){ return tmp;}
    }
    return NULL;
}

Light *Scene::getLight(){
    Light *tmp = NULL;
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        tmp = getLightRecursive(objectsEngine[i]);
        if(tmp != NULL){ return tmp;}
    }
    return NULL;
}

Light *Scene::getLightRecursive(GameObject *obj){
    Light *tmp = NULL;
    if(Light* l = dynamic_cast<Light*>(obj)) {
        return l;
    } else {
        if(obj->m_listOfChildren.size() == 0){
            return NULL;
        } else {
            for(unsigned int i=0; i<obj->m_listOfChildren.size(); i++){
                tmp = getLightRecursive(obj->m_listOfChildren[i]);
                if(tmp != NULL){ return tmp;}
            }
        }
        return NULL;
    }
}

void Scene::createUIAtID(int indexItem, char *ID){

    for(unsigned int i=0; i<objectsEngine.size(); i++){
        if(objectsEngine[i]->getID() == indexItem){
            objectsEngine[i]->createUI(ID);
            return;
        } else {
            drawUIAtID(objectsEngine[i]->m_listOfChildren, indexItem, ID);
        }
    }
}

void Scene::drawUIAtID(std::vector<GameObject*> objs, int indexItem, char *ID){
    for(unsigned int i=0; i<objs.size(); i++){
        if(objs[i]->getID() == indexItem){
            objs[i]->createUI(ID);
            return;
        } else {
            drawUIAtID(objs[i]->m_listOfChildren, indexItem, ID);
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

///// CREATION DE PREFABS

void Scene::addGameObject(){
    objectsEngine.push_back(new GameObject(addNewId()));
}

void Scene::addCube(){
    GameObject *cube = new GameObject(addNewId(), "Cube");

    cube->addComponent<MeshRenderer*>(new MeshRenderer());
    cube->addComponent<Mesh*>(new MeshCube());
    cube->addComponent<Material*>(new Lambertian());
 
    objectsEngine.push_back(cube);

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
    m_idObject++;
    return m_idObject-1;
}

void Scene::updateObj(GameObject *obj){
    obj->update();
    for(unsigned int i=0; i<obj->m_listOfChildren.size(); i++){
        updateObj(obj->m_listOfChildren[i]);
    }
}

void Scene::update(){
    if(!m_pause){
        for(unsigned int i=0; i<objectsEngine.size(); i++){
            updateObj(objectsEngine[i]);
        }
    }
}


void Scene::togglePause(){
    m_pause = !m_pause;
}


void Scene::loadDefaultScene(){
    m_pause = false;

    m_idObject = 0;

    objectsEngine = std::vector<GameObject*>();

    Camera *camera = new CameraProj(addNewId(), "Camera", glm::vec3(0,0,3));
    camera->addComponent<CameraRenderer*>(new CameraRenderer());

    objectsEngine.push_back(camera);

    objectsEngine.push_back(new DirectionnalLight(addNewId(), "Light", glm::vec3(0, 2.0, 2)));
}

