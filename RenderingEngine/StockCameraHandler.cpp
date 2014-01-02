#include "StockCameraHandler.h"
#include "Engine.h"
#include <GLFW/glfw3.h>

using namespace glm;

StockCameraHandler::StockCameraHandler(const Camera &cam, float speed, float rotationSpeed) :
	CameraHandler(cam), speed(speed), rotationSpeed(rotationSpeed), springiness(100), dx(0), dy(0)
{
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
		dir += vec3(0, 0, 1.) * mod;
		break;
	case 'A':
		dir += vec3(-1., 0, 0) * mod;
		break;
	case 'S':
		dir += vec3(0, 0, -1.) * mod;
		break;
	case 'D':
		dir += vec3(1., 0, 0) * mod;
		break;
	case 'Q':
		dir += vec3(0, -1., 0) * mod;
		break;
	case 'E':
		dir += vec3(0, 1., 0) * mod;
		break;
	default:
		break;
	}
}

void StockCameraHandler::mouseMove(double x, double y)
{
	int windowWidth, windowHeight;
	Engine::getWindowSize(windowWidth, windowHeight);

	rotate(float(windowWidth / 2 - x) * rotationSpeed, float(windowHeight / 2 - y) * rotationSpeed);
	glfwSetCursorPos(Engine::getWindow(), windowWidth / 2, windowHeight / 2);
}

void StockCameraHandler::rotate(float yaw, float pitch)
{
	dx += yaw;
	dy += pitch;
}

void StockCameraHandler::windowResize(int width, int height)
{
	cam.aspectRatio = (float)width / height;
}

void StockCameraHandler::update(float deltaTime)
{
	float cf = 1 - exp(-springiness * deltaTime);
	float dxr = cf * dx;
	float dyr = cf * dy;
	cam.rotate(dxr, dyr);
	dx -= dxr;
	dy -= dyr;

	glm::vec3 direction = cam.getDirection();
	glm::vec3 right = cam.getRight();
	glm::vec3 up = glm::cross(right, direction);
	cam.position += (direction * dir.z + up * dir.y + right * dir.x) * deltaTime * speed;
}

glm::mat4 StockCameraHandler::getProjectionMatrix() const
{
	return cam.getProjectionMatrix();
}

glm::mat4 StockCameraHandler::getViewMatrix() const
{
	return cam.getViewMatrix();
}
