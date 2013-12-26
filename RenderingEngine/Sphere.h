#pragma once

#include <glm\glm.hpp>
#include <vector>

class Sphere
{
public:
	static std::vector<glm::vec3>* generate(int depth, float r, const glm::vec3 &center);

private:
	static void subdivide(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, 
		           int depth, std::vector<glm::vec3> &out);

	static float radius;
};

