#pragma once

class InputObserver
{
public:
	InputObserver(void);
	virtual ~InputObserver(void);

	virtual void keyPress(int key, int action) = 0;
	virtual void mouseMove(int x, int y) = 0;
	virtual void mouseClick(int button, int state) = 0;
	virtual void mouseWheelMove(int pos) = 0;
	virtual void windowResize(int width, int height) = 0;
};