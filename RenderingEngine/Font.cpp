#include "Font.h"
#include <iostream>
#include <algorithm>

using namespace glm;
using namespace std;

namespace reng
{
	Font::Font() :
		color(vec4(1, 1, 1, 1)), halign(Left), valign(Top)
	{
	}

	Font::Font(const FontFace *ff, float size, vec4 color,
		HAlignment halign, VAlignment valign) :
		ff(ff), size(size), color(color), halign(halign), valign(valign)
	{
	}

	Font::~Font(void)
	{
	}

	float Font::charWidth(char c) const
	{
		return size * ff->realWidth;
	}

	float Font::stringWidth(const std::string &s) const
	{
		return (find(s.begin(), s.end(), '\n') - s.begin()) * charWidth(' ');
	}

	int Font::numLines(const std::string &s) const
	{
		return 1 + count(s.begin(), s.end(), '\n');
	}

	void Font::draw(char c, vec2 pos)
	{
		vec2 p = ff->pos(c);
		vec2 d = ff->size();
		ff->tex.bind();
		glBegin(GL_QUADS);
		glColor4fv((float*)&color);
		glTexCoord2f(p.x, p.y + d.y);
		glVertex2f(pos.x, pos.y);
		glTexCoord2f(p.x + d.x, p.y + d.y);
		glVertex2f(pos.x + size, pos.y);
		glTexCoord2f(p.x + d.x, p.y);
		glVertex2f(pos.x + size, pos.y + size);
		glTexCoord2f(p.x, p.y);
		glVertex2f(pos.x, pos.y + size);
		glEnd();
	}

	void Font::draw(const string &s, vec2 pos)
	{
		float startx = pos.x;
		for(int i = 0; i < s.size(); ++i)
			if(s[i] == '\n')
				pos = vec2(startx, pos.y + size);
			else
			{
				draw(s[i], pos);
				pos.x += charWidth(s[i]);
			}
	}

	void Font::draw(const string &s, vec2 pos, vec2 dim)
	{
		string line, rest = s;
		float startx = pos.x;
		pos.y += valignOffset(s, dim);
		while(rest != "")
		{
			int x = find(rest.begin(), rest.end(), '\n') - rest.begin();
			line = rest.substr(0, x);
			while(x < rest.size() && rest[x] == '\n')
				++x;
			rest = rest.substr(x);
			pos.x = startx + halignOffset(line, dim);
			for(char c : line)
			{
				draw(c, pos);
				pos.x += charWidth(c);
			}
			pos.y += size;
		}
	}
	
	float Font::halignOffset(const string &s, vec2 dim) const
	{
		if(halign == Center)
			return (dim.x - stringWidth(s)) / 2;
		if(halign == Right)
			return dim.x - stringWidth(s);
		return 0;
	}
	
	float Font::valignOffset(const string &s, vec2 dim) const
	{
		if(valign == Middle)
			return (dim.y - numLines(s) * size) / 2;
		if(valign == Bottom)
			return dim.y - numLines(s) * size;
		return 0;
	}
}
