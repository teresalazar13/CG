#ifndef RENDER_HEADER
#define RENDER_HEADER
#define frand()	((float)rand()/RAND_MAX)

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "RgbImage.h"
using namespace std;

#define NUMBER_OF_CAN_TEXTURES 6

// Class responsible for the renderization funcctions
class Render {
  public:
    GLuint wall;
    GLuint texture[NUMBER_OF_CAN_TEXTURES + 2];
    RgbImage imag;

    void setup_lights();
    void setup_default_textures();
    void setup_cubemap_textures();
    void render_cubemap();
    void render_particle();
};
#endif
