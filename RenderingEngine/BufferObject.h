#pragma once

#include "OGLobject.h"

namespace reng
{
	class BufferObject
		: public OGLobject
	{
	public:
		BufferObject();
		BufferObject(GLenum _target, GLenum _usage);
		BufferObject(GLenum _target, GLenum _usage, const GLvoid *data, GLsizei size);
		~BufferObject(void);

		void bind() const;
		void destroy();

		void setData(const GLvoid *data, GLsizei size);
		void reSetData(const GLvoid *data, GLuint offset, GLuint size);

	protected:
		void generate();
		static BufferObject *boundBuffer;

		GLenum target;
		GLenum usage;
	};
}
