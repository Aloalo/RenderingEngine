#include "Engine.h"
#include "Input.h"

#include <glm/glm.hpp>

using namespace std;
using namespace glm;

namespace reng
{
	list<InputObserver*> Input::observerList;

	Input::Input(void)
	{
		glfwSetKeyCallback(Engine::getWindow(), keyPress);
		glfwSetWindowSizeCallback(Engine::getWindow(), handleResize);
		glfwSetCursorPosCallback(Engine::getWindow(), mouseMove); 
		glfwSetMouseButtonCallback(Engine::getWindow(), mouseClick);
		glfwSetScrollCallback(Engine::getWindow(), mouseWheelMove);
	}

	Input::~Input(void)
	{
	}

	void Input::keyPress(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		double x, y;
		glfwGetCursorPos(Engine::getWindow(), &x, &y);
		for(auto observer : observerList)
			if(observer->active)
				observer->keyPress(KeyPressEvent(vec2(x, y), key, scancode, action, mods));
	}

	void Input::mouseMove(GLFWwindow *window, double x, double y)
	{
		for(auto observer : observerList)
			if(observer->active)
				observer->mouseMove(MouseMoveEvent(vec2(x, y)));
	}

	void Input::mouseClick(GLFWwindow *window, int button, int state, int mods)
	{
		double x, y;
		glfwGetCursorPos(Engine::getWindow(), &x, &y);
		for(auto observer : observerList)
			if(observer->active)
				observer->mouseClick(MouseClickEvent(vec2(x, y), button, state, mods));
	}

	void Input::handleResize(GLFWwindow *window, int width, int height)
	{
		for(auto observer : observerList)
			if(observer->active)
				observer->windowResize(WindowResizeEvent(ivec2(width, height)));
	}

	void Input::mouseWheelMove(GLFWwindow *window, double posx, double posy)
	{
		for(auto observer : observerList)
			if(observer->active)
				observer->mouseWheelMove(MouseWheelMoveEvent(vec2(posx, posy)));
	}

	void Input::addInputObserver(InputObserver *IO)
	{
		observerList.push_back(IO);
	}

	void Input::setMousePosition(double x, double y)
	{
		glfwSetCursorPos(Engine::getWindow(), x, y);
	}
}