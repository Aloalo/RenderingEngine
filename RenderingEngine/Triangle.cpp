#include "Triangle.h"

using namespace glm;

Triangle::Triangle(const vec3 *v)
{
	memcpy(this->v, v, sizeof(this->v));
}

Triangle::Triangle(const vec3 &v0, const vec3 &v1, const vec3 &v2)
{
	v[0] = v0;
	v[1] = v1;
	v[2] = v2;
}

Triangle::~Triangle(void)
{
}

glm::vec3 Triangle::getNormal()
{
	return normalize(cross(v[2] - v[0], v[2] - v[1]));
}
