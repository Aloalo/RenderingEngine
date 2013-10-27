#include "Input.h"
#include "Engine.h"
#include <GL\glfw.h>

std::list<std::shared_ptr<InputObserver> > Input::observerList;

Input::Input(void)
{
	glfwSetKeyCallback(keyPress);
	glfwSetWindowSizeCallback(handleResize);
}


Input::~Input(void)
{
	observerList.clear();
}

void GLFWCALL Input::keyPress(int key, int action)
{
	if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
	{
		Engine::stop();
		exit(0);
	}

	for(std::list<std::shared_ptr<InputObserver> >::iterator i = observerList.begin(); i != observerList.end(); i++)
		(*i)->keyPress(key, action);
}

void GLFWCALL Input::mouseMove(int x, int y)
{
	for(std::list<std::shared_ptr<InputObserver> >::iterator i = observerList.begin(); i != observerList.end(); i++)
		(*i)->mouseMove(x, y);
}

void GLFWCALL Input::mouseClick(int button, int state)
{
	for(std::list<std::shared_ptr<InputObserver> >::iterator i = observerList.begin(); i != observerList.end(); i++)
		(*i)->mouseClick(button, state);
}

void GLFWCALL Input::handleResize(int width, int height)
{
	glViewport(0, 0, width, height);
	for(std::list<std::shared_ptr<InputObserver> >::iterator i = observerList.begin(); i != observerList.end(); i++)
		(*i)->windowResize(width, height);
}

void GLFWCALL Input::mouseWheelMove(int pos)
{
	for(std::list<std::shared_ptr<InputObserver> >::iterator i = observerList.begin(); i != observerList.end(); i++)
		(*i)->mouseWheelMove(pos);
}

void Input::addInputObserver(std::shared_ptr<InputObserver> IO)
{
	observerList.push_back(IO);
}

void Input::setMouseMoveCallback()
{
	int windowWidth, windowHeight;
	glfwGetWindowSize(&windowWidth, &windowHeight);
	glfwDisable(GLFW_MOUSE_CURSOR);

	glfwSetMousePos(windowWidth / 2, windowHeight / 2);
	glfwSetMousePosCallback(mouseMove); 
}

void Input::setMouseClickCallback()
{
	glfwSetMouseButtonCallback(mouseClick);
}

void Input::setMouseWheelCallback()
{
	glfwSetMouseWheelCallback(mouseWheelMove);
}