#include "VertexN.h"
#include <glm/gtx/norm.hpp>

VertexN::VertexN(const glm::vec3 &_position, const glm::vec3 &_normal)
	: Vertex(_position), normal(_normal)
{
}

VertexN::VertexN(void)
{

}

VertexN::~VertexN(void)
{
}

bool VertexN::isZero() const
{
	return glm::length2(position) < EPS && glm::length2(normal) < EPS;
}

Vertex* VertexN::sub(const Vertex &other) const
{
	const VertexN* tmp = dynamic_cast<const VertexN*> (&other);
	return &VertexN(position - tmp->position, normal - tmp->normal);
}
