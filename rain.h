#ifndef RAIN_HEADER
#define RAIN_HEADER

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <time.h>
#include <vector>

using namespace std;

typedef struct {
  bool alive;
  float life;
  float fade;
  float ypos;
  float vel;
  float gravity;
} particles;

class Rain {
  public:
    int NUMBER_OF_RAIN_PARTICLES;
    particles par_sys[1000];
    void setup_particle(int i);
    void init_particles();
    void render_rain();
    void define_rain_properties();
};

#endif
