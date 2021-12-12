#define _USE_MATH_DEFINES
#include <cmath>
#include <random>
#include <cstdio>
#include <GL/freeglut.h>
#include "include/main.h"

constexpr auto windowTitle = "Projeto CG | ramachado@student.dei.uc.pt";
constexpr auto world = 10;

// Window size (automatically refreshed by reshaping the window)
int windowWidth = 800, windowHeight = 600;

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(20, 20);
	glutCreateWindow(windowTitle);

	init();

	glutDisplayFunc(draw);		  // Display Callback
	glutKeyboardFunc(keyboard);	  // Keyboard (ASCII) Callback
	glutSpecialFunc(special);	  // Keyboard (Non-ASCII) Callback
	glutMotionFunc(mouse);		  // Mouse Callback #1
	glutMouseFunc(wheel);		  // Mouse Callback #2
	glutTimerFunc(0, timer, 0);	  // Timer #1 - Redisplay
	glutTimerFunc(0, eqTimer, 1); // Timer #2 - EQ
	glutReshapeFunc(reshape);	  // Reshape Callback

	glutMainLoop();
	return 1;
}

// Draws the 3-dimensional axis
void drawAxis() {
	GLboolean lights = glIsEnabled(GL_LIGHTING);
	if (lights) glDisable(GL_LIGHTING);
	glLineWidth(1);

	// X axis
	glColor4d(RED);
	glBegin(GL_LINES); {
		glVertex3d(0, 0, 0);
		glVertex3i(world, 0, 0);
	} glEnd();

	// Y axis
	glColor4d(GREEN);
	glBegin(GL_LINES); {
		glVertex3d(0, 0, 0);
		glVertex3d(0, world, 0);
	} glEnd();

	// Z axis
	glColor4d(BLUE);
	glBegin(GL_LINES); {
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0, world);
	} glEnd();
	if (lights) glEnable(GL_LIGHTING);
}

// Camera variables (using polar coordinates)
constexpr auto angleMin = -20, angleMax = -340, angleIncrement = -5;
struct camera {
	const GLdouble fov = 70, visionIncrement = 0.2;
	GLdouble radius = 10;
	GLdouble theta = 0;
	GLdouble phi = M_PI / 3;
	GLdouble obs[3];
} Camera;

// Interactive elements
mixerSettings interactive;
bars eq;

// Global Lighting
struct ambient {
	GLboolean enabled = true;
	GLfloat intensity = 0.2;
	GLfloat light[4] = {0, 0, 0, 1};
	GLfloat dark[4] = {0, 0, 0, 1};
	void init() {
		for (int i = 0; i < 3; i++) light[i] = intensity;
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light);
	}
} Ambient;

