#include "StockCameraHandler.h"
#include "Engine.h"
#include <GLFW/glfw3.h>


StockCameraHandler::StockCameraHandler(const Camera &cam, float cameraSpeed, float mouseSpeed)
	: CameraHandler(cam), cameraSpeed(cameraSpeed), mouseSpeed(mouseSpeed)
{
	springiness = 55.0f;
	int windowWidth, windowHeight;
	Engine::getWindowSize(windowWidth, windowHeight);
	usex = windowWidth;
	usey = windowHeight;
}

StockCameraHandler::~StockCameraHandler(void)
{
}

void StockCameraHandler::keyPress(int key, int scancode, int action, int mods)
{
	if(action == GLFW_REPEAT)
		return;
	float mod = action == GLFW_PRESS? 1 : -1;
	switch(key)
	{
	case 'W':
		cam.translate(glm::vec3(0, 0, 1.) * mod);
		break;
	case 'A':
		cam.translate(glm::vec3(-1., 0, 0) * mod);
		break;
	case 'S':
		cam.translate(glm::vec3(0, 0, -1.) * mod);
		break;
	case 'D':
		cam.translate(glm::vec3(1., 0, 0) * mod);
		break;
	case 'Q':
		cam.translate(glm::vec3(0, -1., 0) * mod);
		break;
	case 'E':
		cam.translate(glm::vec3(0, 1., 0) * mod);
		break;
	default:
		break;
	}
}

void StockCameraHandler::mouseMove(double x, double y)
{
	static float lastTime = glfwGetTime();
	float currentTime = glfwGetTime();
	float dt = currentTime - lastTime;
	lastTime = currentTime;

	int windowWidth, windowHeight;
	Engine::getWindowSize(windowWidth, windowHeight);

	float d = 1 - exp(log(0.5) * springiness * dt);
	usex += (x - usex) * d;
	usey += (y - usey) * d;

	cam.rotate(float(windowWidth / 2 - usex) * mouseSpeed, float(windowHeight / 2 - usey) * mouseSpeed);
	glfwSetCursorPos(Engine::getWindow(), windowWidth / 2, windowHeight / 2);
}

void StockCameraHandler::windowResize(int width, int height)
{
	cam.setAspectRatio((float) width / (float) height);
}

void StockCameraHandler::initState()
{
}

void StockCameraHandler::update(float deltaTime)
{
	cam.update(deltaTime * cameraSpeed);
}

glm::mat4 StockCameraHandler::getProjectionMatrix() const
{
	return cam.getProjectionMatrix();
}

glm::mat4 StockCameraHandler::getViewMatrix() const
{
	return cam.getViewMatrix();
}
