#include <cmath>

#include "../include/objects.h"
#include "../include/geometry.h"
#include "../include/palette.h"
#include "../include/materials.h"
#include "../include/textures.h"

void slider(const GLdouble* pos) {
	const GLdouble baseWidth = 0.5, baseHeight = 0.2, baseDepth = 0.2;
	const GLdouble accentWidth = 0.75 * baseWidth, accentHeight = 0.5 * baseHeight, accentDepth = 0.5 * baseDepth;
	GLdouble base[] = {
		LIGHTGRAY, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY,
		LIGHTGRAY, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY,
		LIGHTGRAY, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY,
		LIGHTGRAY, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY,
		LIGHTGRAY, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY,
		LIGHTGRAY, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY
	};

	GLdouble accent[] = {
		WHITE, WHITE, WHITE, WHITE,
		WHITE, WHITE, WHITE, WHITE,
		WHITE, WHITE, WHITE, WHITE,
		WHITE, WHITE, WHITE, WHITE,
		WHITE, WHITE, WHITE, WHITE,
		WHITE, WHITE, WHITE, WHITE
	};

	// Slider horizontal line
	initMaterial(materials::whitePlastic);
	glLineWidth(2);
	glBegin(GL_LINES); {
		glVertex3d(0, 0, -0.5);
		glVertex3d(0, 0, 0.5);
	} glEnd();

	glPushMatrix(); {
		// Slides the control over the line
		glTranslated(0, 0, *pos);

		// Slider Accent
		glPushMatrix(); {
			glTranslated(0, 0.75 * accentHeight, 0);
			glScaled(accentWidth, accentHeight, accentDepth);
			cube(accent);
		} glPopMatrix();

		// Base control
		initMaterial(materials::blackPlastic);
		glPushMatrix(); {
			glScaled(baseWidth, baseHeight, baseDepth);
			cube(base);
		} glPopMatrix();


	} glPopMatrix();
}

void knob(const GLdouble* angle) {
	GLdouble red[] = {
		RED, RED, RED, RED,
		RED, RED, RED, RED,
		RED, RED, RED, RED,
		RED, RED, RED, RED,
		RED, RED, RED, RED,
		RED, RED, RED, RED
	};
	glPushMatrix(); {
		initMaterial(materials::blackPlastic);
		glRotated(*angle, 0, 1, 0);
		glColor4d(LIGHTGRAY);
		glPushMatrix(); {
			glScaled(0.2, 0.3, 0.2);
			glRotated(90, 1, 0, 0);
			glTranslated(0, 0, -0.5);
			glutSolidCylinder(1, 1, 50, 50);
		} glPopMatrix();

		initMaterial(materials::redPlastic);
		glPushMatrix(); {
			glTranslated(0, 0.02, 0.1);
			glScaled(0.05, 0.34, 0.2);
			cube(red);
		} glPopMatrix();
	} glPopMatrix();
}

void button() {
	initMaterial(materials::redPlastic);
	glPushMatrix(); {
		glScaled(0.1, 0.15, 0.1);
		glRotated(90, 1, 0, 0);
		glTranslated(0, 0, -0.5);
		glutSolidCylinder(1, 1, 50, 50);
	} glPopMatrix();
}

void equalizer(const bars* eq, const mixerSettings* interactive) {
	glDisable(GL_LIGHTING);
	constexpr auto spacing = 0.5;

	const GLdouble colours[] = {
		GREEN, GREEN, GREEN, GREEN,
		GREEN, GREEN, GREEN, GREEN,
		GREEN, GREEN, GREEN, GREEN,
		GREEN, GREEN, GREEN, GREEN,
		GREEN, GREEN, GREEN, GREEN,
		GREEN, GREEN, GREEN, GREEN
	};

	initMaterial(materials::redPlastic);
	glPushMatrix(); {
		//glScaled(1, 1, 0);
		if (interactive->pressed1) {
			glPushMatrix(); {
				glTranslated(-1.8, 0, 0);
				glScaled(1, 1, eq->bar1);
				cube(colours);
			} glPopMatrix();
		}
		if (interactive->pressed2) {
			glPushMatrix(); {
				glTranslated(-0.6, 0, 0);
				glScaled(1, 1, eq->bar2);
				cube(colours);
			} glPopMatrix();
		}
		if (interactive->pressed3) {
			glPushMatrix(); {
				glTranslated(0.6, 0, 0);
				glScaled(1, 1, eq->bar3);
				cube(colours);
			} glPopMatrix();
		}
		if (interactive->pressed4) {
			glPushMatrix(); {
				glTranslated(1.8, 0, 0);
				glScaled(1, 1, eq->bar4);
				cube(colours);
			} glPopMatrix();
		}
	} glPopMatrix();

	glEnable(GL_LIGHTING);
}

