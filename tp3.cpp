#include <stdlib.h>
#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <time.h>
#include <vector>
#include "RgbImage.h"


using namespace std;

#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED	 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PI		 3.14159

struct Can {
  int color_index;
};

vector <Can> CANS;

GLfloat tam = 2.0;
static GLfloat vertices[]={
  // x = tam (Esquerda)
  -tam,  -tam,  tam,	// 0
  -tam,   tam,  tam,	// 1
  -tam,   tam, -tam,	// 2
  -tam,  -tam, -tam,	// 3
  // Direita
  tam,  -tam,  tam,	// 4
  tam,   tam,  tam,	// 5
  tam,   tam, -tam,	// 6
  tam,  -tam, -tam,	// 7
  // Cima
  -tam,  tam,  tam,	// 8
  -tam,  tam, -tam,	// 9
  tam,  tam, -tam,	// 10
  tam,  tam,  tam,	// 11
};

static GLfloat normais[] = {
  // x=tam (Esquerda)
  -1.0,  0.0,  0.0,
  -1.0,  0.0,  0.0,
  -1.0,  0.0,  0.0,
  -1.0,  0.0,  0.0,
  // x=tam (Direita)
  1.0,  0.0,  0.0,
  1.0,  0.0,  0.0,
  1.0,  0.0,  0.0,
  1.0,  0.0,  0.0,
  //  y=tam (Cima)
  0.0,  1.0,  0.0,
  0.0,  1.0,  0.0,
  0.0,  1.0,  0.0,
  0.0,  1.0,  0.0,
};

//------------------------------------------------------------ Cores
static GLfloat cor[]={
  // x=tam (Esquerda) - Red
  1.0,  0.0, 0.0,	// 0
  1.0,  0.0, 0.0,	// 1
  1.0,  1.0, 0.0,	// 2
  1.0,  1.0, 0.0,	// 3
  // x=2*tam (Direita) - Green
  0.0,  1.0, 1.0,	// 4
  0.0,  1.0, 1.0,	// 5
  0.0,  1.0, 0.0,	// 6
  0.0,  1.0, 0.0,	// 7
  // y=tam (Cima) - Blue
  0.0,  0.0, 1.0,	// 8
  0.0,  0.0, 1.0,	// 9
  1.0,  0.0, 1.0,	// 10
  1.0,  0.0, 1.0,	// 11
};

//=========================================================== FACES DA MESA
static GLuint     cima[] = {8, 11, 10, 9};
static GLuint     esquerda[] = {0, 1, 2, 3};
static GLuint     direita[] = {4, 7, 6, 5};


//------------------------------------------------------------ Sistema Coordenadas + objectos
GLint		wScreen=800, hScreen=600;		//.. janela (pixeis)
GLfloat		xC=10.0, yC=10.0, zC=10.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Observador
GLfloat  rVisao = 10, aVisao=0.5*PI, incVisao=0.05;
GLfloat  obsP[] ={rVisao*cos(aVisao), 3, rVisao*sin(aVisao)};
GLfloat  angZoom=90;
GLfloat  incZoom=3;

GLfloat TRANSLATE_X = 0;
GLfloat TRANSLATE_USER_Y = 0;

GLfloat LOOK_X = 0;
GLfloat LOOK_Y = 0;
GLfloat LOOK_Z = 0;

GLfloat ROTATE = 0;


//------------------------------------------------------------ Texturas
GLuint  texture[1];
GLuint  tex;
RgbImage imag;


void textures() {

  // Textura Coca cola

  // Cria o identificador de uma textura
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

  // Especifica a forma de mapeamento (combinação de imagem e textura)
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

  // Propriedades
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

  // Construir textura
  imag.LoadBmpFile("mesa.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData()
  );
}


void inicializa(void) {
  glClearColor(BLACK);		// Apagar
  glEnable(GL_DEPTH_TEST);	// Profundidade
  glShadeModel(GL_SMOOTH);	// Interpolacao de cores
  textures();
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
  glVertex3i( 0, 0, 0);
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
  glVertex3i( 0, 0, 0);
  glVertex3i( 0, 0, 10);
  glEnd();
}

//==================================== Lata
void createCan(int x, int y, int z) {

  // create colors matrix
  float colours[6][4] = {
    BLUE,
    RED,
    YELLOW,
    GREEN,
    WHITE,
    BLACK
  };


  // get random index
  srand (time(NULL));
  int random_index = rand() % 5 + 0;

  //glColor4f(colours[random_index][0], colours[random_index][1], colours[random_index][2], colours[random_index][3]);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture[0]);

  glPushMatrix();
    glTranslated(x, y, z);
    GLUquadricObj* yy = gluNewQuadric();
    gluQuadricDrawStyle ( yy, GLU_FILL   );
    gluQuadricNormals   ( yy, GLU_SMOOTH );
    gluQuadricTexture   ( yy, GL_TRUE    );
    gluCylinder(yy, 2, 2, 4, 100, 100);
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);
}


void drawScene(){
  //=================================================== Qual o lado ?
  glCullFace(GL_FRONT);  //glFrontFace(GL_CW);

  glTranslated(TRANSLATE_X, 0, 0);
  glTranslated(0, 2, 0);
  glRotated(ROTATE, 1, 0, 0);
  glTranslated(0, -2, 0);

  for (int i = 0; i < 4; i++) {
    createCan(0, i * 5, 0);
  }
}


void display(void){

  //================================================================= Apaga ecran/profundidade
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  //================================================================= No modificar
  glViewport (0, 0, wScreen, hScreen);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(angZoom, (float)wScreen/hScreen, 0.1, 3*zC);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(rVisao*cos(aVisao), obsP[1] + TRANSLATE_USER_Y, rVisao*sin(aVisao), LOOK_X, LOOK_Y, LOOK_Z, 0, 1, 0);

  //================================================================= No modificar

  //Objectos
  drawEixos();
  drawScene();

  //Actualizacao
  glutSwapBuffers();
}

//======================================================= EVENTOS
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



int main(int argc, char** argv){

  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize (wScreen, hScreen);
  glutInitWindowPosition (300, 100);
  glutCreateWindow ("{jh,pjmm}@dei.uc.pt|       |FaceVisivel:'f'|      |Observador:'SETAS'|        |Andar-'a/s'|        |Rodar -'e/d'| ");

  inicializa();

  glutSpecialFunc(teclasNotAscii);
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);

  glutMainLoop();

  return 0;
}
