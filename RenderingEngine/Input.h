#pragma once

#include "InputObserver.h"
#include <list>

class Input
{
public:
	Input(void);
	~Input(void);

	static void mouseMove(int x, int y);
	static void mouseClick(int button, int action);
	static void mouseWheelMove(int pos);
	static void keyPress(int key, int action);
	static void handleResize(int width, int height);

	static void addInputObserver(std::shared_ptr<InputObserver> IO);

	static void setMouseMoveCallback();
	static void setMouseClickCallback();
	static void setMouseWheelCallback();

private:
	static std::list<std::shared_ptr<InputObserver> > observerList;
};

