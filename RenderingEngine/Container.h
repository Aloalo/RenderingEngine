#pragma once

#include <list>
#include "Component.h"

namespace reng
{
	class LayoutManager;

	class Container : public Component
	{
	public:
		Container(void);
		~Container(void);

		void add(Component *c);

		virtual void draw();

		virtual void onClick(const MouseClickEvent &e);

		std::list<Component*> l;

		void pack();

		LayoutManager *lm;

	protected:
		void drawComponents();
	};
}