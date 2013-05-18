
#include "Program.h"

using namespace glm;

Program::Program(const VertexShader &vs, const GeometryShader &gs, const FragmentShader &fs)
{
	init(&vs, &gs, &fs);
}

Program::Program(const VertexShader &vs, const FragmentShader &fs)
{
	init(&vs, 0, &fs);
}

Program::Program(const char *name)
{
	init(&VertexShader(name), &GeometryShader(name), &FragmentShader(name));
}

Program::~Program(void)
{
}

void Program::init(const VertexShader *vs, const GeometryShader *gs, const FragmentShader *fs)
{
	id = glCreateProgram();
	glAttachShader(id, vs->id);
	if(gs)
		glAttachShader(id, gs->id);
	glAttachShader(id, fs->id);
	glLinkProgram(id);
	int status;
	glGetProgramiv(id, GL_LINK_STATUS, &status);
	if(status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength+1];
		glGetProgramInfoLog(id, infoLogLength, NULL, strInfoLog);
		printf("Linking failure:\n%s\n", strInfoLog);
		delete[] strInfoLog;
	}
	glDetachShader(id, vs->id);
	if(gs)
		glDetachShader(id, gs->id);
	glDetachShader(id, fs->id);
}

void Program::use()
{
	glUseProgram(id);
}

void Program::setUniform(const char *name, const float &x)
{
	glProgramUniform1f(id, glGetUniformLocation(id, name), x);
}

void Program::setUniform(const char *name, const vec2 &x)
{
	glProgramUniform2f(id, glGetUniformLocation(id, name), x.x, x.y);
}

void Program::setUniform(const char *name, const vec3 &x)
{
	glProgramUniform3f(id, glGetUniformLocation(id, name), x.x, x.y, x.z);
}

void Program::setUniform(const char *name, const vec4 &x)
{
	glProgramUniform4f(id, glGetUniformLocation(id, name), x.x, x.y, x.z, x.w);
}

void Program::setUniform(const char *name, int cnt, const float *x)
{
	glProgramUniform1fv(id, glGetUniformLocation(id, name), cnt, x);
}

void Program::setUniform(const char *name, int cnt, const vec2 *x)
{
	glProgramUniform2fv(id, glGetUniformLocation(id, name), cnt, (float*)x);
}

void Program::setUniform(const char *name, int cnt, const vec3 *x)
{
	glProgramUniform3fv(id, glGetUniformLocation(id, name), cnt, (float*)x);
}

void Program::setUniform(const char *name, int cnt, const vec4 *x)
{
	glProgramUniform4fv(id, glGetUniformLocation(id, name), cnt, (float*)x);
}

void Program::setUniform(const char *name, int cnt, const mat4 *x)
{
	glProgramUniformMatrix4fv(id, glGetUniformLocation(id, name), cnt, GL_FALSE, (float*)x);
}

void Program::assignToBindingPoint(int bindingPoint, int blockIndex)
{
	glUniformBlockBinding(id, blockIndex, bindingPoint);
}

void Program::uniformBlockIndex(const char *blockName)
{
	glGetUniformBlockIndex(id, blockName);
}