void mixer(const mixerSettings* interactive, const bars* eq) {
	const GLdouble width = 6, height = 1, depth = 4;
	const GLdouble base[] = {
		GRAY, GRAY, GRAY, GRAY,	// Left
		GRAY, GRAY, GRAY, GRAY,	// Right
		GRAY, GRAY, GRAY, GRAY,	// Top (Maybe change this to a dark accent colour?)
		GRAY, GRAY, GRAY, GRAY,	// Bottom
		GRAY, GRAY, GRAY, GRAY,	// Front
		GRAY, GRAY, GRAY, GRAY	// Back
	};

	const GLdouble sides[] = {
		LIGHTGRAY, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY,	// Left
		LIGHTGRAY, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY,	// Right
		LIGHTGRAY, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY,	// Top (Maybe change this to a dark accent colour?)
		LIGHTGRAY, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY,	// Bottom
		LIGHTGRAY, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY,	// Front
		LIGHTGRAY, LIGHTGRAY, LIGHTGRAY, LIGHTGRAY	// Back
	};

	initMaterial(materials::blackPlastic);
	glPushMatrix(); {
		glScaled(width, height, depth);
		cube(base);
	} glPopMatrix();

	initMaterial(materials::silver);
	for (int i = -1; i <= 1; i += 2) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, metal);
		glPushMatrix(); {
			glTranslated(width / 2 * i, 0, 0);
			glScaled(1, height + 0.1, depth + 0.1);
			cube(sides);
		} glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
	
	const GLdouble offset = -width / 2 + 1;

	glPushMatrix(); {
		// Knob height: 0.3 -> Half: 0.15
		glTranslated(offset, height / 2 + 0.15, 1);
		knob(&interactive->knob1);
		glTranslated(0, -0.15 / 2 + interactive->button1, 0.5);
		button();
	} glPopMatrix();

	glPushMatrix(); {
		// Knob height: 0.3 -> Half: 0.15
		glTranslated(offset + 1, height / 2 + 0.15, 1);
		knob(&interactive->knob2);
		glTranslated(0, -0.15 / 2 + interactive->button2, 0.5);
		button();
	} glPopMatrix();

	glPushMatrix(); {
		// Knob height: 0.3 -> Half: 0.15
		glTranslated(offset + 2, height / 2 + 0.15, 1);
		knob(&interactive->knob3);
		glTranslated(0, -0.15 / 2 + interactive->button3, 0.5);
		button();
	} glPopMatrix();

	glPushMatrix(); {
		// Knob height: 0.3 -> Half: 0.15
		glTranslated(offset + 3, height / 2 + 0.15, 1);
		knob(&interactive->knob4);
		glTranslated(0, -0.15 / 2 + interactive->button4, 0.5);
		button();
	} glPopMatrix();

	glPushMatrix(); {
		glTranslated(offset + 4, height / 2, 1);
		glScaled(1, 1, 1);
		slider(&interactive->slider);
	} glPopMatrix();


	glPushMatrix(); {
		glTranslated(0, (height + 1) / 2, -1);
		glRotated(45, 1, 0, 0);
		glPushMatrix(); {
			glScaled(width / 2, 0.1, depth / 2);
			cube(sides);
		} glPopMatrix();

		// Draw equalizer
		glPushMatrix(); {
			glTranslated(0, 0.15, 0.08);
			glScaled(0.25, 0.1, 0.25);
			equalizer(eq, interactive);
		} glPopMatrix();
	} glPopMatrix();
}

void table() {
	glBindTexture(GL_TEXTURE_2D, wood);
	glEnable(GL_TEXTURE_2D);
	initMaterial(materials::silver);
	for (int i = -1; i < 2; i += 2) {
		for (int j = -1; j < 2; j += 2) {
			glPushMatrix(); {
				glTranslated(4.5* i, -2.5, 2.5 * j);
				glScaled(0.5, 3, 0.5);
				cube(NULL);
			} glPopMatrix();
		}
	}
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	initMaterial(materials::glass);
	glPushMatrix(); {
		glTranslated(0, -0.75, 0);
		glScaled(10, 0.5, 6);
		cube(NULL);
	} glPopMatrix();
	glDisable(GL_BLEND);
}

void mesh(GLdouble count) {
	int i, j;
	GLdouble half = count / 2;
	glPushMatrix(); {
		glTranslated(-0.5, 0, -0.5);
		glBegin(GL_POLYGON);
		glNormal3f(0, 1, 0);
		for (i = 0; i < count-1; i++) {
			for (j = 0; j < count-1; j++) {
				glTexCoord2d((GLdouble)j / count, (GLdouble)i / count);
				glVertex3d((GLdouble)j / count, 0, (GLdouble)i / count);
				glTexCoord2d((GLdouble)(j + 1) / count, (GLdouble)i / count);
				glVertex3d((GLdouble)(j + 1) / count, 0, (GLdouble)i / count);
				glTexCoord2d((GLdouble)(j + 1) / count, (GLdouble)(i + 1) / count);
				glVertex3d((GLdouble)(j + 1) / count, 0, (GLdouble)(i + 1) / count);
				glTexCoord2d((GLdouble)j / count, (GLdouble)(i + 1) / count);
				glVertex3d((GLdouble)j / count, 0, (GLdouble)(i + 1) / count);
			}
		}
		glEnd();
	} glPopMatrix();
}

void quad() {
	glNormal3f(0, 1, 0);
	glBegin(GL_POLYGON); {
		glTexCoord2d(0, 0);
		glVertex3d(-0.5, 0, 0.5);
		glTexCoord2d(0, 1);
		glVertex3d(0.5, 0, 0.5);
		glTexCoord2d(1, 1);
		glVertex3d(0.5, 0, -0.5);
		glTexCoord2d(1, 0);
		glVertex3d(-0.5, 0, -0.5);
	} glEnd();
}

void wall(bool enableMesh) {
	glDisable(GL_CULL_FACE);
	initMaterial(materials::redPlastic);
	const int meshCount = 256;
	glPushMatrix(); {
		glTranslated(0, -4, 0);
		glScaled(15, 1, 10);
		cube(NULL);
	} glPopMatrix();

	if (enableMesh) {
		glBlendFunc(GL_ONE, GL_ZERO);
		glPushMatrix(); {
			glTranslated(0, -3.50, 0);
			glScaled(15, 1, 10);
			mesh(meshCount);
		} glPopMatrix();
	}
}