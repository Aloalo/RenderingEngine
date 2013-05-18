#pragma once

#include <glm/glm.hpp>
#include <stack>

class MatrixStack
{
public:
	MatrixStack(void);
	~MatrixStack(void);

	void pushMatrix();
	void popMatrix();
	void multMatrix(const glm::mat4 &M);
	glm::mat4 top() const;

	//operations done on stack top
	void rotate(float angle, const glm::vec3 &axsis);
	void translate(const glm::vec3 &translation);
	void scale(const glm::vec3 &factor);

private:
	std::stack<glm::mat4> matrixStack;
};

