#ifndef TEXTUREMATERIAL_H
#define TEXTUREMATERIAL_H

#ifndef GLM_H
#define GLM_H
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#endif



#include "material.h"

class TextureMaterial : public Material {

public:
    TextureMaterial(string file);
    ~TextureMaterial();

private:
    string filename;

};


#endif
