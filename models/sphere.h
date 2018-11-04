#ifndef SPHERE_H
#define SPHERE_H

#include "drawableObject.h"

#include <vector>

class Sphere : public DrawableObject {


    private:

        std::vector<float> vertices;
        std::vector<int> triangles;
        std::vector<float> normals;
        std::vector<float> texCoord;
};


#endif;
