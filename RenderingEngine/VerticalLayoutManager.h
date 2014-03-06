#pragma once

#include "LayoutManager.h"

namespace reng
{
	class VerticalLayoutManager : public LayoutManager
	{
	public:
		VerticalLayoutManager(void);
		~VerticalLayoutManager(void);

		virtual void add(Component *c, Container *l);
		void pack(Container *l);
	};
}
