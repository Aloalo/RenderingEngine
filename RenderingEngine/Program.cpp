#include "Program.h"
#include <cstring>

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
	char sn[64];
	strcpy(sn, name);
	strcat(sn, ".geom");
	FILE *f = fopen(sn, "r");
	if(f)
		init(&VertexShader(name), &GeometryShader(name), &FragmentShader(name));
	else
		init(&VertexShader(name), 0, &FragmentShader(name));
}

Program::Program(int vs, int gs, int fs, const char *name)
{
	init(&VertexShader(vs, name), &GeometryShader(gs, name), &FragmentShader(fs, name));
}

Program::Program(int vs, int fs, const char *name)
{
	init(&VertexShader(vs, name), 0, &FragmentShader(fs, name));
}

Program::~Program(void)
{
}

void Program::init(const VertexShader *vs, const GeometryShader *gs, const FragmentShader *fs)
{
	id = glCreateProgram();
	attach(*vs);
	if(gs)
		attach(*gs);
	attach(*fs);
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
		delete [] strInfoLog;
	}
	detach(*vs);
	if(gs)
		detach(*gs);
	detach(*fs);
}

void Program::use()
{
	glUseProgram(id);
}

int Program::getUniformLocation(const char *name)
{
	return glGetUniformLocation(id, name);
}

int Program::getUniformBlockLocation(const char *name)
{
	return glGetUniformBlockIndex(id, name);
}

int Program::getUniformi(const char *name)
{
	int ret;
	glGetUniformiv(id, glGetUniformLocation(id, name), &ret);
	return ret;
}

void Program::setUniformBlockBinding(const char *name, int bindingPoint)
{
	glUniformBlockBinding(id, getUniformBlockLocation(name), bindingPoint);
}

void Program::setUniform(const char *name, int x)
{
	glProgramUniform1f(id, getUniformLocation(name), (float)x);
}

void Program::setUniform(const char *name, float x)
{
	glProgramUniform1f(id, getUniformLocation(name), x);
}

void Program::setUniform(const char *name, const vec2 &x)
{
	glProgramUniform2f(id, getUniformLocation(name), x.x, x.y);
}

void Program::setUniform(const char *name, const vec3 &x)
{
	glProgramUniform3f(id, getUniformLocation(name), x.x, x.y, x.z);
}

void Program::setUniform(const char *name, const vec4 &x)
{
	glProgramUniform4f(id, getUniformLocation(name), x.x, x.y, x.z, x.w);
}

void Program::setUniform(const char *name, const glm::mat3 &x)
{
	glProgramUniformMatrix3fv(id, glGetUniformLocation(id, name), 1, GL_FALSE, (float*)&x);
}

void Program::setUniform(const char *name, const mat4 &x)
{
	glProgramUniformMatrix4fv(id, glGetUniformLocation(id, name), 1, GL_FALSE, (float*)&x);
}

void Program::setUniform(const char *name, int cnt, const float *x)
{
	glProgramUniform1fv(id, getUniformLocation(name), cnt, x);
}

void Program::setUniform(const char *name, int cnt, const vec2 *x)
{
	glProgramUniform2fv(id, getUniformLocation(name), cnt, (float*)x);
}

void Program::setUniform(const char *name, int cnt, const vec3 *x)
{
	glProgramUniform3fv(id, getUniformLocation(name), cnt, (float*)x);
}

void Program::setUniform(const char *name, int cnt, const vec4 *x)
{
	glProgramUniform4fv(id, getUniformLocation(name), cnt, (float*)x);
}

void Program::bindSamplerObjectToSampler(const char *name, const TextureSampler &tex)
{
	int texUnit = getUniformi(name);
	glActiveTexture(GL_TEXTURE0 + texUnit);
	glBindSampler(texUnit, tex.getID());
}

void Program::attach(const Shader &sh)
{
	glAttachShader(id, sh.id);
}

void Program::detach(const Shader &sh)
{
	glDetachShader(id, sh.id);
}
