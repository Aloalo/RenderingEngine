#pragma once

#include "InputObserver.h"
#include <GLFW/glfw3.h>
#include <list>

class Input
{
public:
	Input(void);
	~Input(void);

	static void mouseMove(GLFWwindow *window, double x, double y);
	static void mouseClick(GLFWwindow *window, int button, int action, int mods);
	static void mouseWheelMove(GLFWwindow *window, double posx, double posy);
	static void keyPress(GLFWwindow *window, int key, int scancode, int action, int mods);
	static void handleResize(GLFWwindow *window, int width, int height);

	static void addInputObserver(std::shared_ptr<InputObserver> IO);

	static void setMouseMoveCallback();
	static void setMouseClickCallback();
	static void setMouseWheelCallback();
	static void setMousePosition(double x, double y);

private:
	static std::list<std::shared_ptr<InputObserver> > observerList;
};

