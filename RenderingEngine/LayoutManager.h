#pragma once

namespace reng
{
	class Component;
	class Container;

	class LayoutManager
	{
	public:
		LayoutManager(void);
		~LayoutManager(void);

		virtual void add(Component *c, Container *l) {};
		virtual void pack(Container *l) {};
	};
}