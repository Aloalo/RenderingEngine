#include "Container.h"

#include <GL/glew.h>
#include "LayoutManager.h"

namespace reng
{
	Container::Container(void) :
		lm(0)
	{
	}

	Container::~Container(void)
	{
	}

	void Container::add(Component *c)
	{
		if(lm)
			lm->add(c, this);
		l.push_back(c);
	}

	void Container::pack()
	{
		if(lm)
			lm->pack(this);
	}

	void Container::draw()
	{
		Component::draw();
		glPushMatrix();
		glTranslatef(p.x, p.y, 0);
		drawComponents();
		glPopMatrix();
	}

	void Container::onClick(const MouseClickEvent &e)
	{
		for(auto c = l.begin(); c != l.end(); ++c)
			if((*c)->contains(e.pos))
			{
				MouseClickEvent ne = e;
				ne.pos -= (*c)->p;
				(*c)->onClick(ne);
			}
	}

	void Container::drawComponents()
	{
		for(auto c = l.begin(); c != l.end(); ++c)
			(*c)->draw();
	}
}
