#include "collider.h"


#include "../../engineClass/gameObject.h"
#include "../rigidbody.h"

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


Collider::Collider(glm::vec3 box) : m_collidingBox(box), m_showCollidingBox(true) {
    setName("Collider");
    computeCollisionWithGround();
}

Collider::~Collider() {
    
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
    Rigidbody *rb = m_gameobject->getComponent<Rigidbody*>();
    if(rb != nullptr){
        glm::vec3 objMin = m_boxMin;
        objMin.y -= rb->getMass();
        glm::vec3 objMax = m_boxMax;
        return intersect(objMin, objMax, boxMin, boxMax);
    } else {
        return false;
    }
    
}

void Collider::computeCollisionWithGround(){
    if(m_terrain != nullptr){
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

}

void Collider::physicsUpdate() {
    updateCollidingBox();

    computeCollisionWithGround();
/*
    m_top = m_terrain->getVoxelAt(glm::vec3(position.x, position.y+boxMax.y, position.z));
    m_bottom = m_terrain->getVoxelAt(glm::vec3(position.x, position.y+boxMin.y, position.z));
    m_right = m_terrain->getVoxelAt(glm::vec3(position.x+boxMax.x, position.y, position.z));
    m_left = m_terrain->getVoxelAt(glm::vec3(position.x+boxMin.x, position.y, position.z));
    m_front = m_terrain->getVoxelAt(glm::vec3(position.x, position.y, position.z+box.z));
    m_back = m_terrain->getVoxelAt(glm::vec3(position.x, position.y, position.z-box.z));

*/
}

void Collider::createUI() {
    ImGui::Text("Box Collider: ");
    ImGui::DragFloat3("##boxCollider", &m_collidingBox[0], 0.01f, 0.01f, 10.f, "%.3f");

    ImGui::Text("Min: (%f, %f, %f)", m_boxMin.x, m_boxMin.y, m_boxMin.z);
    ImGui::Text("Max: (%f, %f, %f)", m_boxMax.x, m_boxMax.y, m_boxMax.z);

    if(m_terrain != nullptr){
        glm::vec3 position = m_gameobject->getTransform()->getPosition();


        glm::vec3 boxMin = m_gameobject->getTransform()->getPosition() + m_boxMin;
        glm::vec3 chunk_coord = m_terrain->toChunkGridCoord(boxMin) * glm::ivec3(m_terrain->getChunkSize()); 
        glm::vec3 voxelCoordGrid = m_terrain->toVoxelCoordInChunk(boxMin);

        ImGui::Text("chunk coord : (%f, %f, %f)", chunk_coord.x, chunk_coord.y, chunk_coord.z);
        ImGui::Text("voxel coord : (%f, %f, %f)", voxelCoordGrid.x, voxelCoordGrid.y, voxelCoordGrid.z);


        /*displayImGuiVoxel(m_top, "Top");
        displayImGuiVoxel(m_bottom, "Bottom");
        displayImGuiVoxel(m_left, "Left");
        displayImGuiVoxel(m_right, "Right");
        displayImGuiVoxel(m_back, "Back");
        displayImGuiVoxel(m_top, "Top");*/

    }

    ImGui::Text("Show colliding box "); ImGui::SameLine();
    ImGui::Checkbox("##showColliding",&m_showCollidingBox);
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
    if(m_terrain != nullptr){

        // Test intersect
        glm::vec3 voxel = glm::vec3(4.0f, 13.0f, 35.0f);
        drawAABB(voxel, voxel+1.0f, shader, intersect(voxel, voxel+1.0f) ? glm::vec4(1,0,0,1) : glm::vec4(0,0,1,1));

        // glm::vec3 voxel1 = m_terrain->toVoxelWorldCoord(m_boxMin + glm::vec3(-1,0,0));
        glm::vec3 voxelBottom1 = m_terrain->toVoxelWorldCoord(m_boxMin);
        glm::vec3 voxelBottom2 = m_terrain->toVoxelWorldCoord(glm::vec3(m_boxMin.x, m_boxMin.y, m_boxMax.z));
        glm::vec3 voxelBottom3 = m_terrain->toVoxelWorldCoord(glm::vec3(m_boxMax.x, m_boxMin.y, m_boxMax.z));
        glm::vec3 voxelBottom4 = m_terrain->toVoxelWorldCoord(glm::vec3(m_boxMax.x, m_boxMin.y, m_boxMin.z));

        // drawAABB(voxel1, voxel1+1.0f, shader, glm::vec4(0,0,1,1));
        drawAABB(voxelBottom1, voxelBottom1+1.0f, shader, intersect(voxelBottom1, voxelBottom1+1.0f) ? glm::vec4(1,0,0,1) : glm::vec4(0,0,1,1));
        drawAABB(voxelBottom2, voxelBottom2+1.0f, shader, intersect(voxelBottom2, voxelBottom2+1.0f) ? glm::vec4(1,0,0,1) : glm::vec4(0,0,1,1));
        drawAABB(voxelBottom3, voxelBottom3+1.0f, shader, intersect(voxelBottom3, voxelBottom3+1.0f) ? glm::vec4(1,0,0,1) : glm::vec4(0,0,1,1));
        drawAABB(voxelBottom4, voxelBottom4+1.0f, shader, intersect(voxelBottom4, voxelBottom4+1.0f) ? glm::vec4(1,0,0,1) : glm::vec4(0,0,1,1));
    
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
