#define _USE_MATH_DEFINES
#include <cmath>
#include <random>
#include <cstdio>
#include <GL/freeglut.h>

#include "libs/palette.h"
#include "libs/geometry.h"
#include "libs/objects.h"

constexpr auto windowTitle = "Simple Audio Mixer";
constexpr auto world = 10;

int windowWidth = 800, windowHeight = 600;

void init();
void draw();
void keyboard(unsigned char, int, int);
void special(int, int, int);
void timer(int);
void eqTimer(int);
void mouse(int, int);
void wheel(int, int, int, int);
void reshape(int, int);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(20, 20);
	glutCreateWindow(windowTitle);

	init();

	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMotionFunc(mouse);
	glutMouseFunc(wheel);
	glutTimerFunc(0, timer, 0);
	glutTimerFunc(0, eqTimer, 1);
	glutReshapeFunc(reshape);

	glutMainLoop();
	return 1;
}

void drawAxis() {
	glLineWidth(1);
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
const GLdouble visionRadius = 10, visionIncrement = 0.2, camIncrement = 0.25;
GLdouble fov = 45, visionAngle = 0, vertAngle = M_PI/3;
GLdouble obs[3] = {
	
};
mixerSettings interactive;
bars eq;
constexpr auto angleMin = -20, angleMax = -340, angleIncrement = -5;

void init() {
	glClearColor(WHITE);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	interactive.slider = 0.5;
	interactive.knob1 = angleMin;
	interactive.knob2 = angleMin;
	interactive.knob3 = angleMin;
	interactive.knob4 = angleMin;
	interactive.pressed1 = false;
	interactive.pressed2 = false;
	interactive.pressed3 = false;
	interactive.pressed4 = false;
}

void drawCalls(const GLboolean axis) {
	if (axis) drawAxis();
	mixer(&interactive, &eq);
}

void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, (GLdouble)windowWidth / (GLdouble)windowHeight, 0.1, (double)3 * world);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	obs[0] = visionRadius * sin(visionAngle) * sin(vertAngle);
	obs[1] = visionRadius * cos(vertAngle);
	obs[2] = visionRadius * cos(visionAngle) * sin(vertAngle);
	gluLookAt(obs[0], obs[1], obs[2], 0, 0, 0, 0, 1, 0);

	drawCalls(true);

	glViewport(windowWidth - 100, windowHeight - 100, 100, 100);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 2, 0, 0, 0, 0, 0, 0, -1);

	drawCalls(false);

	glViewport(windowWidth - 100, windowHeight - 200, 100, 100);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

	drawCalls(false);

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	switch (tolower(key)) {
	// Knob #1
	case 'q':
		interactive.knob1 += angleIncrement;
		if (interactive.knob1 < angleMax) interactive.knob1 = angleMax;
		break;
	case 'a':
		interactive.knob1 -= angleIncrement;
		if (interactive.knob1 > angleMin) interactive.knob1 = angleMin;
		break;
	// Knob #2	
	case 'w':
		interactive.knob2 += angleIncrement;
		if (interactive.knob2 < angleMax) interactive.knob2 = angleMax;
		break;
	case 's':
		interactive.knob2 -= angleIncrement;
		if (interactive.knob2 > angleMin) interactive.knob2 = angleMin;
		break;
	// Knob #3
	case 'e':
		interactive.knob3 += angleIncrement;
		if (interactive.knob3 < angleMax) interactive.knob3 = angleMax;
		break;
	case 'd':
		interactive.knob3 -= angleIncrement;
		if (interactive.knob3 > angleMin) interactive.knob3 = angleMin;
		break;
	// Knob #4
	case 'r':
		interactive.knob4 += angleIncrement;
		if (interactive.knob4 < angleMax) interactive.knob4 = angleMax;
		break;
	case 'f':
		interactive.knob4 -= angleIncrement;
		if (interactive.knob4 > angleMin) interactive.knob4 = angleMin;
		break;
	// Slider
	case '1':
		interactive.slider += 0.1;
		if (interactive.slider > 0.5) interactive.slider = 0.5;
		break;
	case '2':
		interactive.slider -= 0.1;
		if (interactive.slider < -0.5) interactive.slider = -0.5;
		break;
	case 'z':
		interactive.pressed1 = !interactive.pressed1;
		break;
	case 'x':
		interactive.pressed2 = !interactive.pressed2;
		break;
	case 'c':
		interactive.pressed3 = !interactive.pressed3;
		break;
	case 'v':
		interactive.pressed4 = !interactive.pressed4;
		break;
		// Camera FOV controls
	case '+':
		if (fov - 3 > 0) fov -= 3;
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
		//obs[1] -= camIncrement;
		vertAngle -= visionIncrement;
		if (vertAngle <= 0) vertAngle = 0.001;
		break;
	// Camera Y position
	case GLUT_KEY_DOWN:
		//obs[1] += camIncrement;
		vertAngle += visionIncrement;
		if (vertAngle > M_PI) vertAngle = M_PI;
		break;
	// Camera rotation (y plane)
	case GLUT_KEY_LEFT:
		visionAngle += visionIncrement;
		break;
	case GLUT_KEY_RIGHT:
		visionAngle -= visionIncrement;
		break;
	// Fullscreen toggle
	case GLUT_KEY_F11:
		glutFullScreenToggle();
		break;
	}
}

std::random_device rd;
std::uniform_real_distribution<GLdouble> d(0, 5);

constexpr auto eqFps = 20, eqMsec = 1000 / eqFps;

void eqTimer(int value) {
	glutTimerFunc(eqMsec, eqTimer, 1);
	GLdouble slider = -interactive.slider + 0.5;
	if (interactive.pressed1) eq.bar1 = d(rd) * slider;
	else eq.bar1 = 0;
	if (interactive.pressed2) eq.bar2 = d(rd) * slider;
	else eq.bar2 = 0;
	if (interactive.pressed3) eq.bar3 = d(rd) * slider;
	else eq.bar3 = 0;
	if (interactive.pressed4) eq.bar4 = d(rd) * slider;
	else eq.bar4 = 0;
}

constexpr auto fps = 60, msec = 1000 / fps;

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

int prevX = 0, prevY = 0;
void mouse(int x, int y) {
	if (x - prevX > 0) visionAngle -= visionIncrement/4;
	if (x - prevX < 0) visionAngle += visionIncrement/4;
	if (y - prevY > 0) vertAngle -= visionIncrement/4;
	if (y - prevY < 0) vertAngle += visionIncrement/4;
	
	if (vertAngle > M_PI) vertAngle = M_PI;
	if (vertAngle <= 0) vertAngle = 0.001;
	
	prevX = x;
	prevY = y;
}

void wheel(int button, int state, int x, int y) {
	if (button == 3 && state == GLUT_DOWN && fov - 3 > 0) fov -= 3;
	if (button == 4 && state == GLUT_DOWN) fov += 3;
}

void reshape(int w, int h) {
	if (h == 0) h = 1;

	windowWidth = w;
	windowHeight = h;
}