#pragma once

#include <glm\glm.hpp>

namespace mfl
{
	static float pi = 3.14159165359f;
	static float EPS = 0.0001f;

	template<class T>
	float clamp(T x, T a, T b);

	template<class T>
	glm::vec3 slerp(const glm::vec3 &start, const glm::vec3 &end, T factor);

	template<class T>
	glm::vec3 lerp(const glm::vec3 &start, const glm::vec3 &end, T factor);

	template<class T>
	glm::vec3 nLerp(const glm::vec3 &start, const glm::vec3 &end, T factor);

	float ccw(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c);
	bool equals(const glm::vec3 &a, const glm::vec3 &b);
	bool equals(const glm::vec2 &a, const glm::vec2 &b);
	bool isZero(const glm::vec3 &a);
}


