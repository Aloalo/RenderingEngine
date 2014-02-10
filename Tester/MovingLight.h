#pragma once

#include "Updateable.h"
#include "SpecularPointLight.h"
#include <memory>

class MovingLight :
	public reng::Updateable
{
public:
	MovingLight(reng::Light *light);
	~MovingLight(void);

	void initState();
	void update(float deltaTime);

private:
	float angle;
	float angularVel;
	reng::SpecularPointLight *light;
};

