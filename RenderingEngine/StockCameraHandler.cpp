#include "StockCameraHandler.h"
#include "Engine.h"
#include "Input.h"
#include <GLFW/glfw3.h>

using namespace glm;

namespace reng
{
	StockCameraHandler::StockCameraHandler(const Camera &cam, float speed, float rotationSpeed) :
		CameraHandler(cam), speed(speed), rotationSpeed(rotationSpeed), springiness(100), dx(0), dy(0)
	{
	}

	StockCameraHandler::~StockCameraHandler(void)
	{
	}
	
	void StockCameraHandler::keyPress(const KeyPressEvent &e)
	{
		if(e.action == GLFW_REPEAT)
			return;

		int mod = e.action == GLFW_PRESS ? 1 : -1;
		switch(e.key)
		{
		case 'W':
			dir += vec3(0, 0, -mod);
			break;
		case 'S':
			dir += vec3(0, 0, mod);
			break;
		case 'A':
			dir += vec3(-mod, 0, 0);
			break;
		case 'D':
			dir += vec3(mod, 0, 0);
			break;
		case 'Q':
			dir += vec3(0, -mod, 0);
			break;
		case 'E':
			dir += vec3(0, mod, 0);
			break;
		default:
			break;
		}
	}

	void StockCameraHandler::mouseMove(const MouseMoveEvent &e)
	{
		int w, h;
		Engine::getWindowSize(w, h);

		rotate(float(w / 2 - e.pos.x) * rotationSpeed, float(h / 2 - e.pos.y) * rotationSpeed);
		Input::setMousePosition(w / 2, h / 2);
		//glfwSetCursorPos(Engine::getWindow(), w / 2, h / 2);
	}

	void StockCameraHandler::rotate(float yaw, float pitch)
	{
		dx += yaw;
		dy += pitch;
	}

	void StockCameraHandler::windowResize(const WindowResizeEvent &e)
	{
		cam.aspectRatio = (float)e.size.x / e.size.y;
	}

	void StockCameraHandler::update(float deltaTime)
	{
		float cf = 1 - exp(-springiness * deltaTime);
		float dxr = cf * dx;
		float dyr = cf * dy;
		cam.rotate(dxr, dyr);
		dx -= dxr;
		dy -= dyr;

		//glm::vec3 direction = cam.getDirection();
		//glm::vec3 right = cam.getRight();
		//glm::vec3 up = glm::cross(right, direction);
		//if(dir.x || dir.y || dir.z)
		//	cam.position += deltaTime * speed * normalize(direction * dir.z + vec3(0, dir.y, 0) + right * dir.x);

		if(!(dir.x || dir.y || dir.z))
			return;

		vec3 v
			(
			dir.x,
			dir.z * sin(cam.phiy),
			dir.z * cos(cam.phiy)
			);
		v = vec3
			(
			v.x * cos(cam.phix) + v.z * sin(cam.phix),
			v.y,
			-v.x * sin(cam.phix) + v.z * cos(cam.phix)
			);
		cam.position += deltaTime * speed * normalize(-v + vec3(0, dir.y, 0));
	}


	glm::mat4 StockCameraHandler::getProjectionMatrix() const
	{
		return cam.getProjectionMatrix();
	}

	glm::mat4 StockCameraHandler::getViewMatrix() const
	{
		return cam.getViewMatrix();
	}
}
