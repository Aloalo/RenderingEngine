#pragma once

#include "VertexN.h"
#include "VertexUV.h"

class PackedVertex :
	public VertexN, public VertexUV
{
public:
	PackedVertex(void);
	PackedVertex(const glm::vec3 &_position, const glm::vec3 &_normal, const glm::vec2 &_uv);
	~PackedVertex(void);

	bool operator<(const PackedVertex &other) const;

protected:
	virtual bool isZero() const;
	virtual Vertex* sub(const Vertex &other) const;
};

