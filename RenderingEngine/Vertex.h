#pragma once

#include <glm\glm.hpp>

struct Vertex
{
public:
	Vertex(void);
	Vertex(const glm::vec3 &_position);
	virtual ~Vertex(void);

	bool operator==(const Vertex &other) const;
	Vertex operator-(const Vertex &other) const;
	bool operator<(const Vertex &other) const;
	Vertex& operator=(const Vertex &other);
	
	glm::vec3 position;

protected:
	virtual bool isZero() const;
	virtual Vertex* sub(const Vertex &other) const;
	const float EPS;
};

