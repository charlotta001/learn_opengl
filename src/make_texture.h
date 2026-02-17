#include "config.h"

#ifndef MAKE_TEXTURE_H
#define MAKE_TEXTURE_H

class Material {
    public:
    Material(const char* filename );
    ~Material();
    void use();
    private:
    std::vector <GLuint> texture;

};




#endif