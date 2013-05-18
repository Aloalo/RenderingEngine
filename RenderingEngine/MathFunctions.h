#pragma once

#include <glm\glm.hpp>
#include <vector>
#include "Function.h"

namespace MathFunctions
{
	const double pi = 3.14159265359;

	float clamp(float x, float a, float b);
	glm::vec3 sLerp(const glm::vec3 &start, const glm::vec3 &end, float factor);
	glm::vec3 lerp(const glm::vec3 &start, const glm::vec3 &end, float factor);
	glm::vec3 nLerp(const glm::vec3 &start, const glm::vec3 &end, float factor);
}


