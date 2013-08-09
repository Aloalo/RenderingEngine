#pragma once

#include <glm/glm.hpp>

class Square
{
public:
	Square(void);
	Square(const glm::vec3 &n, const glm::vec3 &c, const glm::vec3 &a);
	~Square(void);

	glm::vec3 getVertex(int i) const;

	glm::vec3 n;
	glm::vec3 c;
	glm::vec3 a;
};

