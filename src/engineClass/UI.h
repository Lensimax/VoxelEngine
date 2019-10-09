#ifndef UI_H
#define UI_H

#include "scene.h"


class UI {
public:
    UI();
    ~UI();

    void drawUI(Scene *scene);

    void toggleHasToBeDisplayed();

    int getSelected();

private:

    void createUISceneManager(Scene *scene);
    void DrawSplitter(int split_vertically, float thickness, float* size0, float* size1, float min_size0, float min_size1);
    void createInfoWindow();


    bool hasToBeDisplayed;
    int selected = -1;
};

#endif
