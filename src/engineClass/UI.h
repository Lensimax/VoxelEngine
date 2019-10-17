#ifndef UI_H
#define UI_H

#include <GLFW/glfw3.h>

#include "scene.h"
#include "mainRenderer.h"


class UI {
public:
    UI();
    ~UI();

    void drawUI();

    void toggleHasToBeDisplayed();

    int getSelected();

    void set(Scene *sc);
    void set(MainRenderer *main);
    void set(GLFWwindow *win);

private:

    void createUISceneManager(Scene *scene);
    void DrawSplitter(int split_vertically, float thickness, float* size0, float* size1, float min_size0, float min_size1);
    void createInfoWindow();


    bool hasToBeDisplayed;
    int selected = -1;

    Scene *scene;
    MainRenderer *mainRenderer;
    GLFWwindow* window;

};

#endif
