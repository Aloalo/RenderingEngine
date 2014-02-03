#include "MovingLight.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace reng;

MovingLight::MovingLight(Light *light)
	: light(dynamic_cast<SpecularPointLight*>(light))
{
}


MovingLight::~MovingLight(void)
{
}

void MovingLight::initState()
{
	angle = 0.0f;
	angularVel = 30.0;
}

void MovingLight::update(float deltaTime)
{
	angle += angularVel * deltaTime;
	if(angle >= 360.0f)
		angle -= 360.0f;
	light->modelMatrix() = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
}
