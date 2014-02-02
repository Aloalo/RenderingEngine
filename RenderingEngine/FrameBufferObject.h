#pragma once

#include "OGLobject.h"
#include "Texture.h"
#include "RenderBufferObject.h"
#include <vector>

namespace reng
{
	class FrameBufferObject
		: public OGLobject
	{
	public:
		FrameBufferObject(GLenum _target);
		~FrameBufferObject(void);

		void bind() const;
		void unBind() const;

		void destroy();
		void attachTexture(GLenum attachment, const Texture &texture, GLint level);
		void attachTextureLayer(GLenum attachment, const Texture &texture, GLint level, GLint layer);
		void attachRenderBuffer(GLenum attachment, const RenderBufferObject &rbo);
		void setDrawBuffers() const;
		bool check() const;

	protected:
		void generate();
		GLenum target;
		std::vector<GLenum> colorAttachments;
	};
}
