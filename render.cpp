#include "render.h"

void Render::setup_lights() {
  // initializes variables
  GLfloat luzGlobalCor[4]={1.0, 1.0, 1.0};
  GLfloat localCor[4] = {1.0, 1.0, 1.0, 1.0};
  GLfloat localCorDif[4] = {1.0, 1.0, 1.0, 1.0};
  GLfloat localPos[4] = {1.0, 0.0, 0.0};
  GLfloat localAttCon = 1.0;
  GLfloat localAttLin = 0.05;
  GLfloat localAttQua = 0.0;

  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, localPos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, localCor);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 120);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
}

void Render::render_cubemap() {
  glPushMatrix();

    //left
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skyboxtex[3]);
    glBegin(GL_POLYGON);
      glTexCoord2f(1.0f,0.0f);  glVertex3f(-25, -25, -25);
      glTexCoord2f(0.0f,0.0f);  glVertex3f(-25, -25, 25);
      glTexCoord2f(0.0f,1.0f);  glVertex3f(-25, 25, 25);
      glTexCoord2f(1.0f,1.0f);  glVertex3f(-25, 25, -25);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    //top
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skyboxtex[4]);
    glBegin(GL_POLYGON);
      glTexCoord2f(1.0,0.0);glVertex3f(25, 25, -25);
      glTexCoord2f(1.0,1.0);glVertex3f(25, 25, 25);
      glTexCoord2f(0.0,1.0);glVertex3f(-25, 25, 25);
      glTexCoord2f(0.0,0.0);glVertex3f(-25, 25, -25);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // right
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skyboxtex[1]);
    glBegin(GL_POLYGON);
      glTexCoord2f(0.0f,0.0f);  glVertex3f(25, -25, -25);
      glTexCoord2f(1.0f,0.0f);  glVertex3f(25, -25, 25);
      glTexCoord2f(1.0f,1.0f);  glVertex3f(25, 25, 25);
      glTexCoord2f(0.0f,1.0f);  glVertex3f(25, 25, -25);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    // front
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skyboxtex[0]);
    glBegin(GL_POLYGON);
      glTexCoord2f(1.0f,0.0f);glVertex3f(25, -25, -25);
      glTexCoord2f(1.0f,1.0f);glVertex3f(25, 25, -25);
      glTexCoord2f(0.0f,1.0f);glVertex3f(-25, 25, -25);
      glTexCoord2f(0.0f,0.0f);glVertex3f(-25, -25, -25);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    //back
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skyboxtex[2]);
    glBegin(GL_POLYGON);
      glTexCoord2f(0.0f,0.0f);glVertex3f(25, -25, 25);
      glTexCoord2f(0.0f,1.0f);glVertex3f(25, 25, 25);
      glTexCoord2f(1.0f,1.0f);glVertex3f(-25, 25, 25);
      glTexCoord2f(1.0f,0.0f);glVertex3f(-25, -25, 25);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    //bottom
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,skyboxtex[5]);
    glBegin(GL_POLYGON);
      glTexCoord2f(1.0f,0.0f);glVertex3f(-25, -25, 25);
      glTexCoord2f(1.0f,1.0f);glVertex3f(25, -25, 25);
      glTexCoord2f(0.0f,1.0f);glVertex3f(25, -25, -25);
      glTexCoord2f(0.0f,0.0f);glVertex3f(-25, -25, -25);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

void Render::setup_default_textures() {
  glGenTextures(1, &texture[0]);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  imag.LoadBmpFile("mesa.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3,
    imag.GetNumCols(),
    imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
    imag.ImageData()
  );

  glGenTextures(1, &texture[1]);
  glBindTexture(GL_TEXTURE_2D, texture[1]);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  imag.LoadBmpFile("chao.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3,
    imag.GetNumCols(),
    imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
    imag.ImageData()
  );

  glGenTextures(1, &texture[2]);
  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  imag.LoadBmpFile("lata.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3,
    imag.GetNumCols(),
    imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
    imag.ImageData()
  );

}


void Render::setup_cubemap_textures() {
  glGenTextures(1, &skyboxtex[0]);
  glBindTexture(GL_TEXTURE_2D, skyboxtex[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  imag.LoadBmpFile("skybox/front.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &skyboxtex[1]);
  glBindTexture(GL_TEXTURE_2D, skyboxtex[1]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  imag.LoadBmpFile("skybox/right.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &skyboxtex[2]);
  glBindTexture(GL_TEXTURE_2D, skyboxtex[2]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  imag.LoadBmpFile("skybox/back.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &skyboxtex[3]);
  glBindTexture(GL_TEXTURE_2D, skyboxtex[3]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  imag.LoadBmpFile("skybox/left.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &skyboxtex[4]);
  glBindTexture(GL_TEXTURE_2D, skyboxtex[4]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  imag.LoadBmpFile("skybox/top.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &skyboxtex[5]);
  glBindTexture(GL_TEXTURE_2D, skyboxtex[5]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  imag.LoadBmpFile("skybox/bottom.bmp");
  glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());
}
