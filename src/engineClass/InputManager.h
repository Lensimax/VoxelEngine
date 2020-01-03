#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "scene.h"
#include "mainRenderer.h"

class UI;

#ifndef GLM_H
#define GLM_H
#include <glm/gtx/perpendicular.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif

class InputManager {

public:

    InputManager();
    ~InputManager();

    void setScene(Scene *sc);
    void setUI(UI *u);
    void setRenderer(MainRenderer *r);

    void createUI();

    void update();



private:

    Scene *m_scene = NULL;
    UI *m_ui = NULL;
    MainRenderer *m_renderer = NULL;

    
};


#endif