// OpenGL and interactive elements init
void init() {
	glClearColor(BLACK);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Lighting
	glEnable(GL_LIGHTING);
	Ambient.init();

	// Textures
	initTextures();

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

const char colours[4][6] = {"White", "Red", "Green", "Blue"};

struct {
	GLfloat intensity = 1;
	GLfloat color[3] = {1, 1, 1};
	GLfloat ambient[3] = {0, 0, 0};
	GLfloat diffuse[3];
	GLfloat specular[3];
	GLfloat position[4] = {0, 10, 15, 1};
	GLfloat direction[3] = {0, -1, -1};
	GLint cutoff = 25;
	GLint exponent = 50;
	short mode = 0;
	void cycle() {
		if (!glIsEnabled(GL_LIGHT1)) return;
		mode = (mode + 1) % 4;
		if (mode != 0) for (int i = 0; i < 3; i++) color[i] = 0;
		switch (mode) {
		case 0:
			for (int i = 0; i < 3; i++) color[i] = 1;
		case 1:
			color[0] = 1;
			break;
		case 2:
			color[1] = 1;
			break;
		case 3:
			color[2] = 1;
			break;
		}
	}
} SpotLight;

struct {
	GLfloat intensity = 0.2;
	GLfloat color[3] = {1, 1, 1};
	GLfloat ambient[3] = {0, 0, 0};
	GLfloat diffuse[3];
	GLfloat specular[3];
	GLfloat position[4] = {0, 5, -5, 1};
	bool discoMode = false;
	short mode = 0;
	void cycle() {
		if (!glIsEnabled(GL_LIGHT0)) return;
		mode = (mode + 1) % 4;
		if (mode != 0) for (int i = 0; i < 3; i++) color[i] = 0;
		switch (mode) {
		case 0:
			for (int i = 0; i < 3; i++) color[i] = 1;
		case 1:
			color[0] = 1;
			break;
		case 2:
			color[1] = 1;
			break;
		case 3:
			color[2] = 1;
			break;
		}
	}
} PointLight;

void lighting() {
	for (int i = 0; i < 3; i++) {
		SpotLight.ambient[i] = SpotLight.color[i] * SpotLight.intensity;
		SpotLight.diffuse[i] = SpotLight.color[i] * SpotLight.intensity;
		SpotLight.specular[i] = SpotLight.color[i] * SpotLight.intensity;
		PointLight.ambient[i] = PointLight.color[i] * PointLight.intensity;
		PointLight.diffuse[i] = PointLight.color[i] * PointLight.intensity;
		PointLight.specular[i] = PointLight.color[i] * PointLight.intensity;
	}

	glLightfv(GL_LIGHT0, GL_POSITION, PointLight.position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, PointLight.ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, PointLight.diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, PointLight.specular);

	glLightfv(GL_LIGHT1, GL_POSITION, SpotLight.position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, SpotLight.ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, SpotLight.diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpotLight.specular);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, SpotLight.direction);
	glLighti(GL_LIGHT1, GL_SPOT_EXPONENT, SpotLight.exponent);
	glLighti(GL_LIGHT1, GL_SPOT_CUTOFF, SpotLight.cutoff);
}

void lightPos(const GLfloat pos[3]) {
	glDisable(GL_LIGHTING);
	glPushMatrix(); {
		glTranslated(pos[0], pos[1], pos[2]);
		cube(CUBE_WHITE);
	} glPopMatrix();
	glEnable(GL_LIGHTING);
}

bool enableMesh = true;
GLint meshCount = 128;
// Object drawing calls
void drawCalls(const GLboolean main) {
	lighting();
	if (main && glIsEnabled(GL_LIGHT0)) lightPos(PointLight.position);
	if (main && glIsEnabled(GL_LIGHT1)) lightPos(SpotLight.position);
	mixer(&interactive, &eq);
	floor(enableMesh, meshCount);
	table();
}

void printStats();

// Draw calls
void draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 2D Viewport for text rendering
	glViewport(0, windowHeight - 200, 100, 200);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	printStats();
	glEnable(GL_LIGHTING);

	// Main 3D view
	glViewport(0, 0, windowWidth, windowHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(Camera.fov, (GLdouble)windowWidth / (GLdouble)windowHeight, 0.1, (double)20 * world);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Camera.obs[0] = Camera.radius * sin(Camera.theta) * sin(Camera.phi);
	Camera.obs[1] = Camera.radius * cos(Camera.phi);
	Camera.obs[2] = Camera.radius * cos(Camera.theta) * sin(Camera.phi);
	gluLookAt(Camera.obs[0], Camera.obs[1], Camera.obs[2], 0, 0, 0, 0, 1, 0);

	drawCalls(true);

	// Top-down view
	glViewport(windowWidth - 105, windowHeight - 100, 100, 100);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 2, 0, 0, 0, 0, 0, 0, -1);

	drawCalls(false);

	// Front view
	glViewport(windowWidth - 105, windowHeight - 200, 100, 100);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-5, 5, -5, 5, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);

	drawCalls(false);

	glutSwapBuffers();
}

