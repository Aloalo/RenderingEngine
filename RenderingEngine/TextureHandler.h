#pragma once

#include "Texture.h"
#include "TextureSampler.h"
#include <string>
#include <map>

class TextureHandler
{
	friend class Engine;
public:
	static Texture getTexture(const std::string &path, const std::string &name);
	static Texture getDefaultTexture();
	static Texture getTexture(const std::string &name, GLenum target);

private:
	TextureHandler(void);
	~TextureHandler(void);
	static void generateDefaultTex();

	static std::map<std::string, Texture> existingTextures;
	static Texture defaultTexture;
};



