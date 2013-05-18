#pragma once

#include "Function.h"

class SineCosine :
	public Function
{
public:
	SineCosine(void);
	~SineCosine(void);

	float f(const glm::vec2 &x) const;
	glm::vec3 normal(const glm::vec2 &x) const;
	float curvature(const glm::vec2 &x) const;
};

