#include "rain.h"

float slowdown = 2.0;
float velocity = 1;
int loop;
float rain_positions[NUMBER_OF_RAIN][2];


// Initialize / Reset Particles
void Rain::setup_particle(int i) {
  par_sys[i].alive = true;
  par_sys[i].life = 1.0;
  par_sys[i].fade = float(rand() % 100)/ 1000.0f + 0.003f;

  par_sys[i].ypos = 20.0;

  par_sys[i].vel = velocity;
  par_sys[i].gravity = -0.8;
}

void Rain::init_particles() {
  for (int i = 0; i < NUMBER_OF_RAIN_PARTICLES; i++) {
    setup_particle(i);
  }
}

void Rain::define_rain_properties() {
  // First index is x, second index is z
  for (int i = 0; i < NUMBER_OF_RAIN; i++) {
    rain_positions[i][0] = rand() % 40 - 20;
    rain_positions[i][1] = rand() % 40 - 20;
  }
}

void Rain::render_rain() {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE);
  float x, y, z;

  for (loop = 0; loop < NUMBER_OF_RAIN_PARTICLES; loop = loop + 2) {

    if (par_sys[loop].alive == true) {
      y = par_sys[loop].ypos;

      for (int i = 0; i < NUMBER_OF_RAIN; i++) {
        // Draw particles
        glColor4f(0, 0, 1, par_sys[loop].life);
        glBegin(GL_LINES);
          glVertex3f(rain_positions[i][0], y, rain_positions[i][1]);
          glVertex3f(rain_positions[i][0], y + 0.03, rain_positions[i][1]);
        glEnd();

        glColor4f(1, 1, 1, 1);
      }

      // Update values
      // Move
      // Adjust slowdown for speed!
      par_sys[loop].ypos += par_sys[loop].vel / (slowdown * 1000);
      par_sys[loop].vel += par_sys[loop].gravity;
      // Decay
      par_sys[loop].life -= par_sys[loop].fade;

      if (par_sys[loop].ypos <= -20) {
        par_sys[loop].life = -1.0;
      }
      //Revive
      if (par_sys[loop].life < -1.0) {
        setup_particle(loop);
      }
    }
  }
  glDisable(GL_BLEND);
}
