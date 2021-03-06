#include "FunctionGraph.h"
#include "MathFunctions.h"

using namespace glm;

namespace reng
{
	FunctionGraph::FunctionGraph(Function *func)
		: f(func)
	{
	}


	FunctionGraph::~FunctionGraph(void)
	{
		delete f;
	}

	void FunctionGraph::generateGraph(const vec2 x[3], int depth, float cutoff, Mesh *output)
	{
		out = output;
		subdivide(x, depth, cutoff);
		out = NULL;
	}

	void FunctionGraph::catchData(const vec2 x[3])
	{
		const glm::vec3 triangle[] =
		{
			vec3(x[1].x, (*f)(x[1]), x[1].y),
			vec3(x[0].x, (*f)(x[0]), x[0].y),
			vec3(x[2].x, (*f)(x[2]), x[2].y)
		};
		const glm::vec3 normals[] =
		{
			f->normal(x[1]),
			f->normal(x[0]),
			f->normal(x[2])
		};
		out->addTriangle(triangle, normals);
	}

	void FunctionGraph::subdivide(const vec2 x[3], int depth, float cutoff)
	{
		if(depth == 0 || (f->curvature(x[0]) < cutoff && f->curvature(x[1]) < cutoff && f->curvature(x[2]) < cutoff))
		{
			catchData(x);
			return;
		}

		vec2 x12 = (x[0] + x[1]) / 2.0f;
		vec2 x23 = (x[1] + x[2]) / 2.0f;
		vec2 x31 = (x[2] + x[0]) / 2.0f;
		const vec2 x1[] = {x[0], x12, x31};
		const vec2 x2[] = {x[1], x23, x12};
		const vec2 x3[] = {x[2], x31, x23};
		const vec2 x4[] = {x12, x23, x31};
		subdivide(x1, depth-1, cutoff);
		subdivide(x2, depth-1, cutoff);
		subdivide(x3, depth-1, cutoff);
		subdivide(x4, depth-1, cutoff);
	}
}