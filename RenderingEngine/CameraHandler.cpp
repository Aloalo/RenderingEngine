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
