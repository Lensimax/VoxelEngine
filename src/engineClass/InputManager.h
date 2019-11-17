#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "scene.h"
#include "UI.h"

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

    Scene *scene = NULL;
    UI *ui = NULL;
    MainRenderer *renderer = NULL;




};


#endif
