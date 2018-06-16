#include "rain.h"

float slowdown = 1;
float velocity = 0.6;
int loop;

// Initialize / Reset Particles
void Rain::setup_particle(int i) {
  par_sys[i].alive = true;
  par_sys[i].life = 1.0;
  par_sys[i].fade = (rand() % 100) / 1000.0f + 0.003f;
  par_sys[i].xpos = -20.0;
  par_sys[i].zpos = -20.0;
  par_sys[i].ypos = 20.0;

  par_sys[i].vel = velocity;
  par_sys[i].gravity = -0.8;
}

void Rain::init_particles() {
  for (int i = 0; i < NUMBER_OF_RAIN_PARTICLES; i++) {
    setup_particle(i);
  }
}

void Rain::render_rain() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);
  float x, y, z;

  for (loop = 0; loop < NUMBER_OF_RAIN_PARTICLES; loop = loop + 2) {

    if (par_sys[loop].alive == true) {
      x = par_sys[loop].xpos;
      y = par_sys[loop].ypos;
      z = par_sys[loop].zpos;
      for (int i = x; i < 20; i += 2) {
        for (int j = z; j < 20; j+= 3) {
          // Draw particles
          glColor4f(0, 0, 1, par_sys[loop].life);
          glBegin(GL_LINES);
            glVertex3f(i, y, j);
            glVertex3f(i, y + 0.1, j);
          glEnd();

          glColor4f(1, 1, 1, 1);
        }
      }

      // Update values, move, adjust slowdown for speed
      par_sys[loop].ypos += par_sys[loop].vel / (slowdown*1000);
      par_sys[loop].vel += par_sys[loop].gravity;
      // Decay
      par_sys[loop].life -= par_sys[loop].fade;

      if (par_sys[loop].ypos <= -20) {
        par_sys[loop].life = -1.0;
      }

      // Revive
      if (par_sys[loop].life < -1.0) {
        setup_particle(loop);
      }
    }
  }
  glDisable(GL_BLEND);
}
