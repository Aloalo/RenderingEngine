#pragma once

#include <glm/glm.hpp>
#include "tiny_obj_loader.h"

struct Material
{
	Material(const glm::vec4 &ambientColor, const glm::vec4 &diffuseColor, const glm::vec4 &specularColor, float shininess);
	Material(const tinyobj::material_t &mat);
	~Material(void);

	glm::vec4 diffuseColor;
	glm::vec4 specularColor;
	glm::vec4 ambientColor;
	float shininess;
};

