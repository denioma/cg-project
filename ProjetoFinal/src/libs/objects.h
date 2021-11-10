#pragma once
#include <GL/freeglut.h>

typedef struct {
	GLdouble knob1;
	GLdouble knob2;
	GLdouble knob3;
	GLdouble knob4;
	GLdouble button1;
	GLdouble button2;
	GLdouble button3;
	GLdouble button4;
	GLdouble slider;
	GLboolean pressed1;
	GLboolean pressed2;
	GLboolean pressed3;
	GLboolean pressed4;
} mixerSettings;

typedef struct {
	GLdouble bar1;
	GLdouble bar2;
	GLdouble bar3;
	GLdouble bar4;
} bars;

void equalizer(const bars*);
void mixer(const mixerSettings*, const bars*);
void button();
