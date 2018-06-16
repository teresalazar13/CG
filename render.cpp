#include "render.h"


void Render::setup_lights() {
  // Light Variables
  GLfloat light0_amb[4] = {0.7, 0.0, 0.0, 1.0};
  GLfloat light0_dif[4] = {0.7, 0.0, 0.0, 1.0};
  GLfloat light0_spec[4] = {0.7, 0.0, 0.0, 1.0};
  GLfloat light0_pos[4] = {10.0, 0.0, 0.0, 1.0};
  GLfloat light0_dir[3] = {-1.0, 0.0, -1.0};

  GLfloat light1_amb[4] = {0.0, 0.7, 0.0, 1.0};
  GLfloat light1_dif[4] = {0.0, 0.7, 0.0, 1.0};
  GLfloat light1_spec[4] = {0.0, 0.7, 0.0, 1.0};
  GLfloat light1_pos[4] = {10.0, 0.0, 0.0, 1.0};

  GLfloat light2_amb[4] = {0.0, 0.0, 0.7, 1.0};
  GLfloat light2_dif[4] = {0.0, 0.0, 0.7, 1.0};
  GLfloat light2_spec[4] = {0.0, 0.0, 0.7, 1.0};
  GLfloat light2_pos[4] = {10.0, 0.0, 0.0, 1.0};

  glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_spec);
    //glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 80);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_dir);
  glDisable(GL_LIGHT0);

  glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_amb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_dif);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_spec);
  glDisable(GL_LIGHT1);

  glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, light2_amb);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light2_spec);
  glDisable(GL_LIGHT2);
}

void Render::render_cubemap() {
  glPushMatrix();

    //left
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, wall);
    glBegin(GL_POLYGON);
      glTexCoord2f(1.0f, 0.15f); glVertex3f(-20, -20, -20);
      glTexCoord2f(0.15f, 0.15f); glVertex3f(-20, -20, 20);
      glTexCoord2f(0.15f, 1.0f); glVertex3f(-20, 20, 20);
      glTexCoord2f(1.0f, 1.0f); glVertex3f(-20, 20, -20);
    glEnd();

    //top
    glBindTexture(GL_TEXTURE_2D, wall);
    glBegin(GL_POLYGON);
      glTexCoord2f(1.0f, 0.15f); glVertex3f(20, 20, -20);
      glTexCoord2f(1.0f, 1.0f); glVertex3f(20, 20, 20);
      glTexCoord2f(0.15f, 1.0f); glVertex3f(-20, 20, 20);
      glTexCoord2f(0.15f, 0.15f); glVertex3f(-20, 20, -20);
    glEnd();

    // right
    glBindTexture(GL_TEXTURE_2D, wall);
    glBegin(GL_POLYGON);
      glTexCoord2f(0.15f, 0.15f); glVertex3f(20, -20, -20);
      glTexCoord2f(1.0f, 0.15f); glVertex3f(20, -20, 20);
      glTexCoord2f(1.0f, 1.0f); glVertex3f(20, 20, 20);
      glTexCoord2f(0.15f, 1.0f); glVertex3f(20, 20, -20);
    glEnd();

    // front
    glBindTexture(GL_TEXTURE_2D, wall);
    glBegin(GL_POLYGON);
      glTexCoord2f(1.0f, 0.15f); glVertex3f(20, -20, -20);
      glTexCoord2f(1.0f, 1.0f); glVertex3f(20, 20, -20);
      glTexCoord2f(0.15f, 1.0f); glVertex3f(-20, 20, -20);
      glTexCoord2f(0.15f, 0.15f); glVertex3f(-20, -20, -20);
    glEnd();

    //back
    glBindTexture(GL_TEXTURE_2D, wall);
    glBegin(GL_POLYGON);
      glTexCoord2f(0.15f, 0.15f); glVertex3f(20, -20, 20);
      glTexCoord2f(0.15f, 1.0f); glVertex3f(20, 20, 20);
      glTexCoord2f(1.0f, 1.0f); glVertex3f(-20, 20, 20);
      glTexCoord2f(1.0f, 0.15f); glVertex3f(-20, -20, 20);
    glEnd();

    //bottom
    glBindTexture(GL_TEXTURE_2D, wall);
    glBegin(GL_POLYGON);
      glTexCoord2f(1.0f, 0.15f); glVertex3f(-20, -20, 20);
      glTexCoord2f(1.0f, 1.0f); glVertex3f(20, -20, 20);
      glTexCoord2f(0.15f, 1.0f); glVertex3f(20, -20, -20);
      glTexCoord2f(0.15f, 0.15f); glVertex3f(-20, -20, -20);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

void Render::setup_default_textures() {
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  glGenTextures(1, &texture[0]);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  imag.LoadBmpFile("textures/coke_red.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &texture[1]);
  glBindTexture(GL_TEXTURE_2D, texture[1]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  imag.LoadBmpFile("textures/coke_pink.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &texture[2]);
  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  imag.LoadBmpFile("textures/coke_orange.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &texture[3]);
  glBindTexture(GL_TEXTURE_2D, texture[3]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  imag.LoadBmpFile("textures/coke_blue.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &texture[4]);
  glBindTexture(GL_TEXTURE_2D, texture[4]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  imag.LoadBmpFile("textures/coke_green.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &texture[5]);
  glBindTexture(GL_TEXTURE_2D, texture[5]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  imag.LoadBmpFile("textures/coke_yellow.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &texture[6]);
  glBindTexture(GL_TEXTURE_2D, texture[6]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  imag.LoadBmpFile("textures/top.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &texture[7]);
  glBindTexture(GL_TEXTURE_2D, texture[7]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  imag.LoadBmpFile("textures/bottom.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());
}


void Render::setup_cubemap_textures() {
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glGenTextures(1, &wall);
  glBindTexture(GL_TEXTURE_2D,  wall);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  imag.LoadBmpFile("textures/wall.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());
}
