#include "libs/geometry.h"
#include "libs/palette.h"

void cube(const GLdouble* colors) {
	glColor4d(BLACK);
	const GLdouble vertices[] = {
		// Left
		-0.5, -0.5, 0.5,	// 0
		-0.5, 0.5, 0.5,		// 1
		-0.5, 0.5, -0.5,	// 2
		-0.5, -0.5, -0.5,	// 3
		// Right
		0.5, -0.5, 0.5,		// 4
		0.5, -0.5, -0.5,	// 5
		0.5, 0.5, -0.5,		// 6
		0.5, 0.5, 0.5,		// 7
		// Top
		-0.5, 0.5, 0.5,		// 8
		0.5, 0.5, 0.5,		// 9
		0.5, 0.5, -0.5,		// 10
		-0.5, 0.5, -0.5,	// 11
		// Bottom
		-0.5, -0.5, 0.5,	// 12
		-0.5, -0.5, -0.5,	// 13
		0.5, -0.5, -0.5,	// 14
		0.5, -0.5, 0.5,		// 15
		// Front
		-0.5, -0.5, 0.5,	// 16
		0.5, -0.5, 0.5,		// 17
		0.5, 0.5, 0.5,		// 18
		-0.5, 0.5, 0.5,		// 19
		// Back
		0.5, 0.5, -0.5,		// 20
		0.5, -0.5, -0.5,	// 21
		-0.5, -0.5, -0.5,	// 22
		-0.5, 0.5, -0.5		// 23
	};
	const GLdouble cubeNormals[] = {
		// Left
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		-1, 0, 0,
		// Right
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		1, 0, 0,
		// Top
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		0, 1, 0,
		// Bottom
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		0, -1, 0,
		// Front
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		0, 0, 1,
		// Back
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
		0, 0, -1,
	};
	
	const GLuint left[] = { 0, 1, 2, 3 };
	const GLuint right[] = { 4, 5, 6, 7 };
	const GLuint top[] = { 8, 9, 10, 11 };
	const GLuint bottom[] = { 12, 13, 14, 15 };
	const GLuint front[] = { 16, 17, 18, 19 };
	const GLuint back[] = { 6, 5, 3, 2 };

	glVertexPointer(3, GL_DOUBLE, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_DOUBLE, 0, cubeNormals);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(4, GL_DOUBLE, 0, colors);
	glEnableClientState(GL_COLOR_ARRAY);

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, left);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, right);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, top);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bottom);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, front);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}
