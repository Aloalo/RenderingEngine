#include "MathFunctions.h"

namespace MathFunctions
{
	float clamp(float x, float a, float b)
	{
		return x < a ? a : (x > b ? b : x);
	}

	glm::vec3 slerp(const glm::vec3 &start, const glm::vec3 &end, float factor)
	{
		float dot = glm::dot(start, end);     
		clamp(dot, -1.0f, 1.0f);
		float theta = acos(dot) * factor;
		glm::vec3 relativeVec = glm::normalize(end - start * dot);
		return start * cos(theta) + relativeVec * sin(theta);
	}

	glm::vec3 lerp(const glm::vec3 &start, const glm::vec3 &end, float factor)
	{
		return start + factor * (end - start);
	}

	glm::vec3 nLerp(const glm::vec3 &start, const glm::vec3 &end, float factor)
	{
		return glm::normalize(lerp(start, end, factor));
	}

	float ccw(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c)
	{
		return glm::dot(a, glm::cross(b, c));
	}
}