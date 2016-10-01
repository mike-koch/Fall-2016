#include "Material.h"

void getMaterialForType(int type, Material *material) {
	switch (type) {
	case MaterialType::PEARL:
		material->ambience[0] = 0.25f;
		material->ambience[1] = 0.20725f;
		material->ambience[2] = 0.20725f;
		material->diffuse[0] = 1.0f;
		material->diffuse[1] = 0.829f;
		material->diffuse[2] = 0.829f;
		material->specular[0] = 0.296648f;
		material->specular[1] = 0.296648f;
		material->specular[2] = 0.296648f;
		material->shininess = 128.0f * 0.088f;
		return;
	case MaterialType::COPPER:
		material->ambience[0] = 0.19125f;
		material->ambience[1] = 0.0735f;
		material->ambience[2] = 0.0225f;
		material->diffuse[0] = 0.7038f;
		material->diffuse[1] = 0.27048f;
		material->diffuse[2] = 0.0828f;
		material->specular[0] = 0.256777f;
		material->specular[1] = 0.137622f;
		material->specular[2] = 0.086014f;
		material->shininess = 128.0f * 0.1f;
		return;
	case MaterialType::YELLOW_PLASTIC:
		material->ambience[0] =		
			material->ambience[1] =
			material->ambience[2] = 0.0f;
		material->diffuse[0] =
			material->diffuse[1] = 0.5f;
		material->diffuse[2] = 0.0f;
		material->specular[0] =
			material->specular[1] = 0.6f;
		material->specular[2] = 0.5f;
		material->shininess = 128.0f * 0.25f;
		return;
	case MaterialType::EMERALD:
		material->ambience[0] = 0.0215f;
		material->ambience[1] = 0.1745f;
		material->ambience[2] = 0.0215f;
		material->diffuse[0] = 0.07568f;
		material->diffuse[1] = 0.61424f;
		material->diffuse[2] = 0.07568f;
		material->specular[0] = 0.633f;
		material->specular[1] = 0.727811f;
		material->specular[2] = 0.633f;
		material->shininess = 128.0f * 0.6f;
		return;
	case MaterialType::JADE:
		material->ambience[0] = 0.135f;
		material->ambience[1] = 0.2225f;
		material->ambience[2] = 0.1575f;
		material->diffuse[0] = 0.54f;
		material->diffuse[1] = 0.89f;
		material->diffuse[2] = 0.63f;
		material->specular[0] = 0.316228f;
		material->specular[1] = 0.316228f;
		material->specular[2] = 0.316228f;
		material->shininess = 128.0f * 0.1f;
		return;
	case MaterialType::BRASS:
		material->ambience[0] = 0.329412f;
		material->ambience[1] = 0.223529f;
		material->ambience[2] = 0.027451f;
		material->diffuse[0] = 0.780392f;
		material->diffuse[1] = 0.568627f;
		material->diffuse[2] = 0.113725f;
		material->specular[0] = 0.992157f;
		material->specular[1] = 0.941176f;
		material->specular[2] = 0.807843f;
		material->shininess = 128.0f * 0.21794872f;
		return;
	default:
		return;
	}
}