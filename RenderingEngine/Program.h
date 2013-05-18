#pragma once

#include "VertexShader.h"
#include "GeometryShader.h"
#include "FragmentShader.h"
#include <glm/glm.hpp>

class Program
{
public:

	Program(const VertexShader &vs, const FragmentShader &fs);
	Program(const VertexShader &vs, const GeometryShader &gs, const FragmentShader &fs);
	Program(const char *name);
	~Program(void);

	void use();

	void setUniform(const char *name, const float &x);
	void setUniform(const char *name, const glm::vec2 &x);
 	void setUniform(const char *name, const glm::vec3 &x);
 	void setUniform(const char *name, const glm::vec4 &x);

	void setUniform(const char *name, int cnt, const float *x);
	void setUniform(const char *name, int cnt, const glm::vec2 *x);
 	void setUniform(const char *name, int cnt, const glm::vec3 *x);
 	void setUniform(const char *name, int cnt, const glm::vec4 *x);
	void setUniform(const char *name, int cnt, const glm::mat4 *x);

	void uniformBlockIndex(const char *blockName);
	void assignToBindingPoint(int bindingPoint, int blockIndex);

private:
	void init(const VertexShader *vs, const GeometryShader *gs, const FragmentShader *fs);
	int id;
};
