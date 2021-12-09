#pragma once
#include <GL/freeglut.h>

enum class materials
{
    blackPlastic,
    grayPlastic,
    redPlastic,
    whitePlastic,
    silver,
    glass
};

void initMaterial(materials);