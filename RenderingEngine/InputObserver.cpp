
#include "InputObserver.h"

namespace reng
{
	InputObserver::InputObserver(void) :
		active(1)
	{
	}


	InputObserver::~InputObserver(void)
	{
	}
	
	void InputObserver::keyPress(const KeyPressEvent &e)
	{
	}

	void InputObserver::mouseMove(const MouseMoveEvent &e)
	{
	}

	void InputObserver::mouseClick(const MouseClickEvent &e)
	{
	}

	void InputObserver::mouseWheelMove(const MouseWheelMoveEvent &e)
	{
	}

	void InputObserver::windowResize(const WindowResizeEvent &e)
	{
	}
}
