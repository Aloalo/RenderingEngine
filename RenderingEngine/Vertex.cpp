#include "Vertex.h"
#include <cstring>
#include "MathFunctions.h"

using namespace glm;
using namespace mfl;

namespace reng
{
	Vertex::Vertex(void)
	{
	}

	Vertex::Vertex(const vec3 &position, const vec3 &normal, vec2 &uv)
		: position(position), normal(normal), uv(uv)
	{
	}

	bool Vertex::operator<(const Vertex &other) const
	{
		return memcmp((void*)this, (void*)&other, sizeof(Vertex))>0;
	}

	bool Vertex::operator==(const Vertex &other) const
	{
		return equals(position, other.position) && equals(normal, other.normal) && equals(uv, other.uv);
	}
}