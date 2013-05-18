#pragma once

#include "glm\glm.hpp"

class Light
{
public:
	Light(const glm::vec3 _position, float _intensity);
	~Light(void);

	glm::vec3 position;
	float intensity;
};

