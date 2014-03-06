#pragma once

#include "Events.h"

namespace reng
{
	class InputObserver
	{
	public:
		InputObserver(void);
		virtual ~InputObserver(void);

		virtual void keyPress(const KeyPressEvent &e);
		virtual void mouseMove(const MouseMoveEvent &e);
		virtual void mouseClick(const MouseClickEvent &e);
		virtual void mouseWheelMove(const MouseWheelMoveEvent &e);
		virtual void windowResize(const WindowResizeEvent &e);

		bool active;
	};
}