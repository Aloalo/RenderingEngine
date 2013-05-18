#pragma once

#include <glm\glm.hpp>
#include <vector>

class Function
{
public:
	Function(void);
	~Function(void);

	virtual float f(const glm::vec2 &x) const = 0;
	virtual glm::vec3 normal(const glm::vec2 &x) const = 0;
	//curvature = (Fxx * Fyy - Fxy^2) / (1 + Fx + Fy)^2
	virtual float curvature(const glm::vec2 &x) const = 0;

	float operator[] (const glm::vec2 &x) const;
};

