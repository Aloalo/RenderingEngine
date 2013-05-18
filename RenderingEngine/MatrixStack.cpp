#include "MatrixStack.h"
#include <glm/gtc/matrix_transform.hpp>

MatrixStack::MatrixStack(void)
{
}


MatrixStack::~MatrixStack(void)
{
}

void MatrixStack::pushMatrix()
{
	matrixStack.push(glm::mat4(1.0f));
}

void MatrixStack::popMatrix()
{
	matrixStack.pop();
}

void MatrixStack::multMatrix(const glm::mat4 &M)
{
	matrixStack.top() *= M;
}

glm::mat4 MatrixStack::top() const
{
	return matrixStack.top();
}

void MatrixStack::rotate(float angle, const glm::vec3 &axis)
{
	matrixStack.top() = glm::rotate(matrixStack.top(), angle, axis);
}

void MatrixStack::translate(const glm::vec3 &translation)
{
	matrixStack.top() = glm::translate(matrixStack.top(), translation);
}

void MatrixStack::scale(const glm::vec3 &factor)
{
	matrixStack.top() = glm::scale(matrixStack.top(), factor);
}
