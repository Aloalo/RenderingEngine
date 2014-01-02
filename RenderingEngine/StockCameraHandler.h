#pragma once

#include "CameraHandler.h"

class StockCameraHandler :
	public CameraHandler
{
public:
	StockCameraHandler(const Camera &cam, float speed, float rotationSpeed);
	~StockCameraHandler(void);

	void keyPress(int key, int scancode, int action, int mods);
	void mouseMove(double x, double y);
	void windowResize(int width, int height);
	
	void rotate(float yaw, float pitch);

	void update(float deltaTime);

	glm::mat4 getProjectionMatrix() const;
	glm::mat4 getViewMatrix() const;

private:
	glm::vec3 dir;

	float speed;
	float rotationSpeed;
	float springiness;

	float dx, dy;
};

