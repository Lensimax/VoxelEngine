#include "collider.h"


#include "../../engineClass/gameObject.h"

#include <imgui.h>
#include <drawDebug.h>

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif


Collider::Collider(glm::vec3 box) : m_collidingBox(box), m_showCollidingBox(true), m_showCheckCollision(true) {
    setName("Collider");
    m_targetHitPoint = glm::vec3(0);
}

Collider::~Collider() {
    
}

void Collider::start(){
    m_rb = m_gameobject->getComponent<Rigidbody*>();
    assert(m_rb != nullptr);
    computeCollisionWithGround();
}

bool Collider::intersect(glm::vec3 boxMin, glm::vec3 boxMax) {
    return intersect(m_boxMin, m_boxMax, boxMin, boxMax);
}

bool Collider::intersect(glm::vec3 box1Min, glm::vec3 box1Max, glm::vec3 box2Min, glm::vec3 box2Max) {
    return (box1Min.x <= box2Max.x && box1Max.x >= box2Min.x) &&
        (box1Min.y <= box2Max.y && box1Max.y >= box2Min.y) &&
        (box1Min.z <= box2Max.z && box1Max.z >= box2Min.z);
}

bool Collider::intersectAccordingToMove(glm::vec3 boxMin, glm::vec3 boxMax) {
    assert(m_rb != nullptr);
    glm::vec3 objMin = m_boxMin;
    objMin.y -= m_rb->getMass();
    glm::vec3 objMax = m_boxMax;
    return intersect(objMin, objMax, boxMin, boxMax);
    
}


void Collider::computeCollisionWithGround(){
    if(m_terrain != nullptr){
        // m_boxMin -= m_rb->getMass()*2.0f;

        if(m_terrain->getVoxelAt(m_boxMin) == Voxel::Full){
            m_isGrounded = true; return;
        }
        if(m_terrain->getVoxelAt(glm::vec3(m_boxMin.x, m_boxMin.y, m_boxMax.z)) == Voxel::Full){
            m_isGrounded = true; return;
        }
        if(m_terrain->getVoxelAt(glm::vec3(m_boxMax.x, m_boxMin.y, m_boxMax.z)) == Voxel::Full){
            m_isGrounded = true; return;
        }
        if(m_terrain->getVoxelAt(glm::vec3(m_boxMax.x, m_boxMin.y, m_boxMin.z)) == Voxel::Full){
            m_isGrounded = true; return;
        }
    }

    m_isGrounded = false;    

}

void Collider::updateCollidingBox(){
    glm::vec3 position = m_gameobject->getTransform()->getPosition();

    m_boxMin = glm::vec3(-m_collidingBox/2.0f)*m_gameobject->getTransform()->getScale();
    m_boxMax = glm::vec3(m_collidingBox/2.0f)*m_gameobject->getTransform()->getScale();

    m_boxMin += position; m_boxMax += position;

    assert(m_rb != nullptr);
    if(m_rb->getActive()){
        glm::vec3 move = m_rb->getMove();
        // move *= m_rb->getSpeed();
        move.x *=m_rb->getSpeed();
        move.z *=m_rb->getSpeed();
        if(move.x > 0){ m_boxMax.x += move.x;}
        else {m_boxMin.x += move.x;}
        if(move.y > 0){ m_boxMax.y += move.y;}
        else {m_boxMin.y += move.y;}
        if(move.z > 0){ m_boxMax.z += move.z;}
        else {m_boxMin.z += move.z;}
    }

}

glm::vec3 Collider::computeCollision(){

    if(m_terrain->getVoxelAt(m_boxMax) == Voxel::Full){
        return m_boxMax;
    }
    if(m_terrain->getVoxelAt(glm::vec3(m_boxMin.x, m_boxMax.y, m_boxMax.z)) == Voxel::Full){
        return glm::vec3(m_boxMin.x, m_boxMax.y, m_boxMax.z);
    }
    if(m_terrain->getVoxelAt(glm::vec3(m_boxMin.x, m_boxMax.y, m_boxMin.z)) == Voxel::Full){
        return glm::vec3(m_boxMax.x, m_boxMax.y, m_boxMax.z);
    }
    if(m_terrain->getVoxelAt(glm::vec3(m_boxMax.x, m_boxMax.y, m_boxMin.z)) == Voxel::Full){
        return glm::vec3(m_boxMax.x, m_boxMax.y, m_boxMin.z);
    }
    return glm::vec3(0);
}

