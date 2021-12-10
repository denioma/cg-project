#include "../include/textures.h"
#include "../include/RgbImage.h"

GLuint wood, metal, skyBoxTex, flooring;

void initTextures() {
	RgbImage img;
	img.LoadBmpFile("assets/wood.bmp");
	glGenTextures(1, &wood);
	glBindTexture(GL_TEXTURE_2D, wood);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA,
		img.GetNumCols(), img.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE, img.ImageData()
	);

	img.LoadBmpFile("assets/brushed_metal.bmp");
	glGenTextures(1, &metal);
	glBindTexture(GL_TEXTURE_2D, metal);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA,
		img.GetNumCols(), img.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE, img.ImageData()
	);

	img.LoadBmpFile("assets/skybox.bmp");
	glGenTextures(1, &skyBoxTex);
	glBindTexture(GL_TEXTURE_2D, skyBoxTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA,
		img.GetNumCols(), img.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE, img.ImageData()
	);

	img.LoadBmpFile("assets/floor2.bmp");
	glGenTextures(1, &flooring);
	glBindTexture(GL_TEXTURE_2D, flooring);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(
		GL_TEXTURE_2D, 0, GL_RGBA,
		img.GetNumCols(), img.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE, img.ImageData()
	);
}