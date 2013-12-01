#pragma once

class InputObserver
{
public:
	InputObserver(void);
	virtual ~InputObserver(void);

	virtual void keyPress(int key, int scancode, int action, int mods);
	virtual void mouseMove(double x, double y);
	virtual void mouseClick(int button, int state, int mods);
	virtual void mouseWheelMove(int pos);
	virtual void windowResize(int width, int height);
};