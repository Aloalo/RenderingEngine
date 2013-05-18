#include "VertexUV.h"
#include <glm/gtx/norm.hpp>

VertexUV::VertexUV(const glm::vec3 &_position, const glm::vec2 &_uv)
	: Vertex(_position), uv(_uv)
{
}

VertexUV::VertexUV(void)
{
}


VertexUV::~VertexUV(void)
{
}

bool VertexUV::isZero() const
{
	return glm::length2(position) < EPS && glm::length2(uv) < EPS;
}

Vertex* VertexUV::sub(const Vertex &other) const
{
	const VertexUV* tmp = dynamic_cast<const VertexUV*> (&other);
	return new VertexUV(position - tmp->position, uv - tmp->uv);
}
