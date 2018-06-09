#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <time.h>
#include <vector>
#include "materiais.h"
#include "RgbImage.h"
#include "render.h"

using namespace std;

// colors
#define BLUE      0.0, 0.0, 1.0, 1.0
#define RED	  1.0, 0.0, 0.0, 1.0
#define YELLOW	  1.0, 1.0, 0.0, 1.0
#define GREEN     0.0, 1.0, 0.0, 1.0
#define WHITE     1.0, 1.0, 1.0, 1.0
#define BLACK     0.0, 0.0, 0.0, 1.0
#define PI	  3.14159


// saves info needed to render can
struct Can {
  int texture;
};

// number of cans possible
Can cans[50];

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

//------------------------------------------------------------ Sistema Coordenadas + objectos
GLint		wScreen=1600, hScreen=1200;		//.. janela (pixeis)
GLfloat		xC=20.0, yC=20.0, zC=20.0;		//.. Mundo  (unidades mundo)

//------------------------------------------------------------ Observador
GLfloat  rVisao = 18, aVisao=0.5*PI, incVisao=0.05;
GLfloat  obsP[] = {rVisao * cos(aVisao), 3, rVisao * sin(aVisao)};
GLfloat  angZoom=90;
GLfloat  incZoom=3;

GLfloat TRANSLATE_X = 0;

GLfloat LOOK_X = 0;
GLfloat LOOK_Y = 5;
GLfloat LOOK_Z = 0;

GLint    msec = 1;					//.. definicao do timer (actualizacao)

GLfloat  angRotateX[50] = {0};
GLfloat  angRotateY[50] = {0};
GLfloat  angRotateZ[50] = {0};

GLfloat  incAngRotate = 1;

GLfloat  translateCanX[50] = {0};
GLfloat  incTranslateCanX[50] = {0.1};

GLfloat  translateCanY[50] = {0};
GLfloat  incTranslateCanY[50] = {0.1};

GLfloat  translateCanZ[50] = {0};
GLfloat  incTranslateCanZ[50] = {0.1};

// number of existing cans
int NUMBER_OF_CANS = 0;

//============================= Iluminacao

// meter varios tipos de focos com angulos diferentes e cores diferentes
// 1;0;0 para amb dif e especular faz um foco vermelhokk

// Object with methods needed to render
Render render;

#endif
