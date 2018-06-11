#include "main.h"

using namespace std;

// util function that generates a random number from 0 to max
int generate_random_int_number(int max) {
  srand (time(NULL));
  return (rand() % max + 0);
}

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
  rain.init_particles();
}

void generateCan() {
  srand (time(NULL));
  int rand_texture = 0;
  int rand_color = 0;

  if (NUMBER_OF_CANS < 50) {
    int angRotateX_ = generate_random_int_number(360);
    int angRotateY_ = generate_random_int_number(360);
    int angRotateZ_ = generate_random_int_number(360);

    angRotateX[NUMBER_OF_CANS] = angRotateX_;
    angRotateY[NUMBER_OF_CANS] = angRotateY_;
    angRotateZ[NUMBER_OF_CANS] = angRotateZ_;

    int translateCanX_ = rand() % 10 - 5;
    int translateCanY_ = rand() % 10 - 5;
    int translateCanZ_ = rand() % 10 - 5;

    translateCanX[NUMBER_OF_CANS] = translateCanX_;
    incTranslateCanX[NUMBER_OF_CANS] = 0.1;

    translateCanY[NUMBER_OF_CANS] = translateCanY_;
    incTranslateCanY[NUMBER_OF_CANS] = 0.1;

    translateCanZ[NUMBER_OF_CANS] = translateCanZ_;
    incTranslateCanZ[NUMBER_OF_CANS] = 0.1;

    rand_texture = generate_random_int_number(NUMBER_OF_CAN_TEXTURES);

    cans[NUMBER_OF_CANS].texture = rand_texture;
    NUMBER_OF_CANS++;
  }
}

//==================================== Lata
void createCans() {
  for (int i = 0; i < NUMBER_OF_CANS; i++) {
    // increment rotation angle
    angRotateX[i] = angRotateX[i] + incAngRotate;
    angRotateY[i] = angRotateY[i] + incAngRotate;
    angRotateZ[i] = angRotateZ[i] + incAngRotate;

    // translate can accordingly
    if (translateCanY[i] > yC || translateCanY[i] < -yC) {
      if (MODE == 1) {
        glDisable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
      }
      incTranslateCanY[i] = incTranslateCanY[i] * -1;
      render.setup_particles(translateCanX[i], translateCanY[i], translateCanZ[i]);
      render.render_particle();
    }
    translateCanY[i] = translateCanY[i] + incTranslateCanY[i];

    if (translateCanX[i] > xC/2 || translateCanX[i] < -xC/2) {
      if (MODE == 1) {
        glDisable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
      }
      incTranslateCanX[i] = incTranslateCanX[i] * -1;
      render.setup_particles(translateCanX[i], translateCanY[i], translateCanZ[i]);
      render.render_particle();
    }
    translateCanX[i] = translateCanX[i] + incTranslateCanX[i];

    if (translateCanZ[i] > zC/2 || translateCanZ[i] < -zC/2) {
      if (MODE == 1) {
        glDisable(GL_LIGHT2);
        glEnable(GL_LIGHT0);
      }
      incTranslateCanZ[i] = incTranslateCanZ[i] * -1;
      render.setup_particles(translateCanX[i], translateCanY[i], translateCanZ[i]);
      render.render_particle();
    }
    translateCanZ[i] = translateCanZ[i] + incTranslateCanZ[i];

    // bind texture to can
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, render.texture[cans[i].texture]);
    GLUquadricObj* yy = gluNewQuadric();

    // create cylinder
    glPushMatrix();
      glTranslated(translateCanX[i], translateCanY[i], translateCanZ[i]);
      glRotatef (angRotateX[i], 1, 0, 0);
      glRotatef (angRotateY[i], 0, 1, 0);
      glRotatef (angRotateZ[i], 0, 0, 1);

      gluQuadricDrawStyle (yy, GLU_FILL);
      gluQuadricNormals   (yy, GLU_SMOOTH);
      gluQuadricTexture   (yy, GL_TRUE);
      // void gluCylinder(GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks);
      gluCylinder(yy, 0.4, 0.4, 1.75, 100, 100);

      glBindTexture(GL_TEXTURE_2D, render.texture[NUMBER_OF_CAN_TEXTURES]);

      // top of cylinder
      glPushMatrix();
        glTranslated(0.0f, 0.0f, 1.75);
        // (quad, inner, outer, slices, loops)
        gluDisk(yy, 0.0f, 0.4, 100, 100);
      glPopMatrix();

      // bottom of cylinder
      glPushMatrix();
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

  // Objectos
  render.render_cubemap();
  createCans();

  rain.render_rain();
  // Atualizacao
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
    // aproxima do centro ao inicio
    case 'o':
      if (rVisao > 1) {
        rVisao -= 0.1;
        glutPostRedisplay();
      }
      break;

    // afasta do centro ao inicio
    case 'p':
      if (rVisao < 20) {
        rVisao += 0.1;
        glutPostRedisplay();
      }
      break;

    // modificar o ponto para onde o utilizar esta a olha no eixo dos x
    case 'q':
      LOOK_X += -0.1;
      glutPostRedisplay();
      break;

    // modificar o ponto para onde o utilizar esta a olha no eixo dos xs
    case 'w':
      LOOK_X += 0.1;
      glutPostRedisplay();
      break;

    // modificar o ponto para onde o utilizar esta a olha no eixo dos xs
    case 'e':
      LOOK_Y += -0.1;
      glutPostRedisplay();
      break;

    // modificar o ponto para onde o utilizar esta a olha no eixo dos yy
    case 'r':
      LOOK_Y += 0.1;
      glutPostRedisplay();
      break;

    // modificar o ponto para onde o utilizar esta a olha no eixo dos zz
    case 't':
      LOOK_Z += -0.1;
      glutPostRedisplay();
      break;

    // modificar o ponto para onde o utilizar esta a olha no eixo dos zz
    case 'y':
      LOOK_Z += 0.1;
      glutPostRedisplay();
      break;

    case 'z':
      generateCan();
      glutPostRedisplay();
      break;

    case '-':
      if (MODE == 0) {
        MODE = 1;
      }
      else {
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glEnable(GL_LIGHT2);
        MODE = 0;
      }
      break;

    case 27:
      exit(0);
      break;
  }
}

void teclasNotAscii(int key, int x, int y){
  if(key == GLUT_KEY_UP && obsP[1] < yC/2) {
    obsP[1] = (obsP[1] + 0.3);
  }

  if(key == GLUT_KEY_DOWN && obsP[1] > -yC/2) {
    obsP[1] = (obsP[1] - 0.3);
  }

  if(key == GLUT_KEY_LEFT) {
    aVisao = (aVisao + 0.01);
  }
  if(key == GLUT_KEY_RIGHT) {
    aVisao = (aVisao - 0.01);
  }

  obsP[0] = rVisao * cos(aVisao);
  obsP[2] = rVisao * sin(aVisao);

  glutPostRedisplay();
}

void Timer(int value){
  glutPostRedisplay();
  glutTimerFunc(msec, Timer, 1);
}


int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize (wScreen, hScreen);
  glutInitWindowPosition (300, 100);
  // TODO -> in create window write commands
  glutCreateWindow ("");

  inicializa();

  glutSpecialFunc(teclasNotAscii);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(msec, Timer, 1);

  glutMainLoop();
  return 0;
}