void Collider::physicsUpdate() {
    assert(m_rb != nullptr);
    updateCollidingBox();
    if(m_terrain == nullptr){ return;}

    if(m_rb->getActive() && m_rb->useGravity()){
        computeCollisionWithGround();
    }

    if(computeCollision() != glm::vec3(0)){
        if(m_rb != nullptr && m_rb->getActive()){
            glm::vec3 move = m_rb->getMove();
            move.x = 0.0f; move.z = 0.0f;
            m_rb->setMove(move);
        }
    }

    /// TEST
    raycast();

}

glm::vec2 intersectQuadLine(glm::vec2 A, glm::vec2 B, glm::vec2 Rect0, glm::vec2 Rect1){
    
    glm::vec2 AB = B - A;
    glm::vec2 interPoint;

    if (AB.x < 0) {
        if (AB.y < 0) {
            if ((AB.x * (Rect0.y - A.y) - AB.y * (Rect0.x - A.x)) > 0) {
                interPoint.x = Rect0.x;
                interPoint.y = ((interPoint.x - A.x) * AB.y / AB.x) + A.y;
            } else {
                interPoint.y = Rect0.y;
                interPoint.x = ((interPoint.y - A.y) * AB.x / AB.y) + A.x;
            }
        }
        else {
            if ((AB.x * (Rect1.y - A.y) - AB.y * (Rect0.x - A.x)) < 0) {
                interPoint.x = Rect0.x;
                interPoint.y = ((interPoint.x - A.x) * AB.y / AB.x) + A.y;
            } else {
                interPoint.y = Rect1.y;
                interPoint.x = ((interPoint.y - A.y) * AB.x / AB.y) + A.x;
            }
        }
    }
    else {
        if (AB.y < 0) {
            if ((AB.x * (Rect0.y - A.y) - AB.y * (Rect1.x - A.x)) < 0) {
                interPoint.x = Rect1.x;
                interPoint.y = ((interPoint.x - A.x) * AB.y / AB.x) + A.y;
            } else {
                interPoint.y = Rect0.y;
                interPoint.x = ((interPoint.y - A.y) * AB.x / AB.y) + A.x;
            }
        }
        else {
            if ((AB.x * (Rect1.y - A.y) - AB.y * (Rect1.x - A.x)) > 0) {
                interPoint.x = Rect1.x;
                interPoint.y = ((interPoint.x - A.x) * AB.y / AB.x) + A.y;
            } else {
                interPoint.y = Rect1.y;
                interPoint.x = ((interPoint.y - A.y) * AB.x / AB.y) + A.x;
            }
        }
    }
    return interPoint;
}


void Collider::raycast(){
    m_targetHitPoint = m_gameobject->getTransform()->getPosition();
    glm::vec3 rotation = m_gameobject->getTransform()->getRotation();
    float dx = glm::cos(rotation.y);
    float dz = glm::sin(rotation.y);

    const float length = 1.0f;

    m_targetHitPoint.z += length * dx;
    m_targetHitPoint.x += length * dz;
    
    if(m_terrain->getVoxelAt(m_targetHitPoint) == Voxel::Full){ // collision

    }

}

void Collider::createUI() {
    glm::vec3 position = m_gameobject->getTransform()->getPosition();
    ImGui::Text("Box Collider: ");
    ImGui::DragFloat3("##boxCollider", &m_collidingBox[0], 0.01f, 0.01f, 10.f, "%.3f");

    ImGui::Text("Min: (%f, %f, %f)", m_boxMin.x, m_boxMin.y, m_boxMin.z);
    ImGui::Text("Max: (%f, %f, %f)", m_boxMax.x, m_boxMax.y, m_boxMax.z);

    ImGui::Separator();
    ImGui::Text("Position: (%f, %f, %f)", position.x, position.y, position.z);
    glm::vec3 testCast = m_targetHitPoint - position;
    ImGui::Text("Vector ray: (%f, %f, %f)", testCast.x, testCast.y, testCast.z);
    ImGui::Text("Length: %f",glm::distance(m_targetHitPoint, position));
    ImGui::Separator();

    if(m_terrain != nullptr){
        


        glm::vec3 boxMin = m_gameobject->getTransform()->getPosition() + m_boxMin;
        glm::vec3 chunk_coord = m_terrain->toChunkGridCoord(boxMin) * glm::ivec3(m_terrain->getChunkSize()); 
        glm::vec3 voxelCoordGrid = m_terrain->toVoxelCoordInChunk(boxMin);

        ImGui::Text("chunk coord : (%f, %f, %f)", chunk_coord.x, chunk_coord.y, chunk_coord.z);
        ImGui::Text("voxel coord : (%f, %f, %f)", voxelCoordGrid.x, voxelCoordGrid.y, voxelCoordGrid.z);

    }

    ImGui::Text("Show colliding box "); ImGui::SameLine();
    ImGui::Checkbox("##showColliding",&m_showCollidingBox);
    ImGui::Text("Show collisions check "); ImGui::SameLine();
    ImGui::Checkbox("##checkCollision",&m_showCheckCollision);
}




