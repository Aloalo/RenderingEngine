#include "Component.h"
#include <GL/glew.h>

namespace reng
{
	using namespace glm;

	Component::Component(void)
	{
	}

	Component::~Component(void)
	{
	}

	void Component::draw()
	{
		glBegin(GL_QUADS);
		glColor4fv((float*)&color);
		glVertex2f(p.x, p.y);
		glVertex2f(p.x + d.x, p.y);
		glVertex2f(p.x + d.x, p.y + d.y);
		glVertex2f(p.x, p.y + d.y);
		glEnd();
	}

	void Component::onClick(const MouseClickEvent &e)
	{
	}

	bool Component::contains(vec2 v) const
	{
		return
			p.x <= v.x && v.x < p.x + d.x &&
			p.y <= v.y && v.y < p.y + d.y;
	}
}
