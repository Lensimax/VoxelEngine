#ifndef UI_H
#define UI_H

#include <GLFW/glfw3.h>

#include "scene.h"
#include "mainRenderer.h"

#include <vector>


class UI {
public:
    UI();
    ~UI();

    void drawUI();

   
    int getSelected();

    void set(Scene *sc);
    void set(MainRenderer *main);
    void set(GLFWwindow *win);

    inline bool hasToDisplayed(){
        return m_hasToBeDisplayed;
    }
    inline void toggleHasToBeDisplayed(){
        m_hasToBeDisplayed = !m_hasToBeDisplayed;
    }


private:

    void createUISceneManager(Scene *scene);
    void DrawSplitter(int split_vertically, float thickness, float* size0, float* size1, float min_size0, float min_size1);
    void createInfoWindow();
    void displayEngineNode(std::vector<GameObject*> obj);


    bool m_hasToBeDisplayed;
    int m_selectedID;

    Scene *m_scene;
    MainRenderer *m_mainRenderer;
    GLFWwindow* m_window;

};

#endif
