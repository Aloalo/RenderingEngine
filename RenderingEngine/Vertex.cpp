#include "Vertex.h"

#include <memory>
#include <glm/gtx/norm.hpp>

Vertex::Vertex(const glm::vec3 &_position)
	: position(_position), EPS(0.0001f)
{
}

Vertex::Vertex(void)
	: EPS(0.001f)
{
}

Vertex::~Vertex(void)
{
}

bool Vertex::operator==(const Vertex &other) const 
{
	std::unique_ptr<Vertex> tmp(this->sub(other));
	return tmp->isZero();
}

Vertex Vertex::operator-(const Vertex &other) const
{
	std::unique_ptr<Vertex> tmp(this->sub(other));
	return *this;
}

bool Vertex::operator<(const Vertex &other) const
{
	return memcmp((void*)this, (void*)&other, sizeof(*this)) > 0;
}

bool Vertex::isZero() const
{
	return glm::length2(position) < EPS;
}

Vertex* Vertex::sub(const Vertex &other) const
{
	return new Vertex(position - other.position);
}

Vertex& Vertex::operator=(const Vertex &other)
{
	if (this != &other)
		memcpy(this, &other, sizeof(*this));
	return *this;
}
