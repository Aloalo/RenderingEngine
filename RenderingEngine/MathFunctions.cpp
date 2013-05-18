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


	

/*	template <class T>
	void MathFunctions<T>::subdivide(const T x[4], int depth, float cutoff, void (*atEndDepth)(const T x[4]))
	{
		if(depth == 0)
		{
			atEndDepth(x);
			return;
		}

		T x12 = (x1 + x2) / 2.0f;
		T x23 = (x2 + x3) / 2.0f;
		T x31 = (x3 + x1) / 2.0f;

		subdivide(x1, x12, x31, depth-1, cutoff, atEndDepth);
		subdivide(x2, x23, x12, depth-1, cutoff, atEndDepth);
		subdivide(x3, x31, x23, depth-1, cutoff, atEndDepth);
		subdivide(x12, x23, x31, depth-1, cutoff, atEndDepth);
	}*/
}