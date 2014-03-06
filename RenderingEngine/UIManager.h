#pragma once

#include "Container.h"

namespace reng
{
	class UIManager : public Container, public InputObserver
	{
	public:
		static UIManager& get();

		void draw();
		
		void mouseClick(const MouseClickEvent &e);

	private:
		UIManager(void);
		~UIManager(void);

		static UIManager *uim;
	};
}
