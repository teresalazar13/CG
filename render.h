#ifndef RENDER_HEADER
#define RENDER_HEADER
#define frand()			((float)rand()/RAND_MAX)

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "RgbImage.h"
using namespace std;


// Particles variables
typedef struct {
  float size;
  float	life;		// vida
  float	fade;		// fade
  float	r, g, b;    // color
  GLfloat x, y, z;    // posicao
  GLfloat vx, vy, vz; // velocidade 
  GLfloat ax, ay, az; // aceleracao
} Particle;

// Class responsible for the renderization funcctions
class Render {
  public:
    GLuint  particle_texture[1];
    GLuint  skyboxtex[1];
    GLuint  texture[3];
    RgbImage imag;
    Particle particle[2500];

    void setup_particle_texture();
    void setup_particles();
    void setup_lights();
    void setup_default_textures();
    void setup_cubemap_textures();
    void render_cubemap();
    void render_particle();
};
#endif
