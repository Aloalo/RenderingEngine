#include "Material.h"

using namespace glm;
using namespace tinyobj;


Material::Material(const vec4 &ambientColor, const vec4 &diffuseColor, const vec4 &specularColor, float shininess)
	: ambientColor(ambientColor), diffuseColor(diffuseColor), specularColor(specularColor), shininess(shininess)
{
}

Material::Material(const material_t &mat)
	: ambientColor(mat.ambient[0], mat.ambient[1], mat.ambient[2], 1.0f), diffuseColor(mat.diffuse[0], mat.diffuse[1], mat.diffuse[2], 1.0f), 
	specularColor(mat.specular[0], mat.specular[1], mat.specular[2], 1.0f), shininess(mat.shininess)
{
}

Material::~Material(void)
{
}
