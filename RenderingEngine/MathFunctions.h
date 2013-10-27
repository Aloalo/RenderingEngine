#pragma once

#include <glm\glm.hpp>

namespace mfl
{
	const double pi = 3.14159265359;
	const float EPS = 0.0001f;

	template<class T>
	float clamp(T x, T a, T b)
	{
		return x < a ? a : (x > b ? b : x);
	}

	template<class T>
	glm::vec3 slerp(const glm::vec3 &start, const glm::vec3 &end, T factor)
	{
		T dot = glm::dot(start, end);     
		clamp(dot, -1.0f, 1.0f);
		T theta = acos(dot) * factor;
		glm::vec3 relativeVec = glm::normalize(end - start * dot);
		return start * cos(theta) + relativeVec * sin(theta);
	}

	template<class T>
	glm::vec3 lerp(const glm::vec3 &start, const glm::vec3 &end, T factor)
	{
		return start + factor * (end - start);
	}

	template<class T>
	glm::vec3 nLerp(const glm::vec3 &start, const glm::vec3 &end, T factor)
	{
		return glm::normalize(lerp(start, end, factor));
	}

	template<class T>
	float ccw(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c)
	{
		return glm::dot(a, glm::cross(b, c));
	}
}


