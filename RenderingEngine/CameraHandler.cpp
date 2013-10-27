#include "CameraHandler.h"


CameraHandler::CameraHandler(const Camera &cam)
	: cam(cam)
{
}

CameraHandler::~CameraHandler(void)
{
}

const glm::vec3& CameraHandler::getPosition() const
{
	return cam.getPosition();
}
