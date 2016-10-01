#ifndef MATERIAL_H
#define MATERIAL_H
#include <GL/glew.h>
#include "MaterialType.h"

struct Material {
	GLfloat ambience[3];
	GLfloat diffuse[3];
	GLfloat specular[3];
	GLfloat shininess;
};

void getMaterialForType(int type, Material *material);
#endif