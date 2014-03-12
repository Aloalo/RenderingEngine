#include "Label.h"

using namespace glm;

namespace reng
{
	Label::Label(void)
	{
		d = vec2(100, 20);
		color = vec4(1, 1, 1, 0);
	}

	Label::~Label(void)
	{
	}

	void Label::draw()
	{
		Component::draw();
		font->draw(text, p);
	}
}