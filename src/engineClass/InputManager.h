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

    void update();


private:

    Scene *scene = NULL;
    UI *ui = NULL;




};


#endif
