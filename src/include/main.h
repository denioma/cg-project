#include "palette.h"
#include "geometry.h"
#include "objects.h"
#include "textures.h"
#include "materials.h"

void init();
void draw();
void keyboard(unsigned char, int, int);
void special(int, int, int);
void timer(int);
void eqTimer(int);
void mouse(int, int);
void wheel(int, int, int, int);
void reshape(int, int);