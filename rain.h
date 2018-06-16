#ifndef RAIN_HEADER
#define RAIN_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <time.h>
#include <vector>

using namespace std;

#define NUMBER_OF_RAIN_PARTICLES 1000

typedef struct {
  // Life
  bool alive;	// is the particle alive?
  float life;	// particle lifespan
  float fade; // decay
  // color
  float red;
  float green;
  float blue;
  // Position/direction
  float xpos;
  float ypos;
  float zpos;
  // Velocity/Direction, only goes down in y dir
  float vel;
  // Gravity
  float gravity;
} particles;

class Rain {
  public:
    particles par_sys[1000];
    void setup_particle(int i);
    void init_particles();
    void render_rain();
    void define_rain_properties();
};

#endif
