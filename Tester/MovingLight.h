#pragma once

#include "Updateable.h"
#include <memory>
#include <SpecularPointLight.h>

class MovingLight :
	public Updateable
{
public:
	MovingLight(std::shared_ptr<Light> &_light);
	~MovingLight(void);

	void initState();
	void update(float deltaTime);

private:
	float angle;
	float angularVel;
	std::shared_ptr<SpecularPointLight> light;
};

