#ifndef MAINRENDERER_H
#define MAINRENDERER_H

#include <GL/glew.h>

#include <GL/gl.h>

#include <QGLFormat>
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "models/cube.h"

#include <vector>

class MainRenderer : public QGLWidget {
 public:
    MainRenderer(const QGLFormat &format=QGLFormat::defaultFormat());
    ~MainRenderer();

 protected:
    virtual void paintGL();
    virtual void initializeGL();
    virtual void resizeGL(int width,int height);
    virtual void keyPressEvent(QKeyEvent *ke);
    virtual void mousePressEvent(QMouseEvent *me);
    virtual void mouseMoveEvent(QMouseEvent *me);



    private:

        QTimer *_timer;

        glm::mat4 modelMat;
        glm::mat4 viewMat;
        glm::mat4 projectionMat;


        std::vector<GLuint*> arrayOfBuffers;
        std::vector<GLuint> arrayOfVertexArrayID;
        std::vector<DrawableObject*> objectsToDraw;

        void addObjectToScene(DrawableObject* object);
        void createVAOObject(DrawableObject* object);
        void deleteScene();

        void drawAnObject(DrawableObject* object, int i);

        void createShaders();

        void deleteShaders();

        Shader *exampleShader;

};

#endif
