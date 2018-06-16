#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <vector>
#include <time.h>
#include "materiais.h"
#include "RgbImage.h"
#include "render.h"
#include "rain.h"

using namespace std;

// colors
#define BLUE      0.0, 0.0, 1.0, 1.0
#define RED	      1.0, 0.0, 0.0, 1.0
#define YELLOW	  1.0, 1.0, 0.0, 1.0
#define GREEN     0.0, 1.0, 0.0, 1.0
#define WHITE     1.0, 1.0, 1.0, 1.0
#define BLACK     0.0, 0.0, 0.0, 1.0
#define PI	      3.14159


//------------------------------------------------------------ CANS
int NUMBER_OF_CANS = 0;  // number of existing cans

struct Can {
  int texture;
  GLfloat angRotateX;
  GLfloat angRotateY;
  GLfloat angRotateZ;
  GLfloat translateCanX;
  GLfloat translateCanY;
  GLfloat translateCanZ;
  GLfloat incTranslateCanX;
  GLfloat incTranslateCanY;
  GLfloat incTranslateCanZ;
};

Can cans[50];

GLfloat incAngRotate = 1;

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

//------------------------------------------------------------ Sistema Coordenadas + objectos
// Janela (pixeis)
GLint wScreen = 1600;
GLint hScreen = 1200;

// Mundo
GLfloat xC = 20.0;
GLfloat yC = 20.0;
GLfloat zC = 20.0;

//------------------------------------------------------------ Observador
GLfloat rVisao = 18;
GLfloat aVisao = 0.5 * PI;
GLfloat incVisao = 0.05;
GLfloat obsP[] = {rVisao * cos(aVisao), 3, rVisao * sin(aVisao)};
GLfloat angZoom = 90;
GLfloat incZoom = 3;

GLfloat LOOK_X = 0;
GLfloat LOOK_Y = 5;
GLfloat LOOK_Z = 0;

GLint    msec = 1;					// definicao do timer (atualizacao)

// 0 -> without lights; 1 -> with lights
int MODE = 0;

// Object with methods needed to render
Render render;

Rain rain;

#endif
