#include "scene.h"
#include "../engineClass/gameObject.h"

#include "../tools/lights/directionnalLight.h"

#include "../models/mesh/meshCube.h"

#include "../material/simpleMat.h"

#include "../material/textureMaterial.h"
#include "../components/meshRenderer.h"

#include "../components/component.h"
// #include "../components/chunkRenderer.h"
#include "../components/axisRenderer.h"
#include "../terrain/terrainManager.h"

#include "../components/rigidbody.h"
#include "../components/cameraProjective.h"
#include "../components/cameraRenderer.h"
#include "../components/cameraFollow.h"
#include "../components/thirdPersonController.h"
#include "../components/groundFollow.h"
#include "../components/fireProjectiles.h"
#include "../components/debug/debugTransform.h"
#include "../components/colliders/collider.h"

#include <thread>


#include <iostream>

#define M_PI 3.14159265359


Scene::Scene(){

    loadDefaultScene();


    

    GameObject *player = new GameObject(addNewId(), "Player", new Transform(glm::vec3(2.8f,32.5f,33.7f)));
    player->addComponent<Mesh*>(new MeshCube(0.5f));
    player->addComponent<Material*>(new Lambertian());
    player->addComponent<MeshRenderer*>(new MeshRenderer());
    player->addComponent<Rigidbody*>(new Rigidbody());
    player->addComponent<AxisRenderer*>(new AxisRenderer());
    player->addComponent<ThirdPersonController*>(new ThirdPersonController());
    //player->addComponent<GroundFollow*>(new GroundFollow());
    player->addComponent<FireProjectiles*>(new FireProjectiles()); // ça fait rammer mon pc à mort ! O_o
    player->getComponent<FireProjectiles*>()->setScene(this);
    player->getComponent<FireProjectiles*>()->setActive(false);
    player->addComponent<DebugTransform*>(new DebugTransform());
    player->addComponent<Collider*>(new Collider());
    objectsEngine.push_back(player);

    GameObject *terrain = new GameObject(addNewId(), "Terrain");
    terrain->addComponent<TerrainManager*>(new TerrainManager(32, 5, player->getTransform()));
    objectsEngine.push_back(terrain);
  

    player->getComponent<Collider*>()->setTerrain(terrain->getComponent<TerrainManager*>());

    GameObject *origin = new GameObject(addNewId(), "Origin", new Transform(glm::vec3()));
    origin->addComponent<Mesh*>(new MeshCube(0.5f));
    origin->addComponent<Material*>(new Lambertian());
    origin->getComponent<Lambertian*>()->toggleDisplayDiffuse();
    origin->addComponent<MeshRenderer*>(new MeshRenderer());
    objectsEngine.push_back(origin);

    GameObject *uno = new GameObject(addNewId(), "One", new Transform(glm::vec3(1,0,0)));
    uno->addComponent<Mesh*>(new MeshCube(0.5f));
    uno->addComponent<Material*>(new Lambertian(glm::vec4(0,1,0,1)));
    uno->getComponent<Lambertian*>()->toggleDisplayDiffuse();
    uno->addComponent<MeshRenderer*>(new MeshRenderer());
    objectsEngine.push_back(uno);
    

    GameObject *camera = new GameObject(addNewId(), "Camera", new Transform(glm::vec3(0,164, 0), glm::vec3(M_PI / 2 - 0.3, M_PI, 0)));
    camera->addComponent<CameraProjective*>(new CameraProjective());
    CameraFollow* camFoll = new CameraFollow();
    camera->addComponent<CameraFollow*>(camFoll);
    camFoll->setPlayer(player);

    player->getComponent<ThirdPersonController*>()->setCamera(camera);
    // player->getComponent<ThirdPersonController*>()->setActive(false);
    // player->getComponent<GroundFollow*>()->setTerrain(terrain->getComponent<TerrainManager*>());
    
    
    objectsEngine.push_back(camera);
}

Scene::~Scene(){
    deleteScene();
}

void Scene::deleteScene(){
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        delete objectsEngine[i];
    }
}

CameraProjective * Scene::getCamera(){
    CameraProjective* tmp;
    tmp = NULL;
    for(unsigned int i=0; i<objectsEngine.size(); i++){
        tmp = getCameraRecursive(objectsEngine[i], glm::mat4(1));
        if(tmp != NULL){ return tmp;}
    }
    return tmp;
}

CameraProjective * Scene::getCameraRecursive(GameObject *obj, glm::mat4 modelMat){
    CameraProjective * tmp;
    tmp = NULL;
    if(CameraProjective* c = obj->getComponent<CameraProjective*>()) {
        return c;
    } else {
        if(obj->m_listOfChildren.size() == 0){
            return NULL;
        } else {
            modelMat = obj->getTransform()->getModelToChild(modelMat);
            for(unsigned int i=0; i<obj->m_listOfChildren.size(); i++){
                tmp = getCameraRecursive(obj->m_listOfChildren[i], modelMat);
                if(tmp != NULL){ return tmp;}
            }
        }
        return NULL;
    }
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


void Scene::addGameObject(GameObject *obj){
    objectsEngine.push_back(obj);
}

void Scene::addCube(){
    GameObject *cube = new GameObject(addNewId(), "Cube");

    cube->addComponent<Mesh*>(new MeshCube());
    cube->addComponent<Material*>(new Lambertian());
    cube->addComponent<MeshRenderer*>(new MeshRenderer());
 
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
    // std::thread threadUpdate(&GameObject::update, obj);
    for(unsigned int i=0; i<obj->m_listOfChildren.size(); i++){
        updateObj(obj->m_listOfChildren[i]);
    }
    // threadUpdate.join();
}

void Scene::update(){
    if(!m_pause){
        for(unsigned int i=0; i<objectsEngine.size(); i++){
            updateObj(objectsEngine[i]);
        }
    }
}

void Scene::inputUpdateObj(GameObject *obj){
    obj->inputUpdate();
    for(unsigned int i=0; i<obj->m_listOfChildren.size(); i++){
        inputUpdateObj(obj->m_listOfChildren[i]);
    }
}

void Scene::inputUpdate(){
    if(!m_pause){
        for(unsigned int i=0; i<objectsEngine.size(); i++){
            inputUpdateObj(objectsEngine[i]);
        }
    }
}

void Scene::physicsUpdate(){
    if(!m_pause){
        for(unsigned int i=0; i<objectsEngine.size(); i++){
            physicsUpdateObj(objectsEngine[i]);
        }
    }
}

void Scene::physicsUpdateObj(GameObject *obj){
    obj->physicsUpdate();
    // std::thread threadUpdate(&GameObject::update, obj);
    for(unsigned int i=0; i<obj->m_listOfChildren.size(); i++){
        physicsUpdateObj(obj->m_listOfChildren[i]);
    }
    // threadUpdate.join();
}


void Scene::togglePause(){
    m_pause = !m_pause;
}


void Scene::loadDefaultScene(){
    m_pause = false;
    m_idObject = 0;
    objectsEngine = std::vector<GameObject*>();
    objectsEngine.push_back(new DirectionnalLight(addNewId(), "Light", glm::vec3(0, 128, 0)));
}