// Keyboard (ASCII) event handler
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
	case 'g':
		interactive.slider += 0.1;
		if (interactive.slider > 0.5) interactive.slider = 0.5;
		break;
	case 't':
		interactive.slider -= 0.1;
		if (interactive.slider < -0.5) interactive.slider = -0.5;
		break;
	case 'z': // Button #1
		interactive.pressed1 = !interactive.pressed1;
		break;
	case 'x': // Button #2
		interactive.pressed2 = !interactive.pressed2;
		break;
	case 'c': // Button #3
		interactive.pressed3 = !interactive.pressed3;
		break;
	case 'v': // Button #4
		interactive.pressed4 = !interactive.pressed4;
		break;
		// Camera FOV controls
	case '+':
		Camera.radius--;
		if (Camera.radius < 3) Camera.radius = 3;
		break;
	case '-':
		Camera.radius++;
		if (Camera.radius > 50) Camera.radius = 50;
		break;
		// Lighting
	case '1':
		if (Ambient.enabled) glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Ambient.dark);
		else glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Ambient.light);
		Ambient.enabled = !Ambient.enabled;
		break;
	case '2':
		if (glIsEnabled(GL_LIGHT1)) glDisable(GL_LIGHT1);
		else glEnable(GL_LIGHT1);
		break;
	case '3':
		if (glIsEnabled(GL_LIGHT0)) glDisable(GL_LIGHT0);
		else glEnable(GL_LIGHT0);
		break;
	case '9':
		PointLight.cycle();
		break;
	case '8':
		if (glIsEnabled(GL_LIGHT0)) PointLight.intensity += 0.05;
		break;
	case '7':
		if (glIsEnabled(GL_LIGHT0)) {
			PointLight.intensity -= 0.05;
			if (PointLight.intensity < 0) PointLight.intensity = 0;
		}
		break;
	case '6':
		SpotLight.cycle();
		break;
	case '5':
		if (glIsEnabled(GL_LIGHT1)) SpotLight.intensity += 0.1;
		break;
	case '4':
		if (glIsEnabled(GL_LIGHT1)) {
			SpotLight.intensity -= 0.1;
			if (SpotLight.intensity < 0) SpotLight.intensity = 0;
		}
		break;
		// Mesh Controls
	case 'm':
		enableMesh = !enableMesh;
		break;
	case ',':
		meshCount /= 2;
		break;
	case '.':
		meshCount *= 2;
		break;
		// Quit
	case 27:
		glutLeaveMainLoop();
		exit(0);
		break;
	}
}

// Keyboard (non-ascii) event handler
void special(int key, int x, int y) {
	switch (key) {
		// Camera rotation (using polar coordinates)
	case GLUT_KEY_UP:
		Camera.phi -= Camera.visionIncrement;
		if (Camera.phi <= 0) Camera.phi = 0.001;
		break;
	case GLUT_KEY_DOWN:
		Camera.phi += Camera.visionIncrement;
		if (Camera.phi > M_PI) Camera.phi = M_PI;
		break;
	case GLUT_KEY_LEFT:
		Camera.theta -= Camera.visionIncrement;
		break;
	case GLUT_KEY_RIGHT:
		Camera.theta += Camera.visionIncrement;
		break;
		// Fullscreen toggle
	case GLUT_KEY_F11:
		glutFullScreenToggle();
		break;
	}
}

// C++ random generators
std::random_device rd;
std::uniform_real_distribution<GLdouble> d(0, 5);
constexpr auto eqFps = 20, eqMsec = 1000 / eqFps;

// Create random values for EQ bar scale
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

void rasterText(const char *str, GLint x, GLint y) {
	glColor4d(WHITE);
	glRasterPos2i(x, y);
	while (*str)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *str++);
}

