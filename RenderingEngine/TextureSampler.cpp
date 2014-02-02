#include "TextureSampler.h"

namespace reng
{
	TextureSampler::TextureSampler(void)
	{
	}

	TextureSampler::~TextureSampler(void)
	{
	}

	void TextureSampler::bind() const
	{
	}

	void TextureSampler::destroy()
	{
		glDeleteSamplers(1, &ID);
	}

	void TextureSampler::samplerParameteri(GLenum pname, int param)
	{
		glSamplerParameteri(ID, pname, param);
	}

	void TextureSampler::samplerParameterf(GLenum pname, float param)
	{
		glSamplerParameterf(ID, pname, param);
	}

	void TextureSampler::generate()
	{
		glGenSamplers(1, &ID);
	}
}
