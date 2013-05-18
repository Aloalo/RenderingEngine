#pragma once

#include "CameraHandler.h"

class StockCameraHandler :
	public CameraHandler
{
public:
	StockCameraHandler(Camera *_cam, float _cameraSpeed, float _mouseSpeed);
	~StockCameraHandler(void);

	void keyPress(int key, int action);
	void mouseMove(int x, int y);
	void mouseClick(int button, int state);
	void windowResize(int width, int height);
	void mouseWheelMove(int pos);

	void initState();
	void update(float deltaTime);

	glm::mat4 getProjectionMatrix() const;
	glm::mat4 getViewMatrix() const;

private:
	float cameraSpeed;
	float mouseSpeed;

	float springiness;
	int usex, usey;
};