void printStats() {
	char str[BUFSIZ];
	const int offset = 15, x = 10;
	int y = 180;
	if (Ambient.enabled) {
		snprintf(str, sizeof str, "Ambient Intensity: %.2f", Ambient.intensity);
		rasterText(str, x, y);
	} else rasterText("Ambient Light off", x, y);
	y -= offset;
	if (glIsEnabled(GL_LIGHT1)) {
		snprintf(str, sizeof str, "Spot Light Position: (%.2f, %.2f, %.2f)",
				 SpotLight.position[0], SpotLight.position[1], SpotLight.position[2]);
		rasterText(str, x, y);
		y -= offset;
		snprintf(str, sizeof str, "Spot Light Color: %s", colours[SpotLight.mode]);
		rasterText(str, x, y);
		y -= offset;
		snprintf(str, sizeof str, "Spot Light Intensity: %.2f", SpotLight.intensity);
		rasterText(str, x, y);
	} else rasterText("Spot Light off", x, y);
	y -= offset;
	if (glIsEnabled(GL_LIGHT0)) {
		snprintf(str, sizeof str, "Point Light Position: (%.2f, %.2f, %.2f)",
				 PointLight.position[0], PointLight.position[1], PointLight.position[2]);
		rasterText(str, x, y);
		y -= offset;
		snprintf(str, sizeof str, "Point Light Color: %s", colours[PointLight.mode]);
		rasterText(str, x, y);
		y -= offset;
		snprintf(str, sizeof str, "Point Light Intensity: %.2f", PointLight.intensity);
		rasterText(str, x, y);
	} else rasterText("Point Light off", x, y);
	y -= offset;
	if (enableMesh) {
		snprintf(str, sizeof str, "Mesh: %dx%d", meshCount, meshCount);
		rasterText(str, x, y);
	}
	else rasterText("Mesh disabled", x, y);
}

constexpr auto fps = 60, msec = 1000 / fps;

// Calls glutPostRedisplay at a rate of 60 fps, and handles button animation
void timer(int value) {
	glutTimerFunc(msec, timer, 0);

	// Smooth press down
	if (interactive.pressed1 && interactive.button1 >= -0.05)
		interactive.button1 -= 0.01;
	if (interactive.pressed2 && interactive.button2 >= -0.05)
		interactive.button2 -= 0.01;
	if (interactive.pressed3 && interactive.button3 >= -0.05)
		interactive.button3 -= 0.01;
	if (interactive.pressed4 && interactive.button4 >= -0.05)
		interactive.button4 -= 0.01;

	// Smooth bounce up
	if (!interactive.pressed1 && interactive.button1 <= 0)
		interactive.button1 += 0.01;
	if (!interactive.pressed2 && interactive.button2 <= 0)
		interactive.button2 += 0.01;
	if (!interactive.pressed3 && interactive.button3 <= 0)
		interactive.button3 += 0.01;
	if (!interactive.pressed4 && interactive.button4 <= 0)
		interactive.button4 += 0.01;

	glutPostRedisplay();
}

int prevX = 0, prevY = 0;

// Handles orbital controls using the mouse
// Drag the mouse to rotate around the object
void mouse(int x, int y) {
	if (x - prevX > 0) Camera.theta -= Camera.visionIncrement / 4;
	if (x - prevX < 0) Camera.theta += Camera.visionIncrement / 4;
	if (y - prevY > 0) Camera.phi -= Camera.visionIncrement / 4;
	if (y - prevY < 0) Camera.phi += Camera.visionIncrement / 4;

	if (Camera.phi > M_PI) Camera.phi = M_PI;
	if (Camera.phi <= 0) Camera.phi = 0.001;

	prevX = x;
	prevY = y;
}

// Mouse wheel handler to control FOV (zoom)
void wheel(int button, int state, int x, int y) {
	if (button == 3 && state == GLUT_DOWN) Camera.radius--;
	if (button == 4 && state == GLUT_DOWN) Camera.radius++;

	if (Camera.radius < 3) Camera.radius = 3;
	if (Camera.radius > 50) Camera.radius = 50;
}

// Reshape handler to ensure resizing of viewport
void reshape(int w, int h) {
	if (h == 0) h = 1;

	windowWidth = w;
	windowHeight = h;
}
