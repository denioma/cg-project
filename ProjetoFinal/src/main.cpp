#define _USE_MATH_DEFINES
#include <cmath>
#include <random>
#include <cstdio>
#include <GL/freeglut.h>

#include "libs/palette.h"
#include "libs/geometry.h"
#include "libs/objects.h"

constexpr auto windowTitle = "Simple Audio Mixer";
constexpr auto windowWidth = 600, windowHeight = 600, world = 10;
constexpr auto fps = 60, msec = 1000/fps;

void init();
void draw();
void keyboard(unsigned char, int, int);
void special(int, int, int);
void timer(int);
void eqTimer(int);
void equalizer();

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(50, 50);
	glutCreateWindow(windowTitle);

	init();

	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutTimerFunc(0, timer, 0);
	glutTimerFunc(0, eqTimer, 1);

	glutMainLoop();
	return 1;
}

void drawAxis() {
	glColor4d(RED);
	glBegin(GL_LINES); {
		glVertex3d(0, 0, 0);
		glVertex3i(world, 0, 0);
	} glEnd();

	glColor4d(GREEN);
	glBegin(GL_LINES); {
		glVertex3d(0, 0, 0);
		glVertex3d(0, world, 0);
	} glEnd();

	glColor4d(BLUE);
	glBegin(GL_LINES); {
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0, world);
	} glEnd();
}

// Camera variables
const GLdouble visionRadius = 10, visionIncrement= 0.2, camIncrement = 0.25;
GLdouble fov = 45, visionAngle = 0.5 * M_PI;
GLdouble obs[] = { visionRadius * cos(visionAngle), 1, visionRadius*sin(visionAngle) };

mixerSettings interactive;
bars eq;
constexpr auto angleMin = -20, angleMax = -340, angleIncrement = 5;

void init() {
	glClearColor(WHITE);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glLineWidth(2);
	
	interactive.slider = 0;
	interactive.knob1 = angleMin;
	interactive.knob2 = angleMin;
	interactive.knob3 = angleMin;
	interactive.knob4 = angleMin;
	interactive.pressed1 = false;
	interactive.pressed2 = false;
	interactive.pressed3 = false;
	interactive.pressed4 = false;
}


void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, windowWidth / windowHeight, 0.1, (double)3 * world);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obs[0], obs[1], obs[2], 0, 0, 0, 0, 1, 0);

	drawAxis();
	mixer(&interactive, &eq);
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	switch (tolower(key)) {
	case 'w':
		interactive.knob1 -= angleIncrement;
		if (interactive.knob1 < angleMax) interactive.knob1 = angleMax;
		break;
	case 'q':
		interactive.knob1 += angleIncrement;
		if (interactive.knob1 > angleMin) interactive.knob1 = angleMin;
		break;
	case 's':
		interactive.knob2 -= angleIncrement;
		if (interactive.knob2 < angleMax) interactive.knob2 = angleMax;
		break;
	case 'a':
		interactive.knob2 += angleIncrement;
		if (interactive.knob2 > angleMin) interactive.knob2 = angleMin;
		break;
	case 'p':
		interactive.knob3 -= angleIncrement;
		if (interactive.knob3 < angleMax) interactive.knob3 = angleMax;
		break;
	case 'o':
		interactive.knob3 += angleIncrement;
		if (interactive.knob3 > angleMin) interactive.knob3 = angleMin;
		break;
	case 'l':
		interactive.knob4 -= angleIncrement;
		if (interactive.knob4 < angleMax) interactive.knob4 = angleMax;
		break;
	case 'k':
		interactive.knob4 += angleIncrement;
		if (interactive.knob4 > angleMin) interactive.knob4 = angleMin;
		break;
	case '1':
		interactive.slider -= 0.1;
		if (interactive.slider < -0.5) interactive.slider = -0.5;
		break;
	case '2':
		interactive.slider += 0.1;
		if (interactive.slider > 0.5) interactive.slider = 0.5;
		break;
	case 'e':
		interactive.pressed1 = !interactive.pressed1;
		break;
	case 'd':
		interactive.pressed2 = !interactive.pressed2;
		break;
	case 'i':
		interactive.pressed3 = !interactive.pressed3;
		break;
	case 'j':
		interactive.pressed4 = !interactive.pressed4;
		break;
	// Camera FOV controls
	case '+':
		fov -= 3;
		break;
	case '-':
		fov += 3;
		break;
	case 27:
		glutLeaveMainLoop();
		exit(0);
		break;
	}
}

void special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		obs[1] += camIncrement;
		break;
	case GLUT_KEY_DOWN:
		obs[1] -= camIncrement;
		break;
	case GLUT_KEY_LEFT:
		visionAngle += visionIncrement;
		obs[0] = visionRadius * cos(visionAngle);
		obs[2] = visionRadius * sin(visionAngle);
		break;
	case GLUT_KEY_RIGHT:
		visionAngle -= visionIncrement;
		obs[0] = visionRadius * cos(visionAngle);
		obs[2] = visionRadius * sin(visionAngle);
		break;
	case GLUT_KEY_F11:
		glutFullScreenToggle();
		break;
	}
}

GLdouble bar1, bar2, bar3, bar4, bar5;
std::random_device rd;
std::uniform_real_distribution<GLdouble> d(0, 5);

constexpr auto eqFps = 20, eqMsec = 1000 / eqFps;

void eqTimer(int value) {
	glutTimerFunc(eqMsec, eqTimer, 1);
	if (interactive.pressed1) eq.bar1 = d(rd);
	else eq.bar1 = 0;
	if (interactive.pressed2) eq.bar2 = d(rd);
	else eq.bar2 = 0;
	if (interactive.pressed3) eq.bar3 = d(rd);
	else eq.bar3 = 0;
	if (interactive.pressed4) eq.bar4 = d(rd);
	else eq.bar4 = 0;
	eq.bar5 = d(rd);
}

void timer(int value) {
	glutTimerFunc(msec, timer, 0);

	if (interactive.pressed1 && interactive.button1 >= -0.05) interactive.button1 -= 0.01;
	if (interactive.pressed2 && interactive.button2 >= -0.05) interactive.button2 -= 0.01;
	if (interactive.pressed3 && interactive.button3 >= -0.05) interactive.button3 -= 0.01;
	if (interactive.pressed4 && interactive.button4 >= -0.05) interactive.button4 -= 0.01;

	if (!interactive.pressed1 && interactive.button1 <= 0) interactive.button1 += 0.01;
	if (!interactive.pressed2 && interactive.button2 <= 0) interactive.button2 += 0.01;
	if (!interactive.pressed3 && interactive.button3 <= 0) interactive.button3 += 0.01;
	if (!interactive.pressed4 && interactive.button4 <= 0) interactive.button4 += 0.01;

	glutPostRedisplay();
}
