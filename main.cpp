#include <qapplication.h>
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "mainRenderer.h"


using namespace std;



int main(int argc,char** argv) {

    QApplication application(argc,argv);

    QGLFormat fmt;
    fmt.setVersion(3,3);
    fmt.setProfile(QGLFormat::CoreProfile);
    fmt.setSampleBuffers(true);

    MainRenderer viewer(fmt);

    viewer.setWindowTitle("Green Engine");
    viewer.show();

    return application.exec();
}
