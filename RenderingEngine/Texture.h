#pragma once
#include "OGLobject.h"
#include <glm/glm.hpp>
#include <string>
#include <map>

namespace reng
{
	class Texture
		: public OGLobject
	{
		friend class TextureHandler;
	public:
		Texture(void);
		Texture(const std::string &name, GLenum target = GL_TEXTURE_2D);
		~Texture(void);

		void bind() const;
		void unBind() const;

		void texImage(GLint level, GLint internalFormat, const glm::vec3 &dimensions, GLenum format, GLenum type, const GLvoid *data) const;
		const std::string& getName();

		void texParami(GLenum paramName, GLuint param) const;
		void texParamf(GLenum paramName, GLfloat param) const;
		void texParamIuiv(GLenum paramName, const GLuint *param) const;
		void texParamIiv(GLenum paramName, const GLint *param) const;
		void texParamfv(GLenum paramName, const GLfloat *param) const;


	protected:
		std::string name;
		void generate();
		GLenum target;
		int textureUnit;
		void destroy();
	};
}
