#pragma once

#include "glm/glm.hpp"

class Triangle
{
public:
	Triangle(const glm::vec3 *v);
	Triangle(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2);
	~Triangle(void);

	glm::vec3 getNormal();

	glm::vec3 v[3];
};

