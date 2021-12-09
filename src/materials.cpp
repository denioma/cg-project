#include "../include/materials.h"

// Material table: http://devernay.free.fr/cours/opengl/materials.html

struct {
	GLfloat ambient[3] = { 0.0, 0.0, 0.0 };
	GLfloat diffuse[3] = { 0.01, 0.01, 0.01 };
	GLfloat specular[3] = { 0.5, 0.5, 0.5 };
	GLfloat shininess = 0.25 * 128;
} BlackPlastic;

struct {
	GLfloat ambient[3] = { 0.0, 0.0, 0.0 };
	GLfloat diffuse[3] = { 0.2, 0.2, 0.2 };
	GLfloat specular[3] = { 0.55, 0.55, 0.55 };
	GLfloat shininess = 0.25 * 128;
} GrayPlastic;

struct {
	GLfloat ambient[3] = { 0.0, 0.0, 0.0 };
	GLfloat diffuse[3] = { 0.5, 0.0, 0.0 };
	GLfloat specular[3] = { 0.7, 0.6, 0.6 };
	GLfloat shininess = 0.25 * 128;
} RedPlastic;

struct {
	GLfloat ambient[3] = { 0.0, 0.0, 0.0 };
	GLfloat diffuse[3] = { 0.55, 0.55, 0.55 };
	GLfloat specular[3] = { 0.7, 0.7, 0.7 };
	GLfloat shininess = 0.25 * 128;
} WhitePlastic;

struct {
	GLfloat ambient[3] = { 0.19225, 0.19225, 0.19225 };
	GLfloat diffuse[3] = { 0.50754, 0.50754, 0.50754 };
	GLfloat specular[3] = { 0.508273, 0.508273, 0.508273 };
	GLfloat shininess = 0.4 * 128;
} Silver;

struct {
	GLfloat ambient[3] = { 0, 0, 0 };
	GLfloat diffuse[4] = { 0.40754, 0.40754, 0.50754, 0.8 };
	GLfloat specular[3] = { 0.508273, 0.508273, 0.508273 };
	GLfloat shininess = 0.8 * 128;
} Glass;

/*
	List of materials

	0: BlackPlastic
	1: GrayPlastic
	2: RedPlastic
	3: WhitePlastic
	4: Silver
	5: Glass
*/
void initMaterial(materials material) {
	switch (material) {
	case materials::blackPlastic:
		glMaterialfv(GL_FRONT, GL_AMBIENT, BlackPlastic.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, BlackPlastic.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, BlackPlastic.specular);
		glMaterialf(GL_FRONT, GL_SHININESS, BlackPlastic.shininess);
		break;
	case materials::grayPlastic:
		glMaterialfv(GL_FRONT, GL_AMBIENT, GrayPlastic.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, GrayPlastic.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, GrayPlastic.specular);
		glMaterialf(GL_FRONT, GL_SHININESS, GrayPlastic.shininess);
		break;
	case materials::redPlastic:
		glMaterialfv(GL_FRONT, GL_AMBIENT, RedPlastic.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, RedPlastic.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, RedPlastic.specular);
		glMaterialf(GL_FRONT, GL_SHININESS, RedPlastic.shininess);
		break;
	case materials::whitePlastic:
		glMaterialfv(GL_FRONT, GL_AMBIENT, WhitePlastic.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, WhitePlastic.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, WhitePlastic.specular);
		glMaterialf(GL_FRONT, GL_SHININESS, WhitePlastic.shininess);
		break;
	case materials::silver:
		glMaterialfv(GL_FRONT, GL_AMBIENT, Silver.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, Silver.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, Silver.specular);
		glMaterialf(GL_FRONT, GL_SHININESS, Silver.shininess);
		break;
	case materials::glass:
		glMaterialfv(GL_FRONT, GL_AMBIENT, Glass.ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, Glass.diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, Glass.specular);
		glMaterialf(GL_FRONT, GL_SHININESS, Glass.shininess);
		break;
	}
}