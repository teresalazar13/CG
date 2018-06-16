#include "main.h"

bool keyStates[256];

using namespace std;


void inicializa(void) {
  // Interpolacao de cores
  glShadeModel(GL_SMOOTH);
  // Apagar
  glClearColor(BLACK);

  glEnable(GL_DEPTH_TEST);

  render.setup_lights();
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);

  // Ativar modo textura
  glEnable(GL_TEXTURE_2D);
  render.setup_default_textures();
  render.setup_cubemap_textures();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_DEPTH_TEST);
  rain.NUMBER_OF_RAIN_PARTICLES = 1000;
  rain.init_particles();
}


void generateCan() {
  if (NUMBER_OF_CANS < 50) {
    int angRotateX_ = rand() % 360;
    int angRotateY_ = rand() % 360;
    int angRotateZ_ = rand() % 360;

    cans[NUMBER_OF_CANS].angRotateX = angRotateX_;
    cans[NUMBER_OF_CANS].angRotateY = angRotateY_;
    cans[NUMBER_OF_CANS].angRotateZ = angRotateZ_;

    int translateCanX_ = rand() % 36 - xC;
    int translateCanY_ = rand() % 36 - yC;
    int translateCanZ_ = rand() % 36 - zC;

    cans[NUMBER_OF_CANS].translateCanX = translateCanX_;
    cans[NUMBER_OF_CANS].incTranslateCanX = 0.1;

    cans[NUMBER_OF_CANS].translateCanY = translateCanY_;
    cans[NUMBER_OF_CANS].incTranslateCanY = 0.1;

    cans[NUMBER_OF_CANS].translateCanZ = translateCanZ_;
    cans[NUMBER_OF_CANS].incTranslateCanZ = 0.1;

    int rand_texture = rand() % NUMBER_OF_CAN_TEXTURES;

    cans[NUMBER_OF_CANS].texture = rand_texture;
    NUMBER_OF_CANS++;
  }
}


void createCans() {
  for (int i = 0; i < NUMBER_OF_CANS; i++) {
    // increment rotation angle
    cans[i].angRotateX = cans[i].angRotateX + incAngRotate;
    cans[i].angRotateY = cans[i].angRotateY + incAngRotate;
    cans[i].angRotateZ = cans[i].angRotateZ + incAngRotate;


    // translate can accordingly
    if (cans[i].translateCanY > yC - 1.75 || cans[i].translateCanY < -yC + 1.75) {
      if (MODE == 1) {
        glDisable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
      }
      cans[i].incTranslateCanY = cans[i].incTranslateCanY * -1;
    }
    cans[i].translateCanY = cans[i].translateCanY + cans[i].incTranslateCanY;

    if (cans[i].translateCanX > xC - 1.75 || cans[i].translateCanX < -xC + 1.75) {
      if (MODE == 1) {
        glDisable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
      }
      cans[i].incTranslateCanX = cans[i].incTranslateCanX * -1;
    }
    cans[i].translateCanX = cans[i].translateCanX + cans[i].incTranslateCanX;

    if (cans[i].translateCanZ > zC - 1.75 || cans[i].translateCanZ < -zC + 1.75) {
      if (MODE == 1) {
        glDisable(GL_LIGHT2);
        glEnable(GL_LIGHT0);
      }
      cans[i].incTranslateCanZ = cans[i].incTranslateCanZ * -1;
    }
    cans[i].translateCanZ = cans[i].translateCanZ + cans[i].incTranslateCanZ;

    // bind texture to can
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, render.texture[cans[i].texture]);
    GLUquadricObj* yy = gluNewQuadric();

    // create cylinder
    glPushMatrix();
      glTranslated(cans[i].translateCanX, cans[i].translateCanY, cans[i].translateCanZ);
      glRotatef(cans[i].angRotateX, 1, 0, 0);
      glRotatef(cans[i].angRotateY, 0, 1, 0);
      glRotatef(cans[i].angRotateZ, 0, 0, 1);

      gluQuadricDrawStyle (yy, GLU_FILL);
      gluQuadricNormals   (yy, GLU_SMOOTH);
      gluQuadricTexture   (yy, GL_TRUE);
      // void gluCylinder(GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks);
      gluCylinder(yy, 0.4, 0.4, 1.75, 100, 100);

      // top of cylinder
      glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, render.texture[NUMBER_OF_CAN_TEXTURES]);
        glTranslated(0.0f, 0.0f, 1.75);
        // (quad, inner, outer, slices, loops)
        gluDisk(yy, 0.0f, 0.4, 100, 100);
      glPopMatrix();

      // bottom of cylinder
      glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, render.texture[NUMBER_OF_CAN_TEXTURES + 1]);
        // (quad, inner, outer, slices, loops)
        gluDisk(yy, 0.0f, 0.4, 100, 100);
      glPopMatrix();

    glPopMatrix();
  }
}


