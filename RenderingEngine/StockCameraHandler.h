#pragma once

#include "CameraHandler.h"

namespace reng
{
	class StockCameraHandler :
		public CameraHandler
	{
	public:
		StockCameraHandler(const Camera &cam, float speed, float rotationSpeed);
		~StockCameraHandler(void);
		
		void keyPress(const KeyPressEvent &e);
		void mouseMove(const MouseMoveEvent &e);
		void windowResize(const WindowResizeEvent &e);

		void rotate(float yaw, float pitch);

		void update(float deltaTime);

		glm::mat4 getProjectionMatrix() const;
		glm::mat4 getViewMatrix() const;

		float speed;
		float rotationSpeed;

	private:
		glm::vec3 dir;
		float springiness;
		float dx, dy;
	};
}
