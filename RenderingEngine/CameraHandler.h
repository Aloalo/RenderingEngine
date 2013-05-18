#pragma once

#include "InputObserver.h"
#include "Camera.h"
#include "Updateable.h"

class CameraHandler :
	public InputObserver, public Updateable
{
public:
	CameraHandler(Camera *_cam);
	virtual ~CameraHandler(void);

	virtual glm::mat4 getProjectionMatrix() const = 0;
	virtual glm::mat4 getViewMatrix() const = 0;

protected:
	Camera *cam;
};

