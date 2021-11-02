#pragma once
#include <GL/freeglut.h>

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

void cube(const GLdouble* colors);
