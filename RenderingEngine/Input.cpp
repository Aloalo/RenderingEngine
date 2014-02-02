#include "Engine.h"
#include "Input.h"

using namespace std;

namespace reng
{
	list<InputObserver*> Input::observerList;

	Input::Input(void)
	{
		glfwSetKeyCallback(Engine::getWindow(), keyPress);
		glfwSetWindowSizeCallback(Engine::getWindow(), handleResize);
	}


	Input::~Input(void)
	{
	}

	void Input::keyPress(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
			return;
		}

		for(auto i = observerList.begin(); i != observerList.end(); i++)
			(*i)->keyPress(key, scancode, action, mods);
	}

	void Input::mouseMove(GLFWwindow *window, double x, double y)
	{
		for(auto i = observerList.begin(); i != observerList.end(); i++)
			(*i)->mouseMove(x, y);
	}

	void Input::mouseClick(GLFWwindow *window, int button, int state, int mods)
	{
		for(auto i = observerList.begin(); i != observerList.end(); i++)
			(*i)->mouseClick(button, state, mods);
	}

	void Input::handleResize(GLFWwindow *window, int width, int height)
	{
		glViewport(0, 0, width, height);
		Engine::setWindowSize(width, height);
		for(auto i = observerList.begin(); i != observerList.end(); i++)
			(*i)->windowResize(width, height);
	}

	void Input::mouseWheelMove(GLFWwindow *window, double posx, double posy)
	{
		for(auto i = observerList.begin(); i != observerList.end(); i++)
			(*i)->mouseWheelMove(0);
	}

	void Input::addInputObserver(InputObserver *IO)
	{
		observerList.push_back(IO);
	}

	void Input::setMouseMoveCallback()
	{
		int windowWidth, windowHeight;
		Engine::getWindowSize(windowWidth, windowHeight);

		glfwSetCursorPos(Engine::getWindow(), windowWidth / 2, windowHeight / 2);
		glfwSetCursorPosCallback(Engine::getWindow(), mouseMove); 
	}

	void Input::setMouseClickCallback()
	{
		glfwSetMouseButtonCallback(Engine::getWindow(), mouseClick);
	}

	void Input::setMouseWheelCallback()
	{
		glfwSetScrollCallback(Engine::getWindow(), mouseWheelMove);
	}

	void Input::setMousePosition(double x, double y)
	{
		glfwSetCursorPos(Engine::getWindow(), x, y);
	}
}