void Collider::displayImGuiVoxel(Voxel voxel, const char message[]) {
    if(voxel == Voxel::Empty){
        ImGui::Text("%s : Empty", message);
    } else {
        ImGui::Text("%s : Full", message);
    }    
}

void Collider::draw(glm::mat4 modelMat, glm::mat4 viewMat, glm::mat4 projectionMat, Light *light) {
    glm::vec3 position = m_gameobject->getTransform()->getPosition();
    if(!m_showCollidingBox){
        return;
    }

    const float lineWidth = 0.2f;

    // pour enlever la rotation sur la matric model
    modelMat[0][0] = 1; modelMat[1][1] = 1; modelMat[2][2] = 1; 
    modelMat[0][1] = 0; modelMat[0][2] = 0;
    modelMat[1][0] = 0; modelMat[1][2] = 0;
    modelMat[2][0] = 0; modelMat[2][1] = 0;

    glLineWidth(lineWidth);

    Shader shader = Shader();
    shader.load("../data/shaders/simple.vert","../data/shaders/simple.frag");
    glUseProgram(shader.id());
    
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"modelMat"),1,GL_FALSE,&(glm::mat4(1.0f)[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"projMat"),1,GL_FALSE,&(projectionMat[0][0]));

    // affichage des voxels à check pour les collisions
    if(m_terrain != nullptr && m_showCheckCollision){

        // Intersection with ground
        // glm::vec3 voxel1 = m_terrain->toVoxelWorldCoord(m_boxMin + glm::vec3(-1,0,0));
        /*glm::vec3 voxelBottom1 = m_terrain->toVoxelWorldCoord(m_boxMin);
        glm::vec3 voxelBottom2 = m_terrain->toVoxelWorldCoord(glm::vec3(m_boxMin.x, m_boxMin.y, m_boxMax.z));
        glm::vec3 voxelBottom3 = m_terrain->toVoxelWorldCoord(glm::vec3(m_boxMax.x, m_boxMin.y, m_boxMax.z));
        glm::vec3 voxelBottom4 = m_terrain->toVoxelWorldCoord(glm::vec3(m_boxMax.x, m_boxMin.y, m_boxMin.z));

        // drawAABB(voxel1, voxel1+1.0f, shader, glm::vec4(0,0,1,1));
        drawAABB(voxelBottom1, voxelBottom1+1.0f, shader, m_terrain->getVoxelAt(m_boxMin) == Voxel::Full ? glm::vec4(1,0,0,1) : glm::vec4(0,0,1,1));
        drawAABB(voxelBottom2, voxelBottom2+1.0f, shader, m_terrain->getVoxelAt(glm::vec3(m_boxMin.x, m_boxMin.y, m_boxMax.z)) == Voxel::Full ? glm::vec4(1,0,0,1) : glm::vec4(0,0,1,1));
        drawAABB(voxelBottom3, voxelBottom3+1.0f, shader, m_terrain->getVoxelAt(glm::vec3(m_boxMax.x, m_boxMin.y, m_boxMax.z)) == Voxel::Full ? glm::vec4(1,0,0,1) : glm::vec4(0,0,1,1));
        drawAABB(voxelBottom4, voxelBottom4+1.0f, shader, m_terrain->getVoxelAt(glm::vec3(m_boxMax.x, m_boxMin.y, m_boxMin.z)) == Voxel::Full ? glm::vec4(1,0,0,1) : glm::vec4(0,0,1,1));

        // Intersection pour le mouvement du joueur
        glm::vec3 voxel1 = m_terrain->toVoxelWorldCoord(m_boxMax);
        glm::vec3 voxel2 = m_terrain->toVoxelWorldCoord(glm::vec3(m_boxMin.x, m_boxMax.y, m_boxMax.z));
        glm::vec3 voxel3 = m_terrain->toVoxelWorldCoord(glm::vec3(m_boxMin.x, m_boxMax.y, m_boxMin.z));
        glm::vec3 voxel4 = m_terrain->toVoxelWorldCoord(glm::vec3(m_boxMax.x, m_boxMax.y, m_boxMin.z));

        drawAABB(voxel1, voxel1+1.0f, shader, m_terrain->getVoxelAt(m_boxMax) == Voxel::Full ? glm::vec4(1,0,0,1) : glm::vec4(0,0,1,1));
        drawAABB(voxel2, voxel2+1.0f, shader, m_terrain->getVoxelAt(glm::vec3(m_boxMin.x, m_boxMax.y, m_boxMax.z)) == Voxel::Full ? glm::vec4(1,0,0,1) : glm::vec4(0,0,1,1));
        drawAABB(voxel3, voxel3+1.0f, shader, m_terrain->getVoxelAt(glm::vec3(m_boxMin.x, m_boxMax.y, m_boxMin.z)) == Voxel::Full ? glm::vec4(1,0,0,1) : glm::vec4(0,0,1,1));
        drawAABB(voxel4, voxel4+1.0f, shader, m_terrain->getVoxelAt(glm::vec3(m_boxMax.x, m_boxMax.y, m_boxMin.z)) == Voxel::Full ? glm::vec4(1,0,0,1) : glm::vec4(0,0,1,1));
        */

       glUniform4fv(glGetUniformLocation(shader.id(),"color"), 1, &glm::vec4(1,0,1,1)[0]);
       glm::vec3 array[2];
       array[0] = m_gameobject->getTransform()->getPosition();
       array[1] = m_targetHitPoint; 
       DrawDebug::drawArrayPosition(2, (float*)&array[0], GL_LINES);
    }

    drawAABB(m_boxMin, m_boxMax, shader);


    glUseProgram(0);

}


