#include "FontFace.h"

using namespace glm;

namespace reng
{
	FontFace::FontFace(const std::string &path, int r, int c, char start, float realWidth) :
		tex(TextureHandler::getTexture(path)), r(r), c(c), start(start), realWidth(realWidth)
	{
		tex.generateMipmaps();
	}

	FontFace::~FontFace(void)
	{
	}
	
	glm::vec2 FontFace::pos(char ch) const
	{
		int x = ch - start;
		return vec2((x % c + (1 - realWidth) / 2) / c, 1 - (float)(x / c + 1) / r);
	}

	glm::vec2 FontFace::size() const
	{
		return vec2(realWidth / c, 1. / r);
	}
}

