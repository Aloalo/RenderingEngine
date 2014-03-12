#pragma once

#include <string>
#include <glm/glm.hpp>
#include "FontFace.h"

namespace reng
{
	class Font
	{
	public:
		enum HAlignment
		{
			Left, Center, Right
		};
		enum VAlignment
		{
			Top, Middle, Bottom
		};

		Font();
		Font(const FontFace *ff, float size, glm::vec4 color = glm::vec4(1, 1, 1, 1),
			HAlignment halign = Left, VAlignment valign = Top);
		~Font(void);

		void draw(char c, glm::vec2 pos);
		void draw(const std::string &s, glm::vec2 pos);
		void draw(const std::string &s, glm::vec2 pos, glm::vec2 dim);

		float charWidth(char c) const;
		float stringWidth(const std::string &s) const;
		int numLines(const std::string &s) const;
		
		float halignOffset(const std::string &s, glm::vec2 dim) const;
		float valignOffset(const std::string &s, glm::vec2 dim) const;
		
		const FontFace *ff;
		float size;
		HAlignment halign;
		VAlignment valign;
		glm::vec4 color;
	};
}