void Collider::drawAABB(glm::vec3 min, glm::vec3 max, Shader shader, glm::vec4 color){
    glUniform4fv(glGetUniformLocation(shader.id(),"color"), 1, &color[0]);


    std::vector<glm::vec3> arrayAxis;
    arrayAxis.resize(24);
    // face du dessus
    arrayAxis[0] = glm::vec3(min.x, max.y, max.z);
    arrayAxis[1] = glm::vec3(max.x, max.y, max.z);
    arrayAxis[2] = glm::vec3(max.x, max.y, max.z);
    arrayAxis[3] = glm::vec3(max.x, max.y, min.z);
    arrayAxis[4] = glm::vec3(max.x, max.y, min.z);
    arrayAxis[5] = glm::vec3(min.x, max.y, min.z);
    arrayAxis[6] = glm::vec3(min.x, max.y, min.z);
    arrayAxis[7] = glm::vec3(min.x, max.y, max.z);
    // face du dessous
    arrayAxis[8] = glm::vec3(min.x, min.y, max.z);
    arrayAxis[9] = glm::vec3(max.x, min.y, max.z);
    arrayAxis[10] = glm::vec3(max.x, min.y, max.z);
    arrayAxis[11] = glm::vec3(max.x, min.y, min.z);
    arrayAxis[12] = glm::vec3(max.x, min.y, min.z);
    arrayAxis[13] = glm::vec3(min.x, min.y, min.z);
    arrayAxis[14] = glm::vec3(min.x, min.y, min.z);
    arrayAxis[15] = glm::vec3(min.x, min.y, max.z);
    // reliure des 2 faces
    arrayAxis[16] = glm::vec3(min.x, max.y, max.z);
    arrayAxis[17] = glm::vec3(min.x, min.y, max.z);

    arrayAxis[18] = glm::vec3(max.x, max.y, max.z);
    arrayAxis[19] = glm::vec3(max.x, min.y, max.z);

    arrayAxis[20] = glm::vec3(max.x, max.y, min.z);
    arrayAxis[21] = glm::vec3(max.x, min.y, min.z);

    arrayAxis[22] = glm::vec3(min.x, max.y, min.z);
    arrayAxis[23] = glm::vec3(min.x, min.y, min.z);

    DrawDebug::drawArrayPosition(arrayAxis.size(), (float*)&arrayAxis[0], GL_LINES);

}
