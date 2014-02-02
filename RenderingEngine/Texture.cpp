#include "Texture.h"
#include <GLFW/glfw3.h>

using namespace glm;
using namespace std;

namespace reng
{
	Texture::Texture(void)
	{
	}

	Texture::Texture(const string &name, GLenum target)
		: name(name), target(target)
	{
	}

	Texture::~Texture(void)
	{
	}

	void Texture::generate()
	{
		glGenTextures(1, &ID);
	}

	void Texture::destroy()
	{
		glDeleteTextures(1, &ID);
	}

	void Texture::bind() const
	{
		glBindTexture(target, ID);
	}

	void Texture::unBind() const
	{
		glBindTexture(target, 0);
	}

	void Texture::texImage(GLint level, GLint internalFormat, const glm::vec3 &dimensions, GLenum format, GLenum type, const GLvoid *data) const
	{
		bind();
		glTexImage2D(target, level, internalFormat, dimensions.x, dimensions.y, 0, format, type, data);
	}

	const std::string& Texture::getName()
	{
		return name;
	}

	void Texture::texParami(GLenum paramName, GLuint param) const
	{
		bind();
		glTexParameteri(target, paramName, param);
	}

	void Texture::texParamf(GLenum paramName, GLfloat param) const
	{
		bind();
		glTexParameterf(target, paramName, param);
	}

	void Texture::texParamIuiv(GLenum paramName, const GLuint *param) const
	{
		bind();
		glTexParameterIuiv(target, paramName, param);
	}

	void Texture::texParamIiv(GLenum paramName, const GLint *param) const
	{
		bind();
		glTexParameterIiv(target, paramName, param);
	}

	void Texture::texParamfv(GLenum paramName, const GLfloat *param) const
	{
		bind();
		glTexParameterfv(target, paramName, param);
	}
}
