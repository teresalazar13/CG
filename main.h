#ifndef MAIN_HEADER
#define MAIN_HEADER

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <vector>
#include <math.h>
#include <time.h>
#include "RgbImage.h"
#include "render.h"
#include "rain.h"

using namespace std;


#define BLACK     0.0, 0.0, 0.0, 1.0
#define PI	      3.14159


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

// Janela (pixeis)
GLint wScreen = 1600;
GLint hScreen = 1200;

// Mundo
GLfloat xC = 20.0;
GLfloat yC = 20.0;
GLfloat zC = 20.0;

// Observador
GLfloat rVisao = 18;
GLfloat aVisao = 0.5 * PI;
GLfloat incVisao = 0.05;
GLfloat obsP[] = {rVisao * cos(aVisao), 3, rVisao * sin(aVisao)};
GLfloat angZoom = 90;
GLfloat incZoom = 3;

GLfloat LOOK_X = 0;
GLfloat LOOK_Y = 5;
GLfloat LOOK_Z = 0;

GLint msec = 1;	// definicao do timer (atualizacao)

// 0: without lights; 1: with lights
int LIGHT_MODE = 0;
// 0: without rain; 1: with rain
int RAIN_MODE = 1;

// Objects with methods needed to render
Render render;
Rain rain;

#endif
