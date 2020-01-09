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


Collider::Collider(glm::vec3 box) : m_collidingBox(box), m_showCollidingBox(true) {
    setName("Collider");
}

Collider::~Collider() {
    
}

void Collider::update() {
    const glm::vec3 box = m_collidingBox*m_gameobject->getTransform()->getScale();
    glm::vec3 position = m_gameobject->getTransform()->getPosition();
    m_top = m_terrain->getVoxelAt(glm::vec3(position.x, position.y+box.y, position.z));
    m_bottom = m_terrain->getVoxelAt(glm::vec3(position.x, position.y-box.y, position.z));
}

void Collider::createUI() {
    ImGui::Text("Box Collider: ");
    ImGui::DragFloat3("##boxCollider", &m_collidingBox[0], 0.01f, 0.01f, 10.f, "%.3f");

    if(m_terrain != nullptr){
        glm::vec3 position = m_gameobject->getTransform()->getPosition();
        ImGui::Text("Position: (%f, %f, %f)", position.x, position.y, position.z);

        Voxel voxel = m_terrain->getVoxelAt(position);
        displayImGuiVoxel(voxel, "test");

        displayImGuiVoxel(m_top, "Top");
        displayImGuiVoxel(m_bottom, "Bottom");

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
    
    if(!m_showCollidingBox){
        return;
    }

    const float lineWidth = 0.2f;
    const glm::vec4 color = glm::vec4(1,0,0,1);

    glm::vec3 origin = glm::vec3(0, 0, 0);
    glm::vec3 forward = glm::vec3(0, 0, 1);


    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 right = glm::vec3(1, 0, 0);


    std::vector<glm::vec3> arrayAxis;

    glLineWidth(lineWidth);

    Shader shader = Shader();
    shader.load("../data/shaders/simple.vert","../data/shaders/simple.frag");
    glUseProgram(shader.id());
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"modelMat"),1,GL_FALSE,&(modelMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"viewMat"),1,GL_FALSE,&(viewMat[0][0]));
    glUniformMatrix4fv(glGetUniformLocation(shader.id(),"projMat"),1,GL_FALSE,&(projectionMat[0][0]));
    glUniform4fv(glGetUniformLocation(shader.id(),"color"), 1, &color[0]);


    arrayAxis.resize(24);
    // face du dessus
    arrayAxis[0] = glm::vec3(-m_collidingBox.x, m_collidingBox.y, m_collidingBox.z);
    arrayAxis[1] = glm::vec3(m_collidingBox.x, m_collidingBox.y, m_collidingBox.z);
    arrayAxis[2] = glm::vec3(m_collidingBox.x, m_collidingBox.y, m_collidingBox.z);
    arrayAxis[3] = glm::vec3(m_collidingBox.x, m_collidingBox.y, -m_collidingBox.z);
    arrayAxis[4] = glm::vec3(m_collidingBox.x, m_collidingBox.y, -m_collidingBox.z);
    arrayAxis[5] = glm::vec3(-m_collidingBox.x, m_collidingBox.y, -m_collidingBox.z);
    arrayAxis[6] = glm::vec3(-m_collidingBox.x, m_collidingBox.y, -m_collidingBox.z);
    arrayAxis[7] = glm::vec3(-m_collidingBox.x, m_collidingBox.y, m_collidingBox.z);
    // face du dessous
    arrayAxis[8] = glm::vec3(-m_collidingBox.x, -m_collidingBox.y, m_collidingBox.z);
    arrayAxis[9] = glm::vec3(m_collidingBox.x, -m_collidingBox.y, m_collidingBox.z);
    arrayAxis[10] = glm::vec3(m_collidingBox.x, -m_collidingBox.y, m_collidingBox.z);
    arrayAxis[11] = glm::vec3(m_collidingBox.x, -m_collidingBox.y, -m_collidingBox.z);
    arrayAxis[12] = glm::vec3(m_collidingBox.x, -m_collidingBox.y, -m_collidingBox.z);
    arrayAxis[13] = glm::vec3(-m_collidingBox.x, -m_collidingBox.y, -m_collidingBox.z);
    arrayAxis[14] = glm::vec3(-m_collidingBox.x, -m_collidingBox.y, -m_collidingBox.z);
    arrayAxis[15] = glm::vec3(-m_collidingBox.x, -m_collidingBox.y, m_collidingBox.z);
    // reliure des 2 faces
    arrayAxis[16] = glm::vec3(-m_collidingBox.x, m_collidingBox.y, m_collidingBox.z);
    arrayAxis[17] = glm::vec3(-m_collidingBox.x, -m_collidingBox.y, m_collidingBox.z);

    arrayAxis[18] = glm::vec3(m_collidingBox.x, m_collidingBox.y, m_collidingBox.z);
    arrayAxis[19] = glm::vec3(m_collidingBox.x, -m_collidingBox.y, m_collidingBox.z);

    arrayAxis[20] = glm::vec3(m_collidingBox.x, m_collidingBox.y, -m_collidingBox.z);
    arrayAxis[21] = glm::vec3(m_collidingBox.x, -m_collidingBox.y, -m_collidingBox.z);

    arrayAxis[22] = glm::vec3(-m_collidingBox.x, m_collidingBox.y, -m_collidingBox.z);
    arrayAxis[23] = glm::vec3(-m_collidingBox.x, -m_collidingBox.y, -m_collidingBox.z);





    DrawDebug::drawArrayPosition(arrayAxis.size(), (float*)&arrayAxis[0], GL_LINES);

  

    glUseProgram(0);

}
