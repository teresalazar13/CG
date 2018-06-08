#include "main.h"

using namespace std;

// util function that generates a random number from 0 to max
int generate_random_int_number(int max) {
  srand (time(NULL));
  return (rand() % max + 0);
}

void inicializa(void) {
  // Apagar
  glClearColor(BLACK);
  // Interpolacao de cores
  glShadeModel(GL_SMOOTH);

  render.setup_lights();
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);

  render.setup_default_textures();
  render.setup_cubemap_textures();
  // Ativar modo textura
  glEnable(GL_TEXTURE_2D);

  // Vertex arrays
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glEnableClientState(GL_VERTEX_ARRAY);
  glNormalPointer(GL_FLOAT, 0, normais);
  glEnableClientState(GL_NORMAL_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, cor);
  glEnableClientState(GL_COLOR_ARRAY);
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

    rand_texture = generate_random_int_number(3);
    rand_color = generate_random_int_number(4);

    cans[NUMBER_OF_CANS].texture = rand_texture;
    cans[NUMBER_OF_CANS].color = rand_color;
    NUMBER_OF_CANS++;
  }
}

//==================================== Lata
void createCans() {
  glEnable(GL_TEXTURE_2D);

  for (int i = 0; i < NUMBER_OF_CANS; i++) {
    // increment rotation angle
    angRotateX[i] = angRotateX[i] + incAngRotate;
    angRotateY[i] = angRotateY[i] + incAngRotate;
    angRotateZ[i] = angRotateZ[i] + incAngRotate;

    // translate can accordingly
    if (translateCanY[i] > yC/2 || translateCanY[i] < -yC/2) {
      incTranslateCanY[i] = incTranslateCanY[i] * -1;
    }
    translateCanY[i] = translateCanY[i] + incTranslateCanY[i];

    if (translateCanX[i] > yC/2 || translateCanX[i] < -yC/2) {
      incTranslateCanX[i] = incTranslateCanX[i] * -1;
    }
    translateCanX[i] = translateCanX[i] + incTranslateCanX[i];

    if (translateCanZ[i] > yC/2 || translateCanZ[i] < -yC/2) {
      incTranslateCanZ[i] = incTranslateCanZ[i] * -1;
    }
    translateCanZ[i] = translateCanZ[i] + incTranslateCanZ[i];

    // color reflected by can
    //glEnable(GL_COLOR_MATERIAL);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
    //glColor4f(
      //colors[cans[i].color][0],
      //colors[cans[i].color][1],
      //colors[cans[i].color][2],
      //colors[cans[i].color][3]
    //);

    // bind texture to can
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
      gluCylinder(yy, 0.5, 0.5, 1.75, 100, 100);

      // top of cylinder
      glPushMatrix();
        glTranslated(0.0f, 0.0f, 1.75);
        // (quad, inner, outer, slices, loops)
        gluDisk(yy, 0.0f, 0.5, 100, 100);
      glPopMatrix();

      // bottom of cylinder
      glPushMatrix();
        // (quad, inner, outer, slices, loops)
        gluDisk(yy, 0.0f, 0.5, 100, 100);
      glPopMatrix();

    glPopMatrix();
  }
  glDisable(GL_TEXTURE_2D);
}


void drawScene(){
  //glCullFace(GL_FRONT);

  glTranslated(TRANSLATE_X, 0, 0);
  glTranslated(0, 2, 0);
  glRotated(ROTATE, 1, 0, 0);
  glTranslated(0, -2, 0);

  createCans();
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
  gluLookAt(rVisao * cos(aVisao), obsP[1] + TRANSLATE_USER_Y, rVisao * sin(aVisao), LOOK_X, LOOK_Y, LOOK_Z, 0, 1, 0);

  // Objectos
  render.render_cubemap();
  drawScene();

  // Actualizacao
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
    // aproxima do centro ao inicio
    case 'o':
      if (rVisao > 1) {
        rVisao -= 1;
        glutPostRedisplay();
      }
      break;

    // afasta do centro ao inicio
    case 'p':
      if (rVisao < 20) {
        rVisao += 1;
        glutPostRedisplay();
      }
      break;

     // utilizador para baixo
    case 'u':
      TRANSLATE_USER_Y -= 1;
      glutPostRedisplay();
      break;

    // utilizador para cima
    case 'i':
      TRANSLATE_USER_Y += 1;
      glutPostRedisplay();
      break;

    // modificar o ponto para onde o utilizar esta a olha no eixo dos x
    case 'q':
      LOOK_X += -1;
      glutPostRedisplay();
      break;

    // modificar o ponto para onde o utilizar esta a olha no eixo dos xs
    case 'w':
      LOOK_X += 1;
      glutPostRedisplay();
      break;

    // modificar o ponto para onde o utilizar esta a olha no eixo dos xs
    case 'e':
      LOOK_Y += -1;
      glutPostRedisplay();
      break;

    // modificar o ponto para onde o utilizar esta a olha no eixo dos yy
    case 'r':
      LOOK_Y += 1;
      glutPostRedisplay();
      break;

    // modificar o ponto para onde o utilizar esta a olha no eixo dos zz
    case 't':
      LOOK_Z += -1;
      glutPostRedisplay();
      break;

    // modificar o ponto para onde o utilizar esta a olha no eixo dos zz
    case 'y':
      LOOK_Z += 1;
      glutPostRedisplay();
      break;

    case 'a':
      TRANSLATE_X += 1;
      glutPostRedisplay();
      break;

    case 's':
      TRANSLATE_X -= 1;
      glutPostRedisplay();
      break;

    case 'd':
      ROTATE -= 10;
      glutPostRedisplay();
      break;

    case 'f':
      ROTATE += 10;
      glutPostRedisplay();
      break;

    case 'z':
      generateCan();
      glutPostRedisplay();
      break;

    case '.':
      glEnable(GL_LIGHT0);
      glDisable(GL_LIGHT1);
      break;

    case '-':
      glEnable(GL_LIGHT1);
      glDisable(GL_LIGHT0);
      break;

    case 27:
      exit(0);
      break;
  }
}

void teclasNotAscii(int key, int x, int y){
  if(key == GLUT_KEY_UP) {
    obsP[1] = (obsP[1] +  0.1);
  }

  if(key == GLUT_KEY_DOWN) {
    obsP[1] = (obsP[1] - 0.1);
  }

  if (obsP[1] > yC) {
    obsP[1] = yC;
  }

  if (obsP[1] < -yC) {
    obsP[1] = -yC;
  }

  if(key == GLUT_KEY_LEFT) {
    aVisao = (aVisao + 0.1);
  }
  if(key == GLUT_KEY_RIGHT) {
    aVisao = (aVisao - 0.1);
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

  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHT1);
  return 0;
}
