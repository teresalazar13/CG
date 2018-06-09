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

#define NUMBER_OF_PARTICLES 1000
#define NUMBER_OF_CAN_TEXTURES 6

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
    GLuint  wall;
    GLuint  texture[NUMBER_OF_CAN_TEXTURES];
    RgbImage imag;
    Particle particle[2500];

    void setup_particle_texture();
    void setup_particles(GLfloat px, GLfloat py, GLfloat pz);
    void setup_lights();
    void setup_default_textures();
    void setup_cubemap_textures();
    void render_cubemap();
    void render_particle();
};
#endif
