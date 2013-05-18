#include "LightHandler.h"


LightHandler::LightHandler(void)
{
}


LightHandler::~LightHandler(void)
{
}

glm::vec3 LightHandler::lightPosition()
{
	return light->position;
}

float LightHandler::lightIntensity()
{
	return light->intensity;
}
