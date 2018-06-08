#ifndef RENDER_HEADER
#define RENDER_HEADER

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

#include <iostream>
#include "RgbImage.h"
using namespace std;

class Render {
  public:
    GLuint  skyboxtex[1];
    GLuint  texture[3];
    RgbImage imag;

    void setup_lights();
    void setup_default_textures();
    void setup_cubemap_textures();
    void render_cubemap();
};
#endif
