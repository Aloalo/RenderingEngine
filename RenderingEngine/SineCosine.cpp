#include "SineCosine.h"


SineCosine::SineCosine(void)
{
}

SineCosine::~SineCosine(void)
{
}

float SineCosine::f(const glm::vec2 &x)
{
	return cos(x.x) + sin(x.y);
}

glm::vec3 SineCosine::normal(const glm::vec2 &x)
{
	return glm::vec3(sin(x.x), 1, -cos(x.y));
}

float SineCosine::curvature(const glm::vec2 &x)
{
	return (cos(x.x) * sin(x.y)) / ((1 - sin(x.x) + cos(x.y)) * (1 - sin(x.x) + cos(x.y)));
}
