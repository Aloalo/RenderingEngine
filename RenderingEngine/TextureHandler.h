#pragma once

#include "Texture.h"
#include "TextureSampler.h"
#include <string>
#include <map>

namespace reng
{
	class TextureHandler
	{
		friend class Engine;
	public:
		static Texture getTexture(const std::string &path, const std::string &name, GLenum formt = GL_RGBA32F_ARB);
		static Texture getDefaultTexture();
		static Texture getTexture(const std::string &name, GLenum target);
		static bool hasTexture(const std::string &name);

	private:
		TextureHandler(void);
		~TextureHandler(void);
		static void generateDefaultTex();

		static std::map<std::string, Texture> existingTextures;
		static Texture defaultTexture;
	};
}
