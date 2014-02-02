#pragma once

#include "OGLobject.h"
#include <string>

namespace reng
{
	class TextureSampler :
		public OGLobject
	{
	public:
		TextureSampler(void);
		~TextureSampler(void);

		//does nothing, use Program for binding
		void bind() const;
		void samplerParameteri(GLenum pname, int param);
		void samplerParameterf(GLenum pname, float param);

		void generate();
		void destroy();
	};
}
