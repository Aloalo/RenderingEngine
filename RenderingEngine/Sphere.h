#pragma once

#include <glm\glm.hpp>
#include <vector>

class Sphere
{
public:
	Sphere(float _radius, const glm::vec3 &_center);
	~Sphere(void);

	const std::vector<glm::vec3> generate(int depth) const;

private:
	void subdivide(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, 
		           int depth, std::vector<glm::vec3> &out) const;

	float radius;
	glm::vec3 center;
};

