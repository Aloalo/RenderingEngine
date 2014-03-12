#pragma once

#include <glm/glm.hpp>
#include "TextureHandler.h"

namespace reng
{
	class FontFace
	{
	public:
		FontFace(const std::string &path, int r, int c, char start, float realWidth = 1);
		~FontFace(void);
		
		glm::vec2 pos(char c) const;
		glm::vec2 size() const;
		
		Texture tex;
		int r, c;
		char start;
		float realWidth;
	};
}
