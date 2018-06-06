#include <stdlib.h>
#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <time.h>
#include <vector>
#include "main.h"
#include "materiais.h"

using namespace std;

void drawCubeMap(){
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

    glBindTexture(GL_TEXTURE_2D, 0);
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

// util function that generates a random number from 0 to max
int generate_random_int_number(int max) {
  srand (time(NULL));
  return (rand() % max + 0);
}

// initializes the lights used
void initLights() {
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, localPos);
  glLightfv(GL_LIGHT0, GL_AMBIENT, localCor);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
  glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 120);
  glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
}

// setups the textures used by the cans
void setupTextures() {
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

  glDisable(GL_TEXTURE_2D),
  glEnable(GL_TEXTURE_2D),

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

void inicializa(void) {
  glClearColor(BLACK);		// Apagar
  glShadeModel(GL_SMOOTH);	// Interpolacao de cores

  initLights();
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);	// Profundidade

  setupTextures();
  glEnable(GL_TEXTURE_2D);  // Ativar modo textura

  glVertexPointer(3, GL_FLOAT, 0, vertices); //Vertex arrays
  glEnableClientState(GL_VERTEX_ARRAY);
  glNormalPointer(GL_FLOAT, 0, normais);
  glEnableClientState(GL_NORMAL_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, cor);
  glEnableClientState(GL_COLOR_ARRAY);
}

void drawEixos() {
  // Eixo X
  glColor4f(RED);
  glBegin(GL_LINES);
  glVertex3i(0, 0, 0);
  glVertex3i(10, 0, 0);
  glEnd();

  // Eixo Y
  glColor4f(GREEN);
  glBegin(GL_LINES);
  glVertex3i(0,  0, 0);
  glVertex3i(0, 10, 0);
  glEnd();

  // Eixo Z
  glColor4f(BLUE);
  glBegin(GL_LINES);
  glVertex3i(0, 0, 0);
  glVertex3i(0, 0, 10);
  glEnd();
}

void drawBoundaries() {
  GLUquadricObj*  y = gluNewQuadric ( );

  glPushMatrix();
    glScalef(20, 20, 20);
    glutWireCube(1);
  glPopMatrix();
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
    // raise rotation angle
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
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_EMISSION);
    glColor4f(
      colors[cans[i].color][0],
      colors[cans[i].color][1],
      colors[cans[i].color][2],
      colors[cans[i].color][3]
    );

    // bind texture to can
    glBindTexture(GL_TEXTURE_2D, texture[cans[i].texture]);
    GLUquadricObj* yy = gluNewQuadric();

    // create cylinder
    glPushMatrix();
      glTranslated(translateCanX[i], translateCanY[i], translateCanZ[i]);
      glRotatef (angRotateX[i], 1, 0, 0);
      glRotatef (angRotateY[i], 0, 1, 0);
      glRotatef (angRotateZ[i], 0, 0, 1);

      gluQuadricDrawStyle ( yy, GLU_FILL   );
      gluQuadricNormals   ( yy, GLU_SMOOTH );
      gluQuadricTexture   ( yy, GL_TRUE    );
      // void gluCylinder(	GLUquadric* quad, GLdouble base, GLdouble top, GLdouble height, GLint slices, GLint stacks);
      gluCylinder(yy, 0.5, 0.5, 1.75, 100, 100);

      // top of cylinder
      glPushMatrix();
        glTranslated(0.0f, 0.0f, 1.75);
        // (quad, inner, outer, slices, loops)
        gluDisk(yy, 0.0f, 0.5, 100, 100);
      glPopMatrix();

      //glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
      gluDisk(yy, 0.0f, 0.5, 100, 100);
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

  glEnable(GL_LIGHTING);

  createCans();
}


void display(void){
  glEnable(GL_LIGHT0);

  // Apaga ecra/profundidade
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glViewport (0, 0, wScreen, hScreen);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(angZoom, (float)wScreen/hScreen, 0.1, 5*zC);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(rVisao*cos(aVisao), obsP[1] + TRANSLATE_USER_Y, rVisao*sin(aVisao), LOOK_X, LOOK_Y, LOOK_Z, 0, 1, 0);

  // Objectos
  // drawEixos();
  drawCubeMap();
  drawScene();

  // Actualizacao
  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
    // aproxima do centro ao inicio
    case 'o':
      rVisao -= 1;
      glutPostRedisplay();
      break;

    // afasta do centro ao inicio
    case 'p':
      rVisao += 1;
      glutPostRedisplay();
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

    case 27:
      exit(0);
      break;
  }
}

void teclasNotAscii(int key, int x, int y){

  if(key == GLUT_KEY_UP)
    obsP[1] = (obsP[1]+ 0.1) ;
  if(key == GLUT_KEY_DOWN)
    obsP[1] = (obsP[1]- 0.1) ;

  if (obsP[1]>yC)
    obsP[1]=yC;
  if (obsP[1]<-yC)
    obsP[1]=-yC;

  if(key == GLUT_KEY_LEFT)
    aVisao = (aVisao + 0.1) ;
  if(key == GLUT_KEY_RIGHT)
    aVisao = (aVisao - 0.1) ;

  obsP[0] = rVisao*cos(aVisao);
  obsP[2] = rVisao*sin(aVisao);

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
  glutCreateWindow ("");

  inicializa();

  glutSpecialFunc(teclasNotAscii);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(msec, Timer, 1);

  glutMainLoop();

  glDisable(GL_COLOR_MATERIAL);

  return 0;
}
