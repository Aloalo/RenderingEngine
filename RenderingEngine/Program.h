#pragma once

#include "VertexShader.h"
#include "GeometryShader.h"
#include "FragmentShader.h"
#include "TextureSampler.h"
#include <glm/glm.hpp>

class Program
{
public:
	int id;

	Program(const VertexShader &vs, const FragmentShader &fs);
	Program(const VertexShader &vs, const GeometryShader &gs, const FragmentShader &fs);
	Program(const char *name);
	Program(int vs, int gs, int fs, const char *name);
	Program(int vs, int fs, const char *name);
	~Program(void);

	void use();

	int getUniformLocation(const char *name);
	int getUniformBlockLocation(const char *name);
	int getUniformi(const char *name);

	void setUniformBlockBinding(const char *name, int bindingPoint);

	void setUniform(const char *name, int x);

	void setUniform(const char *name, float x);
	void setUniform(const char *name, const glm::vec2 &x);
 	void setUniform(const char *name, const glm::vec3 &x);
 	void setUniform(const char *name, const glm::vec4 &x);
	void setUniform(const char *name, const glm::mat3 &x);
	void setUniform(const char *name, const glm::mat4 &x);

	void setUniform(const char *name, int cnt, const float *x);
	void setUniform(const char *name, int cnt, const glm::vec2 *x);
 	void setUniform(const char *name, int cnt, const glm::vec3 *x);
 	void setUniform(const char *name, int cnt, const glm::vec4 *x);
	void bindSamplerObjectToSampler(const char *samplerName, const TextureSampler& tex);

private:
	void init(const VertexShader *vs, const GeometryShader *gs, const FragmentShader *fs);

	void attach(const Shader &sh);
	void detach(const Shader &sh);
};
