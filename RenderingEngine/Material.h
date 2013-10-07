#pragma once

#include "glm/glm.hpp"

class Material
{
public:
	Material(const glm::vec4 &ambientColor, const glm::vec4 &diffuseColor, const glm::vec4 &specularColor, float shininessFactor);
	~Material(void);

	glm::vec4 diffuseColor;
	glm::vec4 specularColor;
	glm::vec4 ambientColor;
	float shininessFactor;
};

