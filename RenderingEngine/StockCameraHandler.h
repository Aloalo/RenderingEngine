#pragma once

#include "CameraHandler.h"

class StockCameraHandler :
	public CameraHandler
{
public:
	StockCameraHandler(const Camera &cam, float cameraSpeed, float mouseSpeed);
	~StockCameraHandler(void);

	void keyPress(int key, int scancode, int action, int mods);
	void mouseMove(double x, double y);
	void windowResize(int width, int height);

	void initState();
	void update(float deltaTime);

	glm::mat4 getProjectionMatrix() const;
	glm::mat4 getViewMatrix() const;

private:
	float cameraSpeed;
	float mouseSpeed;

	float springiness;
	double usex, usey;
};

