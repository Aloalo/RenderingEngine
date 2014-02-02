#pragma once

#include "Function.h"

namespace reng
{
	class SineCosine :
		public Function
	{
	public:
		SineCosine(void);
		~SineCosine(void);

		float f(const glm::vec2 &x);
		glm::vec3 normal(const glm::vec2 &x);
		float curvature(const glm::vec2 &x);
	};
}
