#include "Material.h"

Material::Material(const glm::vec4 &ambientColor, const glm::vec4 &diffuseColor, const glm::vec4 &specularColor, float shininessFactor)
	: ambientColor(ambientColor), diffuseColor(diffuseColor), specularColor(specularColor), shininessFactor(shininessFactor)
{
}

Material::~Material(void)
{
}