void display(void){
  // Apaga ecra/profundidade
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glViewport (0, 0, wScreen, hScreen);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(angZoom, (float) wScreen / hScreen, 0.1, 5 * zC);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(rVisao * cos(aVisao), obsP[1], rVisao * sin(aVisao), LOOK_X, LOOK_Y, LOOK_Z, 0, 1, 0);

  if(keyStates[GLUT_KEY_UP] && obsP[1] < yC/2) {
    obsP[1] = (obsP[1] + 0.01);
  }

  if(keyStates[GLUT_KEY_DOWN] && obsP[1] > -yC/2) {
    obsP[1] = (obsP[1] - 0.01);
  }

  if(keyStates[GLUT_KEY_LEFT]) {
    aVisao = (aVisao + 0.01);
  }
  if(keyStates[GLUT_KEY_RIGHT]) {
    aVisao = (aVisao - 0.01);
  }

  obsP[0] = rVisao * cos(aVisao);
  obsP[2] = rVisao * sin(aVisao);

  if (keyStates['o'] && rVisao > 1) {
    rVisao -= 0.2;
  }

  // afasta do centro ao inicio
  if (keyStates['p'] && rVisao < xC) {
    rVisao += 0.02;
  }

  // modificar o ponto para onde o utilizar esta a olha no eixo dos x
  if (keyStates['q'] && rVisao < xC) {
    LOOK_X += -0.02;
  }

  // modificar o ponto para onde o utilizar esta a olha no eixo dos xs
  if (keyStates['w']) {
    LOOK_X += 0.02;
  }

  // modificar o ponto para onde o utilizar esta a olha no eixo dos xs
  if (keyStates['e']) {
    LOOK_Y += -0.02;
  }

  // modificar o ponto para onde o utilizar esta a olha no eixo dos yy
  if (keyStates['r']) {
    LOOK_Y += 0.02;
  }

  // modificar o ponto para onde o utilizar esta a olha no eixo dos zz
  if (keyStates['t']) {
    LOOK_Z += -0.02;
  }

  // modificar o ponto para onde o utilizar esta a olha no eixo dos zz
  if (keyStates['y']) {
    LOOK_Z += 0.02;
  }

  // Objectos
  render.render_cubemap();
  createCans();

  rain.render_rain();
  // Atualizacao
  glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y) {
  if (key == 'z') {
    generateCan();
  }

  if (key == '.') {
    if (rain.NUMBER_OF_RAIN_PARTICLES == 1000) {
      rain.NUMBER_OF_RAIN_PARTICLES = 0;
    }
    else {
      rain.NUMBER_OF_RAIN_PARTICLES = 1000;
    }
  }

  else if (key == '-') {
    if (MODE == 0) {
      MODE = 1;
    }
    else {
      glEnable(GL_LIGHT0);
      glEnable(GL_LIGHT1);
      glEnable(GL_LIGHT2);
      MODE = 0;
    }
  }

  else {
    keyStates[key] = true;
  }
}


void keyboardUp(unsigned char key, int x, int y) {
  keyStates[key] = false;
}


void teclasNotAscii(int key, int x, int y){
  keyStates[key] = true;
}

void teclasNotAsciiUp(int key, int x, int y){
  keyStates[key] = false;
}


void Timer(int value){
  glutPostRedisplay();
  glutTimerFunc(msec, Timer, 1);
}


int main(int argc, char** argv){
  srand(time(NULL));
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize (wScreen, hScreen);
  glutInitWindowPosition (300, 100);
  // TODO -> in create window write commands
  glutCreateWindow ("");

  inicializa();
  generateCan();

  glutSpecialFunc(teclasNotAscii);
  glutSpecialUpFunc(teclasNotAsciiUp);
  glutKeyboardFunc(keyboard);
  glutKeyboardUpFunc(keyboardUp);
  glutDisplayFunc(display);
  glutTimerFunc(msec, Timer, 1);

  glutMainLoop();
  return 0;
}
