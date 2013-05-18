#include "Function.h"


Function::Function(void)
{
}


Function::~Function(void)
{
}

float Function::operator[](const glm::vec2 &x) const
{
	return f(x);
}
