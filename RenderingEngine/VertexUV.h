#pragma once

#include "Vertex.h"

class VertexUV :
	public virtual Vertex
{
public:
	VertexUV(void);
	VertexUV(const glm::vec3 &_position, const glm::vec2 &_uv);
	virtual ~VertexUV(void);


	glm::vec2 uv;
protected:
	virtual bool isZero() const;
	virtual Vertex* sub(const Vertex &other) const;
};

