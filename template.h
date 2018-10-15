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

class Template : public QGLWidget {
 public:
    Template(const QGLFormat &format=QGLFormat::defaultFormat());
    ~Template();

 protected:
    virtual void paintGL();
    virtual void initializeGL();
    virtual void resizeGL(int width,int height);
    virtual void keyPressEvent(QKeyEvent *ke);
    virtual void mousePressEvent(QMouseEvent *me);
    virtual void mouseMoveEvent(QMouseEvent *me);

    QTimer *_timer;

    glm::mat4 modelMat;
    glm::mat4 viewMat;
    glm::mat4 projectionMat;

    private:
        Shader *exampleShader;

        void createShaders();
        void deleteShaders();

        GLuint _vaoQuad;
        GLuint _quad;

        void createQuadVAO();
        void deleteQuadVAO();
        void drawQuad();
};
