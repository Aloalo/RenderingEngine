#include "PackedVertex.h"
#include <glm/gtx/norm.hpp>

PackedVertex::PackedVertex(const glm::vec3 &_position, const glm::vec3 &_normal, const glm::vec2 &_uv)
	: VertexN(_position, _normal), VertexUV(_position, _uv), Vertex(_position)
{
}

PackedVertex::PackedVertex(void)
{
}


PackedVertex::~PackedVertex(void)
{
}

bool PackedVertex::isZero() const
{
	return glm::length2(position) < EPS && glm::length2(uv) < EPS && glm::length2(normal) < EPS;
}

Vertex* PackedVertex::sub(const Vertex &other) const
{
	const PackedVertex* tmp = dynamic_cast<const PackedVertex*> (&other);
	return new PackedVertex(position - tmp->position, normal - tmp->normal, uv - tmp->uv);
}

bool PackedVertex::operator<(const PackedVertex &other) const
{
	return memcmp((void*)this, (void*)&other, sizeof(*this)) > 0;
}