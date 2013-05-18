#pragma once

#include "Vertex.h"

class VertexN :
	public virtual Vertex
{
public:
	VertexN(void);
	VertexN(const glm::vec3 &_position, const glm::vec3 &_normal);
	virtual ~VertexN(void);

	glm::vec3 normal;
protected:
	virtual bool isZero() const;
	virtual Vertex* sub(const Vertex &other) const;
};

