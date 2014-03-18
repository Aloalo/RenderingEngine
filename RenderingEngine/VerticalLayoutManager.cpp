#include "VerticalLayoutManager.h"

#include "Component.h"
#include "Container.h"
#include <glm/glm.hpp>

using namespace glm;

namespace reng
{
	VerticalLayoutManager::VerticalLayoutManager(void)
	{
	}

	VerticalLayoutManager::~VerticalLayoutManager(void)
	{
	}
	
	void VerticalLayoutManager::add(Component *c, Container *l)
	{
		vec2 p(5, 5);
		for(auto cli : l->l)
		{
			auto &cl = *cli;
			p.y = max(p.y, cl.p.y + cl.d.y + 5);
		}
		c->p = p;
	}

	void VerticalLayoutManager::pack(Container *l)
	{
		vec2 p(5, 5);
		float mx = 0;
		for(auto cli : l->l)
		{
			auto &cl = *cli;
			cl.p = p;
			p.y += cl.d.y + 5;
			mx = max(mx, cl.d.x);
		}
		l->d = vec2(mx + 10, p.y);
	}
}