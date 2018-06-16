#include "rain.h"

float slowdown = 1;
float velocity = 0.6;
int w;

void Rain::setup_particle(int i) {
  par_sys[i].alive = true;
  par_sys[i].life = 1.0;
  par_sys[i].fade = (rand() % 100) / 1000.0f + 0.003f;
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

  for (w = 0; w < NUMBER_OF_RAIN_PARTICLES; w = w + 2) {

    if (par_sys[w].alive == true) {
      float y = par_sys[w].ypos;

      for (int i = -20; i < 20; i += 2) {
        for (int j = -20; j < 20; j += 3) {
          glColor4f(1, 1, 1, par_sys[w].life);
          glBegin(GL_LINES);
            glVertex3f(i, y, j);
            glVertex3f(i, y + 0.1, j);
          glEnd();
        }
      }

      par_sys[w].ypos += par_sys[w].vel / (slowdown * 1000);
      par_sys[w].vel += par_sys[w].gravity;
      par_sys[w].life -= par_sys[w].fade;

      if (par_sys[w].ypos <= -20) {
        par_sys[w].life = -1.0;
      }

      if (par_sys[w].life < -1.0) {
        setup_particle(w);
      }
    }
  }

  glDisable(GL_BLEND);
}
