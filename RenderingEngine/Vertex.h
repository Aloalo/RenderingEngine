#pragma once

#include <glm\glm.hpp>
#include "MathFunctions.h"

namespace oper
{
	bool lessThan(const glm::vec3 &first, const glm::vec3 &second)
	{
		return first.x < second.x || first.x == second.x && (first.y < second.y || first.y == second.y && first.z < second.z);
	}

	bool equals(const glm::vec3 &first, const glm::vec3 &second)
	{
		return glm::length(first - second) < mfl::EPS;
	}

	bool graterThan(const glm::vec3 &first, const glm::vec3 &second)
	{
		return !(lessThan(first, second) || equals(first, second));
	}

	bool lessThan(const glm::vec2 &first, const glm::vec2 &second)
	{
		return first.x < second.x || (first.x == second.x && first.y < second.y);
	}

	bool equals(const glm::vec2 &first, const glm::vec2 &second)
	{
		return glm::length(first - second) < mfl::EPS;
	}

	bool graterThan(const glm::vec2 &first, const glm::vec2 &second)
	{
		return !(lessThan(first, second) || equals(first, second));
	}
}

struct Vertex
{
public:
	Vertex(void){}
	Vertex(const glm::vec3 &position) : position(position){}
	virtual ~Vertex(void){}

	bool operator<(const Vertex &other) const
	{
		return memcmp(this, &other, sizeof(*this)) < 0;
	}

	bool operator==(const Vertex &other) const
	{
		return oper::equals(position, other.position);
	}
	
	glm::vec3 position;
};

struct VertexN :
	public virtual Vertex
{
public:
	VertexN(void){}
	VertexN(const glm::vec3 &position, const glm::vec3 &normal)
		: Vertex(position), normal(normal)
	{}
	virtual ~VertexN(void)
	{
	}

	bool operator<(const VertexN &other) const
	{
		return memcmp(this, &other, sizeof(*this)) < 0;
	}

	bool operator==(const VertexN &other) const
	{
		return oper::equals(position, other.position) && oper::equals(normal, other.normal);
	}

	glm::vec3 normal;
};


struct VertexUV :
	public virtual Vertex
{
public:
	VertexUV(void){}
	VertexUV(const glm::vec3 &position, const glm::vec2 &uv)
		: Vertex(position), uv(uv)
	{
	}
	virtual ~VertexUV(void)
	{}

	bool operator<(const VertexUV &other) const
	{
		return memcmp(this, &other, sizeof(*this)) < 0;
	}

	bool operator==(const VertexUV &other) const
	{
		return oper::equals(position, other.position) && oper::equals(uv, other.uv);
	}

	glm::vec2 uv;
};

struct PackedVertex :
	public VertexN, public VertexUV
{
public:
	PackedVertex(void){}
	PackedVertex(const glm::vec3 &position, const glm::vec3 &normal, const glm::vec2 &uv)
		: Vertex(position), VertexN(position, normal), VertexUV(position, uv)
	{
	}
	~PackedVertex(void)
	{
	}

	bool operator<(const PackedVertex &other) const
	{
		return memcmp(this, &other, sizeof(*this)) < 0;
	}

	bool operator==(const PackedVertex &other) const
	{
		return oper::equals(position, other.position) && oper::equals(normal, other.normal) && oper::equals(uv, other.uv);
	}
};
