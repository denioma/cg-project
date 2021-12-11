#include "include/geometry.h"
#include "include/palette.h"

void cube(const GLdouble* colors) {
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
		-0.5, 0.5, 0.5,		// 8 = 1
		0.5, 0.5, 0.5,		// 9 = 7
		0.5, 0.5, -0.5,		// 10 = 6
		-0.5, 0.5, -0.5,	// 11 = 2
		// Bottom
		-0.5, -0.5, 0.5,	// 12 = 0
		-0.5, -0.5, -0.5,	// 13 = 3
		0.5, -0.5, -0.5,	// 14 = 5
		0.5, -0.5, 0.5,		// 15 = 4
		// Front
		-0.5, -0.5, 0.5,	// 16 = 0
		0.5, -0.5, 0.5,		// 17 = 4
		0.5, 0.5, 0.5,		// 18 = 7
		-0.5, 0.5, 0.5,		// 19 = 1
		// Back
		0.5, 0.5, -0.5,		// 20 = 6
		0.5, -0.5, -0.5,	// 21 = 5
		-0.5, -0.5, -0.5,	// 22 = 3
		-0.5, 0.5, -0.5		// 23 = 2
	};
	const GLdouble textures[] = {
		// Left
		1, 0,	// 0
		1, 1,	// 1
		0, 1,	// 2
		0, 0,	// 3
		// Right
		0, 0,	// 4
		1, 0,	// 5
		1, 1,	// 6
		0, 1,	// 7
		// Top
		0, 0,	// 8 = 1
		1, 0,	// 9 = 7
		1, 1,	// 10 = 6
		0, 1,	// 11 = 2
		// Bottom
		0, 1,	// 12 = 0
		0, 0,	// 13 = 3
		1, 0,	// 14 = 5
		1, 1,	// 15 = 4
		// Front
		0, 0,	// 16 = 0
		1, 0,	// 17 = 4
		1, 1,	// 18 = 7
		0, 1,	// 19 = 1
		// Back
		0, 1,	// 20 = 6
		0, 0,	// 21 = 5
		1, 0,	// 22 = 3
		1, 1,	// 23 = 2

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
	glTexCoordPointer(2, GL_DOUBLE, 0, textures);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, left);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, right);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, top);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bottom);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, front);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);
}

GLdouble CUBE_WHITE[] = {
		WHITE, WHITE, WHITE, WHITE,
		WHITE, WHITE, WHITE, WHITE,
		WHITE, WHITE, WHITE, WHITE,
		WHITE, WHITE, WHITE, WHITE,
		WHITE, WHITE, WHITE, WHITE,
		WHITE, WHITE, WHITE, WHITE
};