#pragma once

#include "Function.h"
#include "Mesh.h"

namespace reng
{
	class FunctionGraph
	{
	public:
		FunctionGraph(Function *func);
		~FunctionGraph(void);

		void generateGraph(const glm::vec2 x[3], int depth, float cutoff, Mesh *output);

	private:
		void catchData(const glm::vec2 x[3]);
		void subdivide(const glm::vec2 x[3], int depth, float cutoff);
		Function *f;
		Mesh *out;
	};
}
