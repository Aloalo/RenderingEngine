#pragma once

#include <glm\glm.hpp>
#include "MathFunctions.h"

namespace reng
{
	struct Vertex
	{
		Vertex(void);
		Vertex(const glm::vec3 &position, const glm::vec3 &normal = glm::vec3(), glm::vec2 &uv = glm::vec2());

		bool operator<(const Vertex &other) const;
		bool operator==(const Vertex &other) const;

		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;
	};
}