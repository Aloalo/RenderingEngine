#pragma once

#include "Updateable.h"
#include "Light.h"

class LightHandler :
	public Updateable
{
public:
	LightHandler(void);
	~LightHandler(void);

	virtual void initState() = 0;
	virtual void update(float deltaTime) = 0;

	glm::vec3 lightPosition();
	float lightIntensity();

private:
	Light *light;
};

