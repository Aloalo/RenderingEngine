#include "Square.h"

using namespace glm;

Square::Square(void)
{
}

Square::Square(const glm::vec3 &n, const glm::vec3 &c, const glm::vec3 &a)
	: n(n), c(c), a(a)
{
}


Square::~Square(void)
{
}

glm::vec3 Square::getVertex(int i) const
{
	switch(i)
	{
	case 0:
		return a;
	case 1:
		return cross(n, a - c) / length(n) + c;
	case 2:
		return 2.f * c - a;
	case 3:
		return cross(n, c - a) / length(n) + c;
	}
	return vec3();
}
