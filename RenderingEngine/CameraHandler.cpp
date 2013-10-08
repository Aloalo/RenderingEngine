#include "CameraHandler.h"


CameraHandler::CameraHandler(Camera *_cam)
	: cam(_cam)
{
}

CameraHandler::~CameraHandler(void)
{
	delete cam;
	cam = NULL;
}

const glm::vec3& CameraHandler::getPosition() const
{
	return cam->getPosition();
}
